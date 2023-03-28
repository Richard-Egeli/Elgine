#pragma once

#include "elgine/ecs/entity.hpp"

struct EditorCamera : public Entity {
    void Setup(Scene& scene) override;
};
