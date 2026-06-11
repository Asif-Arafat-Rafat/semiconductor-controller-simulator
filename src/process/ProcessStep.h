#pragma once

#include <string>

class ProcessStep {
public:
    ProcessStep(
        const std::string& name,
        double targetTemperature,
        int durationSeconds
    );

    const std::string& getName() const;
    double getTargetTemperature() const;
    int getDurationSeconds() const;

private:
    std::string name;
    double targetTemperature;
    int durationSeconds;
};