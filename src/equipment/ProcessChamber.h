#pragma once
#include "VacuumSystem.h"
#include "../sensors/TemperatureSensor.h"
class ProcessChamber {
    public:
        ProcessChamber();
        bool loadWafer();
        bool unloadWafer();
        bool startProcessing();
        bool doneProcessing();
        bool startVacuum();
        bool isProcessing() const;
        bool isWaferPresent() const;
        bool isVacuumReady() const;
        double readTemperature() const;
        void setTemperature(double temp);
        bool isTemperatureSafe();
    private:
        bool processing;
        bool waferPresent;
        VacuumSystem vacuumSystem;
        TemperatureSensor temperatureSensor;
};