#pragma once
#include "Message.h"
#include "Command.h"
#include "ProtocolSerializer.h"

class CommandParser
{
    public:
        static Command parse(const ProtocolMessage& message);
};