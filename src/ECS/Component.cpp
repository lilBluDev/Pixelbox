#include "ECS/Component.h"
#include "ECS/Object.h"

Scene* Component::getParentScene() const {
    return owner ? owner->getParentScene() : nullptr;
}
