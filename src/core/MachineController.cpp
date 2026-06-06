#include "MachineController.h"

MachineController::MachineController() : stateMachine() {}

bool MachineController::startMachine() {
    return stateMachine.transitionToState(MachineState::INIT);
}


bool MachineController::resetMachine() {
    return stateMachine.transitionToState(MachineState::IDLE);
}

bool MachineController::recoverMachine() {
    return stateMachine.transitionToState(MachineState::RECOVER);
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

    if (!processChamber.startProcessing()) {
        return false;
    }

    return stateMachine.transitionToState(
        MachineState::PROCESSING
    );
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

bool MachineController::faultDetected() {
    return stateMachine.getCurrentState() == MachineState::ERROR;
}

MachineState MachineController::getCurrentState() const {
    return stateMachine.getCurrentState();
}