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
        tri->getComponent<Obj>()->renObj.setScale(glm::vec3(500.0f, 500.0f, 500.0f));
        
        getCamera()->setRotation(0.0f);
        getCamera()->setPosition(glm::vec3(-0.5f, 0.5f, 0.0f));
        std::cout << "Default scene initialized!" << std::endl;
    }

    void update(Timer timer) override {
        angle += timer.getDeltaTime() * 15.0f;
        getObjectByName("tri")->getComponent<Obj>()->renObj.setRotation(angle, glm::vec3(0.0f, 0.0f, 1.0f));
        std::cout << "DeltaTime: " << timer.getDeltaTime() << " - FPS: " << timer.getFPS() << std::endl;        
    }

    void handleInputEvent(const InputEvent& inputEvent, Timer timer) override {
        std::cout << "Recived input event!" << std::endl;

        if (inputEvent.getEventType() == InputEvent::Type::KEYBOARD) {
            const KeyInputEvent& keyEvent = static_cast<const KeyInputEvent&>(inputEvent);
            if (keyEvent.getKeyCode() == SDLK_w) {
                getCamera()->position.y += timer.getDeltaTime() * 0.5f;
            } else if (keyEvent.getKeyCode() == SDLK_s)
                getCamera()->position.y -= timer.getDeltaTime() * 0.5f;
            if (keyEvent.getKeyCode() == SDLK_a) {
                getCamera()->position.x -= timer.getDeltaTime() * 0.5f;
            } else if (keyEvent.getKeyCode() == SDLK_d) {
                getCamera()->position.x += timer.getDeltaTime() * 0.5f;
            }
        
        }

    }

    void render(Renderer* renderer) override {
        getCamera()->setZoom(0.5f);
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