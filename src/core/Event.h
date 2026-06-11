#pragma once

#include "MachineState.h"

#include <string>

enum class EventType {
    MachineStateChanged,
    RecipeStarted,
    RecipeStepStarted,
    RecipeCompleted,
    FaultDetected
};

struct Event {
    EventType type;
    MachineState machineState;
    std::string message;
};