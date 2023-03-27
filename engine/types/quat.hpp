#ifndef ELGINE_ENGINE_TYPES_QUATERNION_HPP_
#define ELGINE_ENGINE_TYPES_QUATERNION_HPP_

#include "vec3.hpp"
struct Quat {
    float w;
    float x;
    float y;
    float z;

    Quat(float w = 1, float x = 1, float y = 1, float z = 1) : w(w), x(x), y(y), z(z) {}

    Quat Normalize();

    void Print();
};

#endif  // ELGINE_ENGINE_TYPES_QUATERNION_HPP_
