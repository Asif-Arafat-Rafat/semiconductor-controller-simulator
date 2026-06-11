#pragma once
#include <string>
#include <vector>
#include "ProcessStep.h"
class ProcessRecipe {
    public:
    explicit ProcessRecipe(const std::string& name);
    void addStep(const ProcessStep& step);
    const std::string& getName() const;
    const std::vector<ProcessStep>& getSteps() const;
    private:
    std::string name;
    std::vector<ProcessStep> steps;
};