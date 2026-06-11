#include <iostream>
#include <thread>
#include <chrono>

#include "core/MachineController.h"
#include "process/ProcessRecipe.h"
#include "process/RecipeExecutor.h"
#include "process/RecipeLoader.h"
#include "core/EventBus.h"
#include "logging/Logger.h"

int main()
{
    EventBus eventBus;

    MachineController controller(eventBus);

    Logger logger("logs/machine.log");

    // Subscribe to system events
    eventBus.subscribe(
        [&logger](const Event& event) {

            switch (event.type)
            {
            case EventType::RecipeStarted:
                logger.log(
                    LogLevel::INFO,
                    "Recipe started: " + event.message
                );
                break;

            case EventType::RecipeStepStarted:
                logger.log(
                    LogLevel::INFO,
                    "Step started: " + event.message
                );
                break;

            case EventType::RecipeCompleted:
                logger.log(
                    LogLevel::INFO,
                    "Recipe completed: " + event.message
                );
                break;

            case EventType::FaultDetected:
                logger.log(
                    LogLevel::ERROR,
                    "Fault: " + event.message
                );
                break;

            case EventType::MachineStateChanged:
                logger.log(
                    LogLevel::INFO,
                    "Machine state changed: " + event.message
                );
                break;
            }
        }
    );

    logger.log(
        LogLevel::INFO,
        "System started"
    );

    // --------------------------------------------------
    // Fault detection test
    // --------------------------------------------------

    controller.startMachine();

    controller.setTemperature(310.0);

    std::this_thread::sleep_for(
        std::chrono::milliseconds(300)
    );

    std::cout << "State after fault: ";

    if (controller.getCurrentState() == MachineState::ERROR)
    {
        std::cout << "ERROR\n";
    }
    else
    {
        std::cout << "OTHER\n";
    }

    // --------------------------------------------------
    // Stop the fault test before running the recipe
    // --------------------------------------------------

    controller.setTemperature(298.15);

    controller.recoverMachine();

    controller.resetMachine();

    // --------------------------------------------------
    // Load recipe from JSON
    // --------------------------------------------------

    RecipeLoader loader;

    ProcessRecipe recipe ("");
    try {
        recipe = loader.loadFromFile(
            "configs/default_recipe.json"
        );
    }
    catch(const std::exception& e){
        logger.log(
            LogLevel::ERROR,
            "Failed to load recipe: " + std::string(e.what())
        );
        return 1;
    }


    std::cout
        << "Loaded recipe: "
        << recipe.getName()
        << '\n';

    std::cout
        << "Recipe steps: "
        << recipe.getSteps().size()
        << '\n';

    // --------------------------------------------------
    // Execute recipe
    // --------------------------------------------------

    RecipeExecutor executor(
        controller,
        eventBus
    );

    if (executor.executeRecipe(recipe))
    {
        std::cout
            << "Recipe executed successfully\n";
    }
    else
    {
        std::cout
            << "Recipe execution failed\n";
    }

    // --------------------------------------------------
    // Display execution status
    // --------------------------------------------------

    const auto& status =
        executor.getStatus();

    std::cout
        << "Steps: "
        << status.totalSteps
        << '\n';

    std::cout << "Final state: ";

    switch (status.state)
    {
    case RecipeExecutionState::IDLE:
        std::cout << "IDLE";
        break;

    case RecipeExecutionState::RUNNING:
        std::cout << "RUNNING";
        break;

    case RecipeExecutionState::COMPLETED:
        std::cout << "COMPLETED";
        break;

    case RecipeExecutionState::FAILED:
        std::cout << "FAILED";
        break;
    }

    std::cout << '\n';

    if (!status.errorMessage.empty())
    {
        std::cout
            << "Error: "
            << status.errorMessage
            << '\n';
    }

    return 0;
}
