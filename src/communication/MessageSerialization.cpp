#include "MessageSerialization.h"

#include <stdexcept>

std::string MessageSerializer::serialize(
    const Message& message
)
{
    if (message.command.empty()) {
        throw std::invalid_argument(
            "Message command cannot be empty"
        );
    }

    return message.command + "|" + message.value;
}

Message MessageSerializer::deserialize(
    const std::string& data
)
{
    const std::size_t separator =
        data.find('|');

    if (separator == std::string::npos) {
        throw std::invalid_argument(
            "Invalid message format"
        );
    }

    Message message;

    message.command =
        data.substr(0, separator);

    message.value =
        data.substr(separator + 1);

    if (message.command.empty()) {
        throw std::invalid_argument(
            "Message command cannot be empty"
        );
    }

    if (message.value.empty()) {
        throw std::invalid_argument(
            "Message value cannot be empty"
        );
    }

    return message;
}