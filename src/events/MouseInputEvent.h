#pragma once

#include "InputEvent.h"

class MouseInputEvent : public InputEvent {
public:
    MouseInputEvent(int x, int y, int button, bool isPressed)
        : InputEvent(InputEvent::Type::MOUSE), x(x), y(y), button(button), isPressed(isPressed) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getButton() const { return button; }
    bool getIsPressed() const { return isPressed; }

private:
    int x;
    int y;
    int button;
    bool isPressed;
};