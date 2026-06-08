#include "ProcessChamber.h"
namespace {

constexpr double MIN_PROCESS_TEMPERATURE = 293.15;
constexpr double MAX_PROCESS_TEMPERATURE = 303.15;

}
ProcessChamber::ProcessChamber()
    : waferPresent(false),
      processing(false),
      sensorManager(),
      vacuumSystem(sensorManager)

{
}

bool ProcessChamber::startProcessing()
{
    if (!waferPresent || processing || !vacuumSystem.isVacuumReady() || !isTemperatureSafe()) {
        return false;
    }

    processing = true;
    return true;
}

bool ProcessChamber::startVacuum()
{
    return vacuumSystem.startPump();
}

bool ProcessChamber::isVacuumReady() const
{
    return vacuumSystem.isVacuumReady();
}

bool ProcessChamber::doneProcessing()
{
    if (!processing) {
        return false;
    }

    processing = false;
    return true;
}

bool ProcessChamber::isProcessing() const
{
    return processing;
}

bool ProcessChamber::isWaferPresent() const
{
    return waferPresent;
}

bool ProcessChamber::loadWafer()
{
    if (waferPresent) {
        return false;
    }

    waferPresent = true;
    return true;
}

bool ProcessChamber::unloadWafer()
{
    if (!waferPresent || processing) {
        return false;
    }

    waferPresent = false;
    return true;
}

double ProcessChamber::readTemperature() const
{
    return sensorManager.readTemperature();
}

void ProcessChamber::setTemperature(double temp){
    this->sensorManager.setTemperature(temp);
}

bool ProcessChamber::isTemperatureSafe() const{
    double temp = sensorManager.readTemperature();
    return temp>=MIN_PROCESS_TEMPERATURE &&temp<=MAX_PROCESS_TEMPERATURE;
}
