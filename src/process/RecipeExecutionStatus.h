#pragma once

#include <string>

enum class RecipeExecutionState {
    IDLE,
    RUNNING,
    COMPLETED,
    FAILED
};

struct RecipeExecutionStatus {
    RecipeExecutionState state;
    std::string currentStep;
    int currentStepIndex;
    int totalSteps;
    std::string errorMessage;
};