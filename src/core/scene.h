#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "ECS/Object.h"
#include "utility/Timer.h"
#include "renderer/Renderer.h"
#include "renderer/Camera.h"

class Object;

struct Scene {
    Scene() = default;
    virtual ~Scene() = default;

    // Pure virtual functions for scene lifecycle
    virtual void init() = 0;
    virtual void update(Timer timer) = 0;
    virtual void render(Renderer* renderer) = 0;
    virtual void cleanup() = 0;

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

    // void setCamera(Camera& newCamera) {
    //     camera = newCamera;
    // };
    Camera* getCamera() {
        return &camera;
    };

protected:
    

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

