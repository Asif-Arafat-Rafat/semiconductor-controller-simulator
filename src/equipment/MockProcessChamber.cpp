#include "MockProcessChamber.h"

MockProcessChamber::MockProcessChamber()
    : waferPresent(false),
      processing(false),
      vacuumReady(false),
      temperature(298.15)
{
}

bool MockProcessChamber::loadWafer()
{
    if (waferPresent) {
        return false;
    }

    waferPresent = true;
    return true;
}

bool MockProcessChamber::unloadWafer()
{
    if (!waferPresent || processing) {
        return false;
    }

    waferPresent = false;
    return true;
}

bool MockProcessChamber::startProcessing()
{
    if (!waferPresent ||
        processing ||
        !vacuumReady ||
        !isTemperatureSafe()) {

        return false;
    }

    processing = true;
    return true;
}

bool MockProcessChamber::doneProcessing()
{
    if (!processing) {
        return false;
    }

    processing = false;
    return true;
}

bool MockProcessChamber::startVacuum()
{
    vacuumReady = true;
    return true;
}

bool MockProcessChamber::isVacuumReady() const
{
    return vacuumReady;
}

bool MockProcessChamber::isTemperatureSafe() const
{
    return temperature >= 293.15 &&
           temperature <= 303.15;
}

double MockProcessChamber::readTemperature() const
{
    return temperature;
}

void MockProcessChamber::setTemperature(double value)
{
    temperature = value;
}