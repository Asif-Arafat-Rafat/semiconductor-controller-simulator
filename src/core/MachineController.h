#pragma once
#include "StateMachine.h"
#include "../equipment/ProcessChamber.h"
#include "../equipment/WaferHandler.h"
class MachineController{
public:
    MachineController();
    bool startMachine();
    bool stopMachine();
    bool resetMachine();
    bool recoverMachine();
    bool startProcessing();
    bool initDone();
    bool processingDone();
    bool waferLoaded();
    bool waferUnloaded();
    bool vacuumReady();
    bool faultDetected();
    bool handleFault();
    void setTemperature(double temp);
    MachineState getCurrentState() const;
private:
    StateMachine stateMachine;
    WaferHandler waferHandler;
    ProcessChamber processChamber;
    
};