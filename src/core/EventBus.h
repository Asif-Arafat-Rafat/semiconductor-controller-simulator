#pragma once

#include "Event.h"

#include <functional>
#include <mutex>
#include <vector>

class EventBus {
public:
    using EventHandler = std::function<void(const Event&)>;

    void subscribe(EventHandler handler);

    void publish(const Event& event);

private:
    std::vector<EventHandler> handlers;
    mutable std::mutex eventMutex;
};