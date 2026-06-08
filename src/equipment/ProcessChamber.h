#pragma once
#include "VacuumSystem.h"
#include "../sensors/SensorManager.h"
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
        bool isTemperatureSafe() const;
    private:
        bool processing;
        bool waferPresent;
        VacuumSystem vacuumSystem;
        SensorManager sensorManager;
};