#pragma once
#include<string>

struct ProtocolMessage
{
    int stream;
    int function;

    std::string value;
};
