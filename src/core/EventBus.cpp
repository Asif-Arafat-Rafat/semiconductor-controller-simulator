#include "EventBus.h"

void EventBus::subscribe(EventHandler handler)
{
    std::lock_guard<std::mutex> lock(eventMutex);

    handlers.push_back(std::move(handler));
}

void EventBus::publish(const Event& event)
{
    std::vector<EventHandler> handlersCopy;

    {
        std::lock_guard<std::mutex> lock(eventMutex);
        handlersCopy = handlers;
    }

    for (const auto& handler : handlersCopy) {
        handler(event);
    }
}