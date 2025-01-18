#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "ECS/Object.h"
#include "utility/Timer.h"
#include "renderer/Renderer.h"
#include "renderer/Camera.h"

#include "events/Event.h"
#include "events/KeyInputEvent.h"
#include "events/MouseInputEvent.h"

class Object;

struct Scene {
    Scene() : eventHandler(std::make_shared<EventHandler>()) {
        // Register listeners for key events
        eventHandler->registerListener(typeid(KeyInputEvent).name(), [](const Event& e) {
            const KeyInputEvent& keyEvent = static_cast<const KeyInputEvent&>(e);
            std::cout << "Key " << keyEvent.getKeyCode()
                      << (keyEvent.getIsPressed() ? " pressed" : " released") << std::endl;
        });

        // Register listeners for mouse events
        eventHandler->registerListener(typeid(MouseInputEvent).name(), [](const Event& e) {
            const MouseInputEvent& mouseEvent = static_cast<const MouseInputEvent&>(e);
            std::cout << "Mouse button " << mouseEvent.getButton()
                      << (mouseEvent.getIsPressed() ? " pressed" : " released")
                      << " at (" << mouseEvent.getX() << ", " << mouseEvent.getY() << ")\n";
        });
    }
    virtual ~Scene() = default;

    // Pure virtual functions for scene lifecycle
    virtual void init() = 0;
    virtual void update(Timer timer) = 0;
    virtual void render(Renderer* renderer) = 0;
    virtual void cleanup() = 0;

    virtual void handleInputEvent(const InputEvent& inputEvent, Timer timer) {
        if (eventHandler) {
            eventHandler->triggerEvent(inputEvent);
        }
    }

    // Object management
    Object* createObject(const std::string& name) {
        if (objectMap.find(name) != objectMap.end()) {
            throw std::runtime_error("Object with name '" + name + "' already exists in the scene.");
        }

        auto object = std::make_unique<Object>(name);
        Object* objectPtr = object.get();
        objectPtr->setParentScene(this);
        objects.push_back(std::move(object));
        objectMap[name] = objectPtr;
        return objectPtr;
    }

    Object* getObjectByName(const std::string& name) {
        if (objectMap.find(name) != objectMap.end()) {
            return objectMap[name];
        }
        return nullptr; // Object not found
    }

    const std::vector<std::unique_ptr<Object>>& getObjects() const {
        return objects;
    }

    Camera* getCamera() {
        return &camera;
    };

protected:
    std::shared_ptr<EventHandler> eventHandler;
    std::vector<std::unique_ptr<Object>> objects; // List of all objects
    std::unordered_map<std::string, Object*> objectMap; // Map for name-based access
    Camera camera;
};

class SceneManager {
public:
    SceneManager();
    ~SceneManager() = default;

    void addScene(const std::string& name, Scene* scene);
    void setCurrentScene(const std::string& name);
    Scene* getCurrentScene() const;
    Scene* getScene(const std::string& name) const;
    void updateCurrentScene(Timer timer);
    void renderCurrentScene(Renderer* renderer);
    void cleanup();
private:
    std::unordered_map<std::string, Scene*> scenes;
    Scene* currentScene;
};

