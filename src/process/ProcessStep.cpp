#include "ProcessStep.h"

ProcessStep::ProcessStep(
    const std::string& name,
    double targetTemperature,
    int durationSeconds
):name(name),targetTemperature(targetTemperature),durationSeconds(durationSeconds)
{

}
const std::string& ProcessStep::getName() const
{
    return name;
}
double ProcessStep::getTargetTemperature() const{
    return targetTemperature;
}
int ProcessStep::getDurationSeconds() const{
    return durationSeconds;
}