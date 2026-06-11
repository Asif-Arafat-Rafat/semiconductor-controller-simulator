#include "ProcessRecipe.h"

ProcessRecipe::ProcessRecipe(
    const std::string& name
)
    : name(name)
{
}

void ProcessRecipe::addStep(
    const ProcessStep& step
)
{
    steps.push_back(step);
}

const std::string& ProcessRecipe::getName() const
{
    return name;
}

const std::vector<ProcessStep>& ProcessRecipe::getSteps() const
{
    return steps;
}