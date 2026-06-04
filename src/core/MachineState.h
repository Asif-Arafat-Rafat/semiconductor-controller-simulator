#pragma once

enum class MachineState {
    IDLE,
    INIT,
    LOADING,
    PROCESSING,
    UNLOADING,
    DONE,
    ERROR,
    RECOVER,
    SHUTDOWN
};