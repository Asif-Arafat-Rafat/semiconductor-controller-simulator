#pragma once

#include "TemperatureSensor.h"
#include "PressureSensor.h"

class SensorManager{
    public:
        SensorManager();
        double readTemperature() const;
        void setTemperature(double temp);
        double readPressure() const;
        void setPressure(double pressure);
    private:
        TemperatureSensor temperatureSensor;
        PressureSensor pressureSensor;
};