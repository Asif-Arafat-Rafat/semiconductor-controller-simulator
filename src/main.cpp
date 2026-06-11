#include <iostream>

#include "core/MachineController.h"
#include <chrono>
#include <thread>
#include "equipment/WaferHandler.h"
#include "equipment/VacuumSystem.h"
#include "sensors/PressureSensor.h"

const char* stateToString(MachineState state)
{
    switch (state) {

    case MachineState::IDLE:
        return "IDLE";

    case MachineState::INIT:
        return "INITIALIZING";

    case MachineState::LOADING:
        return "LOADING";

    case MachineState::PROCESSING:
        return "PROCESSING";

    case MachineState::UNLOADING:
        return "UNLOADING";

    case MachineState::DONE:
        return "COMPLETED";

    case MachineState::ERROR:
        return "ERROR";

    case MachineState::RECOVER:
        return "RECOVERY";

    case MachineState::SHUTDOWN:
        return "SHUTDOWN";
    }

    return "UNKNOWN";
}

void printState(
    const char* action,
    MachineState state
)
{
    std::cout
        << action
        << " -> "
        << stateToString(state)
        << '\n';
}

int main()
{
    MachineController controller;

    controller.startMachine();
    controller.initDone();

    // Create a temperature fault
    controller.setTemperature(310.0);

    std::this_thread::sleep_for(
        std::chrono::milliseconds(300)
    );

    std::cout << "State after fault: "
              << stateToString(controller.getCurrentState())
              << '\n';

    // Clear the fault
    controller.setTemperature(298.0);

    std::cout << "Recovery: "
              << controller.recoverMachine()
              << '\n';

    std::cout << "State after recovery: "
              << stateToString(controller.getCurrentState())
              << '\n';

    // Return to IDLE
    std::cout << "Reset: "
              << controller.resetMachine()
              << '\n';

    std::cout << "Final state: "
              << stateToString(controller.getCurrentState())
              << '\n';

    return 0;
};