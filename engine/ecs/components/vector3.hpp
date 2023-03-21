#ifndef ENGINE_ECS_COMPONENTS_VECTOR3_HPP_
#define ENGINE_ECS_COMPONENTS_VECTOR3_HPP_

#include "component.hpp"

struct Vector3 : public Component {
    float x;
    float y;
    float z;

    Vector3() { this->id = GetId<Vector3>(); }
};

#endif  // ENGINE_ECS_COMPONENTS_VECTOR3_HPP_
