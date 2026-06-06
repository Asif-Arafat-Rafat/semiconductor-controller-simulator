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
    VacuumSystem vacuum;

    std::cout << vacuum.isPumping() << '\n';
    std::cout << vacuum.isVacuumReady() << '\n';

    vacuum.startPump();

    std::cout << vacuum.isPumping() << '\n';
    std::cout << vacuum.isVacuumReady() << '\n';

    vacuum.stopPump();

    std::cout << vacuum.isPumping() << '\n';
    std::cout << vacuum.isVacuumReady() << '\n';
};