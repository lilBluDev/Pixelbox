#pragma once

class Object;
class Scene;

class Component {
public:
    virtual ~Component() = default;

    virtual void init() {}
    // virtual void update(Component* self) {}

    Object* getOwner() const { return owner; }
    void setOwner(Object* newOwner) { owner = newOwner; }

    Scene* getParentScene() const;

protected:
    Object* owner = nullptr; // Pointer to the owning object
};

