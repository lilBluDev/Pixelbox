#include "events/Event.h"

void EventHandler::registerListener(const std::string& eventType, EventListener listener) {
    listeners[eventType].push_back(listener);
}

void EventHandler::triggerEvent(const Event& event) {
    const std::string eventType = typeid(event).name();
    if (listeners.find(eventType) != listeners.end()) {
        for (const auto& listener : listeners[eventType]) {
            listener(event);
        }
    }
}
