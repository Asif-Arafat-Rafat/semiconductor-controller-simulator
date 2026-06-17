#pragma once

#include "Message.h"

#include <string>

class MessageSerializer
{
public:
    static std::string serialize(
        const Message& message
    );

    static Message deserialize(
        const std::string& data
    );
};