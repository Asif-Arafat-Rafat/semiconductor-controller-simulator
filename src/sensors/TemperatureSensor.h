#pragma once

class TemperatureSensor {
    public:
        TemperatureSensor();
        double readTemperature() const;
        void setTemperature(double temp);
    private:
        double temperature;
};