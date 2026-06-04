#include "StateMachine.h"

StateMachine::StateMachine() : currentState(MachineState::IDLE) {}

MachineState StateMachine::getCurrentState() const {
    return currentState;
}

bool StateMachine::transitionToState(MachineState newState) {
    if (isValidTransition(currentState, newState)) {
        currentState = newState;
        return true;
    }
    return false;
}
bool StateMachine::isValidTransition(
    MachineState from,
    MachineState to
) const
{
    switch (from) {

    case MachineState::IDLE:
        return to == MachineState::INIT;

    case MachineState::INIT:
        return to == MachineState::LOADING || to == MachineState::ERROR;

    case MachineState::LOADING:
        return to == MachineState::PROCESSING || to == MachineState::ERROR;

    case MachineState::PROCESSING:
        return to == MachineState::UNLOADING ||to == MachineState::ERROR;

    case MachineState::UNLOADING:
        return to == MachineState::DONE ||to == MachineState::ERROR;

    case MachineState::DONE:
        return to == MachineState::IDLE;

    case MachineState::ERROR:
        return to == MachineState::RECOVER;

    case MachineState::RECOVER:
        return to == MachineState::IDLE;

    case MachineState::SHUTDOWN:
        return false;
    }

    return false;
}