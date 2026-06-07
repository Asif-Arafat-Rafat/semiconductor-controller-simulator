#include "PressureSensor.h"

PressureSensor::PressureSensor():pressure(1000.0){

}
double PressureSensor::readPressure() const{
    return pressure;
}
void PressureSensor::setPressure(double pressure){
    this->pressure=pressure;
}