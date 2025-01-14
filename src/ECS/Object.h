#pragma once

#include <vector>
#include <string>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "ECS/Component.h"

class Scene;
class Component;

class Object {
public:
    explicit Object(const std::string& objectName) : name(objectName) {}

    const std::string& getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    Scene* getParentScene() const { return parentScene; }
    void setParentScene(Scene* scene) { parentScene = scene; }

    template<typename ComponentType, typename... Args>
    ComponentType* addComponent(Args&&... args) {
        auto typeId = std::type_index(typeid(ComponentType));
        if (components.find(typeId) == components.end()) {
            auto component = std::make_unique<ComponentType>(std::forward<Args>(args)...);
            component->setOwner(this);
            components[typeId] = std::move(component);
            return static_cast<ComponentType*>(components[typeId].get());
        }
        return nullptr; // Component already exists
    }

    template<typename ComponentType>
    ComponentType* getComponent() {
        auto typeId = std::type_index(typeid(ComponentType));
        if (components.find(typeId) != components.end()) {
            return static_cast<ComponentType*>(components[typeId].get());
        }
        return nullptr; // Component not found
    }

    template<typename ComponentType>
    bool hasComponent() const {
        auto typeId = std::type_index(typeid(ComponentType));
        return components.find(typeId) != components.end();
    }

private:
    std::string name;
    Scene* parentScene = nullptr;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};