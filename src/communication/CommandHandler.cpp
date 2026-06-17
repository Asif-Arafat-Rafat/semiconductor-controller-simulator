#include "CommandHandler.h"

#include <stdexcept>

CommandHandler::CommandHandler(
    MachineController& controller
)
    : controller(controller)
{
}

Response CommandHandler::execute(
    const Command& command
)
{
    switch (command.type) {

    case CommandType::START:

        if (controller.startMachine()) {
            return {
                true,
                "Machine started"
            };
        }

        return {
            false,
            "Failed to start machine"
        };


    case CommandType::STOP:

        if (controller.stopMachine()) {
            return {
                true,
                "Machine stopped"
            };
        }

        return {
            false,
            "Failed to stop machine"
        };


    case CommandType::STATUS:

        return {
            true,
            stateToString(
                controller.getCurrentState()
            )
        };


    case CommandType::SET_TEMPERATURE:
    {
        double temperature;

        try {
            temperature =
                std::stod(command.value);
        }
        catch (...) {
            return {
                false,
                "Invalid temperature"
            };
        }

        controller.setTemperature(
            temperature
        );

        return {
            true,
            "Temperature updated"
        };
    }


    case CommandType::LOAD_WAFER:

        if (controller.waferLoaded()) {
            return {
                true,
                "Wafer loaded"
            };
        }

        return {
            false,
            "Failed to load wafer"
        };


    case CommandType::UNLOAD_WAFER:

        if (controller.waferUnloaded()) {
            return {
                true,
                "Wafer unloaded"
            };
        }

        return {
            false,
            "Failed to unload wafer"
        };
    }

    return {
        false,
        "Unsupported command"
    };
}
std::string CommandHandler::stateToString(
    MachineState state
) const
{
    switch (state) {

    case MachineState::IDLE:
        return "IDLE";

    case MachineState::INIT:
        return "INIT";

    case MachineState::LOADING:
        return "LOADING";

    case MachineState::PROCESSING:
        return "PROCESSING";

    case MachineState::UNLOADING:
        return "UNLOADING";

    case MachineState::DONE:
        return "DONE";

    case MachineState::ERROR:
        return "ERROR";

    case MachineState::RECOVER:
        return "RECOVER";

    case MachineState::SHUTDOWN:
        return "SHUTDOWN";
    }

    return "UNKNOWN";
}