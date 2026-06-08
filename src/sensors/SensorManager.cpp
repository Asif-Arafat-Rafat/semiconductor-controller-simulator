#include "SensorManager.h"

SensorManager::SensorManager():temperatureSensor() {}

double SensorManager::readTemperature() const {
    return temperatureSensor.readTemperature();
}

void SensorManager::setTemperature(double temp){
    this->temperatureSensor.setTemperature(temp);
}
void SensorManager::setPressure(double pressure){
    this->pressureSensor.setPressure(pressure);
}

double SensorManager::readPressure() const{
    return pressureSensor.readPressure();

}