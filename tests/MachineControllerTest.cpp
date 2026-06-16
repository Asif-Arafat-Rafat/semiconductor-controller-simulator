#include <iostream>

#include "../src/core/MachineController.h"
#include "../src/core/EventBus.h"
#include "../src/equipment/MockProcessChamber.h"
#include "../src/equipment/WaferHandler.h"

int main()
{
    EventBus eventBus;
    MockProcessChamber chamber;
    WaferHandler waferHandler;
    MachineController controller(
        eventBus,
        chamber,
        waferHandler
    );

    if (!controller.startMachine()) {
        std::cerr << "Failed to start machine\n";
        return 1;
    }

    if (controller.getCurrentState() != MachineState::INIT) {
        std::cerr << "Machine did not enter INIT\n";
        return 1;
    }

    if (!controller.initDone()) {
        std::cerr << "Initialization failed\n";
        return 1;
    }

    if (!controller.waferLoaded()) {
        std::cerr << "Wafer loading failed\n";
        return 1;
    }

    if (!controller.vacuumReady()) {
        std::cerr << "Vacuum was not ready\n";
        return 1;
    }

    std::cout << "MachineController test passed\n";

    return 0;
}