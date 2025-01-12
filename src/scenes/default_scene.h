#pragma once
#include "core/scene.h"
#include <iostream>
#include "ECS/Component.h"
#include "utility/Timer.h"

class Transform : public Component {
public:
    float x = 0.0f, y = 0.0f;
    float scaleX = 1.0f, scaleY = 1.0f;
    float rotation = 0.0f;
};

class DefaultScene : public Scene {
public:
    DefaultScene() : Scene() {}
    ~DefaultScene() = default;

    void init() override {
        createObject("Test");

        getObjectByName("Test")->addComponent<Transform>();

        std::cout << "Default scene initialized!" << std::endl;
    }

    void update(Timer timer) override {
        Object* testObject = getObjectByName("Test");
        testObject->getComponent<Transform>()->x += timer.getDeltaTime() * 15.0f;
        // std::cout << "Test Object, parent: " << testObject->getParentScene()->getObjectByName("Test")->getComponent<Transform>()->x << std::endl;
        // std::cout << "DeltaTime: " << timer.getDeltaTime() << " - FPS: " << timer.getFPS() << std::endl;        
        std::cout << "Test Object, pos x: " << getObjectByName("Test")->getComponent<Transform>()->x << std::endl;
    }

    void render() override {

    }

    void cleanup() override {
        std::cout << "Default scene cleaned up!" << std::endl;
    }
};