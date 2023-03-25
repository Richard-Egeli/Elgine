#ifndef ELGINE_ENGINE_COMPONENTS_TRANSFORM_HPP_
#define ELGINE_ENGINE_COMPONENTS_TRANSFORM_HPP_

#include "quaternion.hpp"
#include "vector3.hpp"

struct Transform {
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
};

#endif  // ELGINE_ENGINE_COMPONENTS_TRANSFORM_HPP_
