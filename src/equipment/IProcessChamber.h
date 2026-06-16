#pragma once

class IProcessChamber {
public:
    virtual ~IProcessChamber() = default;

    virtual bool loadWafer() = 0;
    virtual bool unloadWafer() = 0;

    virtual bool startProcessing() = 0;
    virtual bool doneProcessing() = 0;

    virtual bool startVacuum() = 0;
    virtual bool isVacuumReady() const = 0;

    virtual bool isTemperatureSafe() const = 0;

    virtual double readTemperature() const = 0;
    virtual void setTemperature(double temperature) = 0;
};