#pragma once

class ProcessChamber {
    public:
        ProcessChamber();
        bool loadWafer();
        bool unloadWafer();
        bool startProcessing();
        bool doneProcessing();
        bool isProcessing() const;
        bool isWaferPresent() const;
    private:
        bool processing;
        bool waferPresent;
};