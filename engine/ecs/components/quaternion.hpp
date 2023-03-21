#ifndef ENGINE_ECS_COMPONENTS_QUATERNION_HPP_
#define ENGINE_ECS_COMPONENTS_QUATERNION_HPP_

#include "component.hpp"

struct Quaternion : public Component {
    float w;
    float x;
    float y;
    float z;

    Quaternion() { this->id = GetId<Quaternion>(); }
};

#endif  // ENGINE_ECS_COMPONENTS_QUATERNION_HPP_
