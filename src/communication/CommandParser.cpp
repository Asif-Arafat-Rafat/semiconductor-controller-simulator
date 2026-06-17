#include "CommandParser.h"

#include <stdexcept>

Command CommandParser::parse(
    const ProtocolMessage& message
)
{
    // S1F1 -> STATUS
    if (message.stream == 1 &&
        message.function == 1)
    {
        if (message.value != "none") {
            throw std::invalid_argument(
                "S1F1 does not accept a value"
            );
        }

        return {
            CommandType::STATUS,
            ""
        };
    }

    // S2F1 -> START
    if (message.stream == 2 &&
        message.function == 1)
    {
        if (message.value != "none") {
            throw std::invalid_argument(
                "S2F1 does not accept a value"
            );
        }

        return {
            CommandType::START,
            ""
        };
    }

    // S2F2 -> STOP
    if (message.stream == 2 &&
        message.function == 2)
    {
        if (message.value != "none") {
            throw std::invalid_argument(
                "S2F2 does not accept a value"
            );
        }

        return {
            CommandType::STOP,
            ""
        };
    }

    // S3F1 -> LOAD_WAFER
    if (message.stream == 3 &&
        message.function == 1)
    {
        if (message.value != "none") {
            throw std::invalid_argument(
                "S3F1 does not accept a value"
            );
        }

        return {
            CommandType::LOAD_WAFER,
            ""
        };
    }

    // S3F2 -> UNLOAD_WAFER
    if (message.stream == 3 &&
        message.function == 2)
    {
        if (message.value != "none") {
            throw std::invalid_argument(
                "S3F2 does not accept a value"
            );
        }

        return {
            CommandType::UNLOAD_WAFER,
            ""
        };
    }

    // S4F1 -> SET_TEMPERATURE
    if (message.stream == 4 &&
        message.function == 1)
    {
        if (message.value.empty()) {
            throw std::invalid_argument(
                "S4F1 requires a temperature value"
            );
        }

        return {
            CommandType::SET_TEMPERATURE,
            message.value
        };
    }

    throw std::invalid_argument(
        "Unsupported stream/function"
    );
}