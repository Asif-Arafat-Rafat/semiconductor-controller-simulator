#include "RecipeExecutor.h"
#include "../core/MachineController.h"

#include <chrono>
#include <thread>

RecipeExecutor::RecipeExecutor(
    MachineController& controller,
    EventBus& eventBus
)
    : controller(controller), eventBus(eventBus), status{RecipeExecutionState::IDLE,"",-1,0,""}
{
}

bool RecipeExecutor::executeRecipe(
    const ProcessRecipe& recipe
)
{
    status.state = RecipeExecutionState::RUNNING;
    status.currentStepIndex = -1;
    status.currentStep.clear();
    status.totalSteps = static_cast<int>(recipe.getSteps().size());
    eventBus.publish({
        EventType::RecipeStarted,
        controller.getCurrentState(),
        "Recipe execution started: " + recipe.getName()
    });
    // Machine must start from IDLE.
    if (controller.getCurrentState() != MachineState::IDLE) {
        status.state = RecipeExecutionState::FAILED;
        status.errorMessage = "Machine is not idle.";
        return false;

    }

    // IDLE -> INIT
    if (!controller.startMachine()) {
        status.state = RecipeExecutionState::FAILED;
        status.errorMessage = "Failed to initialize machine.";
        return false;
    }

    // INIT -> LOADING
    if (!controller.initDone()) {
        status.state = RecipeExecutionState::FAILED;
        status.errorMessage = "Machine initialization failed.";
        return false;
    }

    // Load wafer and prepare vacuum.
    if (!controller.waferLoaded()) {
        status.state = RecipeExecutionState::FAILED;
        status.errorMessage = "Failed to load wafer.";
        return false;
    }

    // Wait until vacuum reaches the required pressure.
    while (!controller.vacuumReady()) {

        if (controller.faultDetected()) {
            controller.handleFault();
            status.state = RecipeExecutionState::FAILED;
            status.errorMessage = "Fault detected during vacuum.";
            return false;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(100)
        );
    }

    // LOADING -> PROCESSING
    if (!controller.startProcessing()) {
        status.state = RecipeExecutionState::FAILED;
        status.errorMessage = "Failed to start processing.";
        return false;
    }
    const auto& steps = recipe.getSteps();

    for (int i = 0; i < static_cast<int>(steps.size()); ++i) {

        const auto& step = steps[i];

        status.currentStepIndex = i;
        status.currentStep = step.getName();
        eventBus.publish({
            EventType::RecipeStepStarted,
            controller.getCurrentState(),
            step.getName()
        });
        controller.setTemperature(
            step.getTargetTemperature()
        );

        if (controller.faultDetected()) {
            controller.handleFault();

            status.state = RecipeExecutionState::FAILED;
            status.errorMessage =
                "Unsafe temperature during step: " +
                step.getName();

            return false;
        }

        std::this_thread::sleep_for(
            std::chrono::seconds(
                step.getDurationSeconds()
            )
        );

        if (controller.faultDetected()) {
            controller.handleFault();

            status.state = RecipeExecutionState::FAILED;
            status.errorMessage =
                "Temperature fault during step: " +
                step.getName();

            return false;
        }
    }

    if (!controller.processingDone()) {
        status.state = RecipeExecutionState::FAILED;
        status.errorMessage =
            "Failed to complete processing.";

        return false;
    }

    if (!controller.waferUnloaded()) {
        status.state = RecipeExecutionState::FAILED;
        status.errorMessage =
            "Failed to unload wafer.";

        return false;
    }

    status.currentStep.clear();
    status.currentStepIndex = -1;
    status.state = RecipeExecutionState::COMPLETED;
    eventBus.publish({
        EventType::RecipeCompleted,
        controller.getCurrentState(),
        recipe.getName()
    });
    return true;
}

const RecipeExecutionStatus&
RecipeExecutor::getStatus() const
{
    return status;
}