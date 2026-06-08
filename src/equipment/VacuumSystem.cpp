#include <algorithm>
#include <chrono>
#include <thread>
#include "VacuumSystem.h"
namespace { 
    constexpr double TARGET_PRESSURE = 10.0; 
    constexpr double PRESSURE_DECREMENT = 100.0; 
    constexpr double ATMOSPHERIC_PRESSURE = 1000.0; 
    constexpr std::chrono::milliseconds SLEEP_DURATION(500); 
}
VacuumSystem::VacuumSystem(SensorManager& sensorManager)
    :pumping(false),sensorManager(sensorManager){

    }


VacuumSystem::~VacuumSystem(){
    pumping=false;
    if(pumpThread.joinable()){
        pumpThread.join();
    }
}

bool VacuumSystem::startPump(){
    if( isPumping()){
        return false;
    }
    if (pumpThread.joinable()) {
        pumpThread.join();
    }


    pumping = true;
    pumpThread=std::thread(&VacuumSystem::pumpLoop,this);
    return true;
}

void VacuumSystem::pumpLoop()
{
    while (pumping) {
        if (readPressure() <= TARGET_PRESSURE) {
            break;
        }

        updatePressure();

        std::this_thread::sleep_for(SLEEP_DURATION);
    }

    pumping = false;
}
void VacuumSystem::updatePressure(){
    std::lock_guard<std::mutex> lock(pressureMutex);
    double pressure=sensorManager.readPressure();
    sensorManager.setPressure(
        std::max(TARGET_PRESSURE,pressure-PRESSURE_DECREMENT));
}

bool VacuumSystem::stopPump(){
    if(!isPumping()){
        return false;
    }
    pumping = false;
    if(pumpThread.joinable()){
        pumpThread.join();
    }
    std::lock_guard<std::mutex> lock(pressureMutex);
    sensorManager.setPressure(ATMOSPHERIC_PRESSURE);
    return true;
}



bool VacuumSystem::isVacuumReady() const{
    return sensorManager.readPressure() <= TARGET_PRESSURE;
}

bool VacuumSystem::isPumping() const{
    return pumping;
}

double VacuumSystem::readPressure() const{
    std::lock_guard<std::mutex> lock(pressureMutex);
    return sensorManager.readPressure();
}