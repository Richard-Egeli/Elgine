#pragma once

#include "elgine/types.hpp"
#include "elgine/utils.hpp"

struct Transform {
    Vec3 position;
    Quat rotation;
    Vec3 scale;
    Mat4 matrices = Mat4(1.0f);

    void Translate(Vec3 position) { this->position = matrices.Translate(position); }

    void SetPosition(Vec3 position) { this->position = matrices.SetPosition(position); }

    void Rotate(float angle, Vec3 axis) {
        this->rotation = matrices.Rotate(Quat(angle, axis.x, axis.y, axis.z));
    }

    void Scale(Vec3 scale) { matrices.Scale(scale); }

    Vec3 Forward() const { return matrices.Forward(); }
    Vec3 Left() const { return matrices.Left(); }
    Vec3 Up() const { return matrices.Up(); }
};
