#pragma once
#include "Response.h"
#include "Command.h"
#include "../core/MachineController.h"
class CommandHandler
{
    public:
        explicit CommandHandler(
            MachineController& controller
        );
        Response execute(
            const Command& command
        );
    private:
        MachineController& controller;
        std::string stateToString(
            MachineState state
        ) const;

};