#pragma once

#include "color.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

struct Vertex {
    Vec3 position;
    Color color;
    Vec2 uv;

    Vertex(float x   = 0.0f,
           float y   = 0.0f,
           float z   = 0.0f,
           float r   = 1.0f,
           float g   = 1.0f,
           float b   = 1.0f,
           float uvX = 0.0f,
           float uvY = 0.0f) {
        position.SetPosition(x, y, z);
        color.SetColor(r, g, b);
        uv.SetPosition(uvX, uvY);
    }
};
