#pragma once

#include "MachineState.h"

class StateMachine {
public:
    StateMachine();
    MachineState getCurrentState() const;
    bool transitionToState(MachineState newState);
private:
    MachineState currentState;
    bool isValidTransition(
        MachineState fromState, 
        MachineState toState
    ) const;
};