#pragma once
#include "core/EventBus.h"

#include "ProcessRecipe.h"
#include "RecipeExecutionStatus.h"

class MachineController;

class RecipeExecutor {
    public:
        RecipeExecutor(
            MachineController& controller,
            EventBus& eventBus
        );
        bool executeRecipe(const ProcessRecipe& recipe);
        const RecipeExecutionStatus& getStatus() const;
    private:
        MachineController& controller;
        EventBus& eventBus;
        RecipeExecutionStatus status;
};