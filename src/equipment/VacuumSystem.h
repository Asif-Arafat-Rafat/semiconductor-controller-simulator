#pragma once
#include "../sensors/PressureSensor.h"
class VacuumSystem {
    public:
        VacuumSystem();
        bool startPump();
        bool stopPump();
        bool isVacuumReady() const;
        bool isPumping() const;
        double readPressure() const;
    private:
        bool pumping;
        PressureSensor pressureSensor;
};