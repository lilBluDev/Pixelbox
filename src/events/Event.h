#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <vector>

class Event {
public:
    virtual ~Event() = default;
};

using EventListener = std::function<void(const Event&)>;

class EventHandler {
public:
    void registerListener(const std::string& eventType, EventListener listener);
    void triggerEvent(const Event& event);

private:
    std::unordered_map<std::string, std::vector<EventListener>> listeners;
};