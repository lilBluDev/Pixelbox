#pragma once

#include "events/InputEvent.h"

class KeyInputEvent : public InputEvent {
public:
    KeyInputEvent(int keyCode, bool isPressed)
        : InputEvent(InputEvent::Type::KEYBOARD), keyCode(keyCode), isPressed(isPressed) {}

    int getKeyCode() const { return keyCode; }
    bool getIsPressed() const { return isPressed; }

private:
    int keyCode;
    bool isPressed;
};