#pragma once
#include<string>
#include"ProtocolMessage.h"
class ProtocolSerializer{
    public:
        static std::string serialize(
            const ProtocolMessage& message
        );
        static ProtocolMessage deserialize(
            const std::string& data
        );
};