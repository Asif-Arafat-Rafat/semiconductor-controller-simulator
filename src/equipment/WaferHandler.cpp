#include "WaferHandler.h"

WaferHandler::WaferHandler()
    : waferLoaded(false)
{
}

bool WaferHandler::loadWafer()
{
    if (waferLoaded) {
        return false;
    }

    waferLoaded = true;
    return true;
}

bool WaferHandler::unloadWafer()
{
    if (!waferLoaded) {
        return false;
    }

    waferLoaded = false;
    return true;
}

bool WaferHandler::isWaferLoaded() const
{
    return waferLoaded;
}