#pragma once

#include "btBulletDynamicsCommon.h"
#include "elgine/types.hpp"

extern Vec3 operator*(const float& f, const Vec3& v);

struct TransformComponent {
    Vec3 position;
    Quat rotation;
    Vec3 scale;
    Mat4 matrices = Mat4(1.0f);
    btTransform btTransform;

    void Translate(Vec3 position);
    void SetPosition(Vec3 position);
    void Rotate(float angle, Vec3 axis);
    void Scale(Vec3 scale);

    Vec3 Forward() const;
    Vec3 Right() const;
    Vec3 Up() const;
};
