#include "ProcessChamber.h"

ProcessChamber::ProcessChamber()
    : waferPresent(false),
      processing(false)
{
}

bool ProcessChamber::startProcessing()
{
    if (!waferPresent || processing || !vacuumSystem.isVacuumReady()) {
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