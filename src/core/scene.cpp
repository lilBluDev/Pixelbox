#include "core/scene.h"
#include <iostream>
#include <string>
#include <unordered_map>

SceneManager::SceneManager() : scenes(), currentScene(nullptr) {}
// Scene::~Scene() = default;

void SceneManager::addScene(const std::string& name, Scene* scene) {
    scenes[name] = scene;
}

void SceneManager::setCurrentScene(const std::string& name) {
    if (scenes.find(name) != scenes.end()) {
        if (currentScene) {
            currentScene->cleanup();
        }
        currentScene = scenes[name];
        currentScene->init();
    } else {
        std::cerr << "Scene " << name << " not found!" << std::endl;
    }
}

Scene* SceneManager::getCurrentScene() const {
    return currentScene;
}

Scene* SceneManager::getScene(const std::string& name) const {
    if (scenes.find(name) != scenes.end()) {
        return scenes.at(name);
    }
    return nullptr;
}

void SceneManager::updateCurrentScene(Timer timer) {
    if (currentScene) {
        currentScene->update(timer);
    }
}

void SceneManager::renderCurrentScene(Renderer* renderer) {
    if (currentScene) {
        currentScene->render(renderer);
    }
}

void SceneManager::cleanup() {
    for (auto& pair : scenes) {
        if (pair.second) {
            pair.second->cleanup();
            delete pair.second;
        }
    }
    scenes.clear();
    currentScene = nullptr;
}
