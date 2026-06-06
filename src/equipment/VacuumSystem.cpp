#include "VacuumSystem.h"

VacuumSystem::VacuumSystem():vacuumReady(false),pumping(false){

} 

bool VacuumSystem::startPump(){
    if( isPumping()){
        return false;
    }
    pumping = true;
    vacuumReady = true;
    return true;
}
bool VacuumSystem::stopPump(){
    if(!isPumping()){
        return false;
    }
    pumping = false;
    vacuumReady = false;
    return true;
}

bool VacuumSystem::isVacuumReady() const{
    return vacuumReady;
}
bool VacuumSystem::isPumping() const{
    return pumping;
}
