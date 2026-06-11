#pragma once
#include <atomic>
#include <thread>
#include <chrono>

#include "EventBus.h"
#include "StateMachine.h"
#include "../equipment/ProcessChamber.h"
#include "../equipment/WaferHandler.h"
class MachineController{
public:
    explicit MachineController(EventBus& eventBus);
    ~MachineController();
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

    bool faultDetected() const;
    bool isTemperatureSafe() const;
    bool handleFault();
    void startMonitoring();
    void setTemperature(double temp);
    MachineState getCurrentState() const;
private:
    void monitorLoop();

    std::atomic<bool> monitoring;
    std::thread monitorThread;

    StateMachine stateMachine;
    WaferHandler waferHandler;
    ProcessChamber processChamber;
    
    EventBus& eventBus;
};