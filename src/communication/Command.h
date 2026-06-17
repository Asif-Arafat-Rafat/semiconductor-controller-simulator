#pragma once
enum class CommandType
{
    START,
    STOP,
    STATUS,
    SET_TEMPERATURE,
    LOAD_WAFER,
    UNLOAD_WAFER,
    UNKNOWN
};
struct Command
{
    CommandType type;
    std::string value;
};