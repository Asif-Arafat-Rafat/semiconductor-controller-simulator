#include "VacuumSystem.h"
#include <algorithm>
#include <chrono>
#include <thread>
constexpr double TARGET_PRESSURE = 10.0;
constexpr double DECREASING_PRESSURE = 100.0;
constexpr std::chrono::milliseconds SLEEP_DURATION(500);
VacuumSystem::VacuumSystem():pumping(false){

} 

bool VacuumSystem::startPump(){
    if( isPumping()){
        return false;
    }
    pumping = true;
    double pressure = readPressure();
    while (pressure>TARGET_PRESSURE){
        pressure=std::max(pressure-DECREASING_PRESSURE,TARGET_PRESSURE);
        pressureSensor.setPressure(pressure);
        std::this_thread::sleep_for(SLEEP_DURATION);
    }
    return true;
}
bool VacuumSystem::stopPump(){
    if(!isPumping()){
        return false;
    }
    pumping = false;
    
    pressureSensor.setPressure(1000.0);
    return true;
}

bool VacuumSystem::isVacuumReady() const{
    return pressureSensor.readPressure() <= TARGET_PRESSURE;
}
bool VacuumSystem::isPumping() const{
    return pumping;
}
double VacuumSystem::readPressure() const{
    return pressureSensor.readPressure();
}