#pragma once

#include "elgine/types.hpp"
#include "elgine/utils.hpp"

struct Transform {
    Vec3<float> position;
    Quat rotation;
    Vec3<float> scale;
    Mat4 matrices = Mat4(1.0f);

    void Translate(Vec3<float> position) { this->position = matrices.Translate(position); }

    void SetPosition(Vec3<float> position) { this->position = matrices.SetPosition(position); }

    void Rotate(float angle, Vec3<float> axis) {
        this->rotation = matrices.Rotate(Quat(angle, axis.x, axis.y, axis.z));
    }

    void Scale(Vec3<float> scale) { matrices.Scale(scale); }

    Vec3<float> Forward() const { return matrices.Forward(); }
    Vec3<float> Left() const { return matrices.Left(); }
    Vec3<float> Up() const { return matrices.Up(); }
};
