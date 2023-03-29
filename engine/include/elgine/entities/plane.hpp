#pragma once

#include <array>

#include "elgine/ecs.hpp"

struct Plane : public Entity {
    virtual void Setup(Scene& scene) override;
};
