#include "MachineController.h"

MachineController::MachineController(EventBus& eventBus) : 
    stateMachine(),
    monitoring(true),
    eventBus(eventBus) 
    {
        monitorThread=std::thread(&MachineController::monitorLoop,this);
    }

MachineController::~MachineController()
{
    monitoring = false;

    if (monitorThread.joinable()) {
        monitorThread.join();
    }
}

bool MachineController::startMachine() {
    return stateMachine.transitionToState(MachineState::INIT);
}

bool MachineController::resetMachine() {
    return stateMachine.transitionToState(MachineState::IDLE);
}

bool MachineController::recoverMachine()
{
    if (stateMachine.getCurrentState() != MachineState::ERROR) {
        return false;
    }

    if (faultDetected()) {
        return false;
    }

    return stateMachine.transitionToState(
        MachineState::RECOVER
    );
}

bool MachineController::startProcessing(){
    if (stateMachine.getCurrentState() != MachineState::LOADING) {
        return false;
    }

    if (!processChamber.isVacuumReady()) {
        return false;
    }

    if (!processChamber.startProcessing()) {
        return false;
    }

    return stateMachine.transitionToState(
        MachineState::PROCESSING
    );

}

bool MachineController::initDone() {
    return stateMachine.transitionToState(MachineState::LOADING);
}

bool MachineController::processingDone() {
    if(stateMachine.getCurrentState() != MachineState::PROCESSING) {
        return false;
    }
    if(!processChamber.doneProcessing()) {
        return false;
    }
    return stateMachine.transitionToState(MachineState::UNLOADING);
}

bool MachineController::waferLoaded()
{
    if (stateMachine.getCurrentState() != MachineState::LOADING) {
        return false;
    }

    if (!waferHandler.loadWafer()) {
        return false;
    }

    if (!processChamber.loadWafer()) {
        waferHandler.unloadWafer();
        return false;
    }

    if (!waferHandler.unloadWafer()) {
        return false;
    }
    if (!processChamber.startVacuum()) {
        return false;
    }
    return true;

}

bool MachineController::waferUnloaded() {
    if( stateMachine.getCurrentState() != MachineState::UNLOADING){
        return false;
    }
    if(!processChamber.unloadWafer()){
        return false;
    }
    if(!waferHandler.loadWafer()){
        return false;
    }
    if(!waferHandler.unloadWafer()){
        return false;
    }
    return stateMachine.transitionToState(MachineState::DONE);
}

bool MachineController::vacuumReady() {
    return processChamber.isVacuumReady();
}

bool MachineController::faultDetected() const {
    return !processChamber.isTemperatureSafe();
}

bool MachineController::handleFault(){
    if (!faultDetected()) {
        return false;
    }

    bool transitioned = stateMachine.transitionToState(
        MachineState::ERROR
    );

    if(transitioned) {
        eventBus.publish({
            EventType::FaultDetected,
            stateMachine.getCurrentState(),
            "Fault detected: Temperature is unsafe"
        });
    }

    return transitioned;
}

void MachineController::setTemperature(double temp){
    processChamber.setTemperature(temp);
}

void MachineController::monitorLoop()
{
    while (monitoring) {

        if (faultDetected()) {
            handleFault();
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(100)
        );
    }
}

bool MachineController::isTemperatureSafe() const {
    return processChamber.isTemperatureSafe();
}

void MachineController::startMonitoring()
{
    if (monitoring) {
        return;
    }

    monitoring = true;

    monitorThread = std::thread(
        &MachineController::monitorLoop,
        this
    );
}
MachineState MachineController::getCurrentState() const {
    return stateMachine.getCurrentState();
}