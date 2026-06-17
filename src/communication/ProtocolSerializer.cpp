#include "ProtocolSerializer.h"
#include "ProtocolMessage.h"
#include <string>
#include <stdexcept>

std::string ProtocolSerializer::serialize(const ProtocolMessage& message){
    if(message.stream<1||message.stream>99){
        throw std::invalid_argument(
            "Invalid stream number"
        );
    }
    if (
        message.function < 1 ||
        message.function > 99
    ) {
        throw std::invalid_argument(
            "Invalid function number"
        );
    }
    return
        "S" +
        std::to_string(message.stream) +
        "F" +
        std::to_string(message.function) +
        "|" +
        message.value;

};

ProtocolMessage ProtocolSerializer::deserialize(
    const std::string& data
)
{
    if (data.empty() || data[0] != 'S') {
        throw std::invalid_argument(
            "Invalid protocol message"
        );
    }

    const std::size_t fPosition =
        data.find('F');

    if (fPosition == std::string::npos) {
        throw std::invalid_argument(
            "Missing function"
        );
    }

    const std::size_t separator =
        data.find('|', fPosition);

    if (separator == std::string::npos) {
        throw std::invalid_argument(
            "Missing value separator"
        );
    }

    if (fPosition <= 1) {
        throw std::invalid_argument(
            "Missing stream number"
        );
    }

    const std::string streamString =
        data.substr(
            1,
            fPosition - 1
        );

    if (
        separator <= fPosition + 1
    ) {
        throw std::invalid_argument(
            "Missing function number"
        );
    }

    const std::string functionString =
        data.substr(
            fPosition + 1,
            separator - fPosition - 1
        );

    int stream;
    int function;

    try {
        std::size_t consumed = 0;

        stream = std::stoi(
            streamString,
            &consumed
        );

        if (consumed != streamString.size()) {
            throw std::invalid_argument(
                "Invalid stream number"
            );
        }

        consumed = 0;

        function = std::stoi(
            functionString,
            &consumed
        );

        if (consumed != functionString.size()) {
            throw std::invalid_argument(
                "Invalid function number"
            );
        }
    }
    catch (...) {
        throw std::invalid_argument(
            "Invalid protocol numbers"
        );
    }

    if (stream < 1 || stream > 99) {
        throw std::invalid_argument(
            "Invalid stream number"
        );
    }

    if (function < 1 || function > 99) {
        throw std::invalid_argument(
            "Invalid function number"
        );
    }

    return {
        stream,
        function,
        data.substr(separator + 1)
    };
}