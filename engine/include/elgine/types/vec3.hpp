#pragma once

#include <iostream>

#include "elgine/utils.hpp"

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3() {}

    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    void SetPosition(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Print() {
        std::cout << "x: " << this->x << ", y: " << this->y << ", z: " << this->z << std::endl;
    }

    Vec3 Normalize() {
        const float n = 1.0f / Math::SqrtF(x * x + y * y + z * z);
        return Vec3(x * n, y * n, z * n);
    }

    Vec3 Cross(Vec3 v1) { return {y * v1.z - z * v1.y, z * v1.x - x * v1.z, x * v1.y - y * v1.x}; }

    static Vec3 Zero() { return {0.f, 0.f, 0.f}; }
    static Vec3 Up() { return {0.f, 1.f, 0.f}; }
    static Vec3 Right() { return {1.f, 0.f, 0.f}; }
    static Vec3 Forward() { return {0.f, 0.f, 1.f}; }

    Vec3 operator*(const Vec3& v1) {
        Vec3 result;

        result.x = this->x * v1.x;
        result.y = this->y * v1.y;
        result.z = this->z * v1.z;

        return result;
    }

    Vec3 operator/(const Vec3& v1) {
        Vec3 result;

        result.x = this->x / v1.x;
        result.y = this->y / v1.y;
        result.z = this->z / v1.z;

        return result;
    }

    Vec3 operator+(const Vec3& v1) {
        Vec3 result;

        result.x = this->x + v1.x;
        result.y = this->y + v1.y;
        result.z = this->z + v1.z;

        return result;
    }

    Vec3 operator-(const Vec3& v1) {
        Vec3 result;

        result.x = this->x - v1.x;
        result.y = this->y - v1.y;
        result.z = this->z - v1.z;

        return result;
    }
};
