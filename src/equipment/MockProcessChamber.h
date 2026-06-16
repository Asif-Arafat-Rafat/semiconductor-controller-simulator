#pragma once

#include "IProcessChamber.h"

class MockProcessChamber : public IProcessChamber {
public:
    MockProcessChamber();

    bool loadWafer() override;
    bool unloadWafer() override;

    bool startProcessing() override;
    bool doneProcessing() override;

    bool startVacuum() override;
    bool isVacuumReady() const override;

    bool isTemperatureSafe() const override;

    double readTemperature() const override;
    void setTemperature(double temperature) override;

private:
    bool waferPresent;
    bool processing;
    bool vacuumReady;
    double temperature;
};