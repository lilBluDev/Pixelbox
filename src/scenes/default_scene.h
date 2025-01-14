#pragma once
#include "core/scene.h"
#include <iostream>
#include "ECS/Component.h"
#include "utility/Timer.h"

class DefaultScene : public Scene {
public:
    DefaultScene() : Scene() {}
    ~DefaultScene() = default;

    void init() override {
        std::cout << "Default scene initialized!" << std::endl;
    }

    void update(Timer timer) override {
        std::cout << "DeltaTime: " << timer.getDeltaTime() << " - FPS: " << timer.getFPS() << std::endl;        
    }

    void render() override {

    }

    void cleanup() override {
        std::cout << "Default scene cleaned up!" << std::endl;
    }
};