#pragma once
#include "VacuumSystem.h"
class ProcessChamber {
    public:
        ProcessChamber();
        bool loadWafer();
        bool unloadWafer();
        bool startProcessing();
        bool doneProcessing();
        bool startVacuum();
        bool isProcessing() const;
        bool isWaferPresent() const;
        bool isVacuumReady() const;
    private:
        bool processing;
        bool waferPresent;
        VacuumSystem vacuumSystem;
};