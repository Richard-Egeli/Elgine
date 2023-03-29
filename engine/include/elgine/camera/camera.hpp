#pragma once

#include "mat4.hpp"
struct Camera {
    friend class Elgine;
    static Mat4 View;
    static Mat4 Projection;

    static Mat4 GetView();
    static Mat4 GetProjection();

 private:
    static void Init();
};
