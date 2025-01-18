#pragma once

#include "events/Event.h"

class InputEvent : public Event {
public:
    enum class Type {
        KEYBOARD,
        MOUSE
    };

    explicit InputEvent(Type type) : eventType(type) {}
    Type getEventType() const { return eventType; }

private:
    Type eventType;
};