#include <iostream>

#include "core/MachineController.h"

#include "equipment/WaferHandler.h"
#include "equipment/VacuumSystem.h"


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

    if (!controller.startMachine()) {
        std::cout << "Failed to start machine\n";
        return 1;
    }

    printState(
        "Start",
        controller.getCurrentState()
    );

    if (!controller.initDone()) {
        std::cout << "Initialization failed\n";
        return 1;
    }

    printState(
        "Initialization complete",
        controller.getCurrentState()
    );

    if (!controller.waferLoaded()) {
        std::cout << "Wafer loading/processing preparation failed\n";
        return 1;
    }

    printState(
        "Wafer loaded and processing started",
        controller.getCurrentState()
    );

    if (!controller.processingDone()) {
        std::cout << "Processing failed\n";
        return 1;
    }

    printState(
        "Process complete",
        controller.getCurrentState()
    );

    if (!controller.waferUnloaded()) {
        std::cout << "Wafer unloading failed\n";
        return 1;
    }

    printState(
        "Wafer unloaded",
        controller.getCurrentState()
    );

    if (!controller.resetMachine()) {
        std::cout << "Reset failed\n";
        return 1;
    }

    printState(
        "Reset",
        controller.getCurrentState()
    );

    return 0;
};