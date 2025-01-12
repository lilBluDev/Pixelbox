#pragma once

#include "ECS/Object.h"

class Object;

class Component {
public:
    virtual ~Component() = default;

    virtual void init() {}
    virtual void update(Component* self) {}

    Object* getOwner() const { return owner; }
    void setOwner(Object* newOwner) { owner = newOwner; }

    Scene* getParentScene() const { return owner->getParentScene(); }

protected:
    Object* owner = nullptr; // Pointer to the owning object
};

