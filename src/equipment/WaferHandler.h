#pragma once
#include "IWaferHandler.h"
class WaferHandler:public IWaferHandler {
    public:
        WaferHandler();
        bool loadWafer() override;
        bool unloadWafer() override;

        bool isWaferLoaded() const override;
    private:
        bool waferLoaded;
};