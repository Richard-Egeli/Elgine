#ifndef ENGINE_ECS_COMPONENTS_TRANSFORM_HPP_
#define ENGINE_ECS_COMPONENTS_TRANSFORM_HPP_

#include "component.hpp"
#include "quaternion.hpp"
#include "vector3.hpp"

struct Transform {
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
};

#endif  // ENGINE_ECS_COMPONENTS_TRANSFORM_HPP_
