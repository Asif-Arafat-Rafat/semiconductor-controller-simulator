#pragma once

class VacuumSystem {
    public:
        VacuumSystem();
        bool startPump();
        bool stopPump();
        bool isVacuumReady() const;
        bool isPumping() const;
    private:
        bool vacuumReady;
        bool pumping;
};