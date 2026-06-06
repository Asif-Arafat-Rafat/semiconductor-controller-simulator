#include "ProcessChamber.h"

ProcessChamber::ProcessChamber()
    : waferPresent(false),
      processing(false)
{
}

bool ProcessChamber::startProcessing()
{
    if (!waferPresent || processing) {
        return false;
    }

    processing = true;
    return true;
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