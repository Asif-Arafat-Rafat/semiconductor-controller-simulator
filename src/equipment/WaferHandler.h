#pragma once

class WaferHandler {
    public:
        WaferHandler();
        bool loadWafer();
        bool unloadWafer();

        bool isWaferLoaded() const;
    private:
        bool waferLoaded;
};