#pragma once 

class PressureSensor {
    public:
        PressureSensor();
        double readPressure() const;
        void setPressure(double pressure);
    private:
        double pressure;
};