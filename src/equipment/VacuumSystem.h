#pragma once
#include <thread>
#include <atomic>
#include <mutex>

#include "../sensors/PressureSensor.h"

class VacuumSystem {
    public:
        VacuumSystem();
        ~VacuumSystem();
        bool startPump();
        bool stopPump();
        bool isVacuumReady() const;
        bool isPumping() const;
        double readPressure() const;

    private:
        std::atomic<bool> pumping;
        void updatePressure();
        PressureSensor pressureSensor;
        mutable std::mutex pressureMutex;
        std::thread pumpThread;
        void pumpLoop();
};