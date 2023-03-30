#pragma once

#include "elgine/utils.hpp"
struct Vec2 {
    float x;
    float y;

    Vec2(float x = 0.f, float y = 0.f) : x(x), y(y) {}

    void SetPosition(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vec2 Normalize() {
        float n = 1.0f / Math::Sqrt(x * x + y * y);
        return Vec2(x * n, y * n);
    }

    void Print() const { std::cout << "x: " << x << ", y: " << y << std::endl; }
};
