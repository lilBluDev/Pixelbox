#pragma once
#include "core/scene.h"
#include <iostream>
#include "ECS/Object.h"
#include "utility/Timer.h"
#include "renderer/Renderer.h"

#include "components/Obj.h"



class DefaultScene : public Scene {
public:
    DefaultScene() : Scene() {}
    ~DefaultScene() = default;

    void init() override {
        std::vector<float> triangleVertices = {
            0.0f,  0.5f, 0.0f, // Top
            -0.5f, -0.5f, 0.0f, // Bottom left
            0.5f, -0.5f, 0.0f  // Bottom right
        };

        Object* tri = createObject("tri");
        tri->addComponent<Obj>(triangleVertices);
        tri->getComponent<Obj>()->renObj.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
        std::cout << "Default scene initialized!" << std::endl;
    }

    void update(Timer timer) override {
        angle += timer.getDeltaTime() * 15.0f;
        getObjectByName("tri")->getComponent<Obj>()->renObj.setRotation(angle, glm::vec3(0.0f, 0.0f, 1.0f));
        std::cout << "DeltaTime: " << timer.getDeltaTime() << " - FPS: " << timer.getFPS() << std::endl;        
    }

    void render(Renderer* renderer) override {
        for (const auto& object : getObjects()) {
            if (object->hasComponent<Obj>()) {
                renderer->addObject(&object->getComponent<Obj>()->renObj);
            }
        }
    }

    float angle = 0.0f;

    void cleanup() override {
        std::cout << "Default scene cleaned up!" << std::endl;
    }
};