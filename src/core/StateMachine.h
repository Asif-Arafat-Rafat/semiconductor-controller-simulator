#pragma once
#include <mutex>
#include "MachineState.h"

class StateMachine {
public:
    StateMachine();
    MachineState getCurrentState() const;
    bool transitionToState(MachineState newState);
private:
    MachineState currentState;
    mutable std::mutex stateMutex;
    bool isValidTransition(
        MachineState fromState, 
        MachineState toState
    ) const;
};