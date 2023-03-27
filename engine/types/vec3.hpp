#ifndef ELGINE_ENGINE_TYPES_VECTOR3_HPP_
#define ELGINE_ENGINE_TYPES_VECTOR3_HPP_

#include <iostream>

#include "elgine/utils.hpp"

template <typename T>
struct Vec3 {
    T x;
    T y;
    T z;

    Vec3() {}

    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    void SetPosition(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Print() {
        std::cout << "x: " << this->x << ", y: " << this->y << ", z: " << this->z << std::endl;
    }

    Vec3<T> Normalize() {
        const float n = 1.0f / Math::SqrtF(x * x + y * y + z * z);
        return Vec3<T>(x * n, y * n, z * n);
    }

    Vec3<T> operator*(const Vec3& v1) {
        Vec3<T> result;

        result.x = this->x * v1.x;
        result.y = this->y * v1.y;
        result.z = this->z * v1.z;

        return result;
    }

    Vec3<T> operator/(const Vec3& v1) {
        Vec3<T> result;

        result.x = this->x / v1.x;
        result.y = this->y / v1.y;
        result.z = this->z / v1.z;

        return result;
    }

    Vec3<T> operator+(const Vec3& v1) {
        Vec3<T> result;

        result.x = this->x + v1.x;
        result.y = this->y + v1.y;
        result.z = this->z + v1.z;

        return result;
    }

    Vec3<T> operator-(const Vec3& v1) {
        Vec3<T> result;

        result.x = this->x - v1.x;
        result.y = this->y - v1.y;
        result.z = this->z - v1.z;

        return result;
    }
};

#endif  // ELGINE_ENGINE_TYPES_VECTOR3_HPP_
