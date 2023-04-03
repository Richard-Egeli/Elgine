#pragma once

#include "color.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

struct Vertex {
    Vec3 position;
    Vec3 normal;
    Vec2 uv;
    Color color;

    Vertex(float x   = 0.0f,
           float y   = 0.0f,
           float z   = 0.0f,
           float xn  = 0.0f,
           float yn  = 0.0f,
           float zn  = 0.0f,
           float r   = 1.0f,
           float g   = 1.0f,
           float b   = 1.0f,
           float a   = 1.0f,
           float uvX = 0.0f,
           float uvY = 0.0f) {
        position.SetPosition(x, y, z);
        color.SetColor(r, g, b, a);
        uv.SetPosition(uvX, uvY);
    }
};
