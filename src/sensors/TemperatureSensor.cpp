#include "TemperatureSensor.h"

namespace{
    constexpr double DEFAULT_TEMPERATURE= 298.15;
}

TemperatureSensor::TemperatureSensor():temperature(DEFAULT_TEMPERATURE){}

double TemperatureSensor::readTemperature() const {
    return temperature;
};

void TemperatureSensor::setTemperature(double temp){
    this->temperature=temp;
}