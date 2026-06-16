#pragma once
class IWaferHandler{
    public:
        virtual ~IWaferHandler() = default;
        virtual bool loadWafer() = 0;
        virtual bool unloadWafer() = 0;

        virtual bool isWaferLoaded() const = 0;
};