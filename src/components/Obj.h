#pragma once

#include "renderer/renderableObject.h"
#include "ECS/Component.h"

struct Obj : public Component {
    std::vector<float> vertecies;
    RenderableObject renObj;

    Obj(const std::vector<float>& vert)
        : renObj(vert) {
            vertecies = vert;
        }
};
