#pragma once
#include <thread>
#include <atomic>
#include <mutex>

#include "../sensors/SensorManager.h"

class VacuumSystem {
    public:
        VacuumSystem(SensorManager& sensorManager);
        ~VacuumSystem();
        bool startPump();
        bool stopPump();
        bool isVacuumReady() const;
        bool isPumping() const;
        double readPressure() const;

    private:
        std::atomic<bool> pumping;
        void updatePressure();
        SensorManager& sensorManager;
        mutable std::mutex pressureMutex;
        std::thread pumpThread;
        void pumpLoop();
};