#include <iostream>

#include "core/MachineController.h"

#include "equipment/WaferHandler.h"

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

    std::cout << "Semiconductor Machine Controller\n";
    std::cout << "================================\n\n";

    printState(
        "Initial",
        controller.getCurrentState()
    );

    controller.startMachine();

    printState(
        "Start",
        controller.getCurrentState()
    );

    controller.initDone();

    printState(
        "Initialization complete",
        controller.getCurrentState()
    );

    controller.waferLoaded();

    printState(
        "Wafer loaded",
        controller.getCurrentState()
    );

    controller.processingDone();

    printState(
        "Process complete",
        controller.getCurrentState()
    );

    controller.waferUnloaded();

    printState(
        "Wafer unloaded",
        controller.getCurrentState()
    );

    controller.resetMachine();

    printState(
        "Reset",
        controller.getCurrentState()
    );

    return 0;

}