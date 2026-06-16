#pragma once
#include "VacuumSystem.h"
#include "../sensors/SensorManager.h"
#include "IProcessChamber.h"

class ProcessChamber : public IProcessChamber {
    public:
        ProcessChamber();

        bool loadWafer() override;
        bool unloadWafer() override;

        bool startProcessing() override;
        bool doneProcessing() override;

        bool startVacuum() override;
        bool isVacuumReady() const override;

        bool isTemperatureSafe() const override;

        bool isProcessing() const;
        bool isWaferPresent() const;
        double readTemperature() const override;
        void setTemperature(double temperature) override;
    private:
        bool processing;
        bool waferPresent;
        VacuumSystem vacuumSystem;
        SensorManager sensorManager;
};