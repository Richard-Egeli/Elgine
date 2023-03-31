#include "vec3.hpp"

Vec3 operator*(const float& f, const Vec3& v) {
    Vec3 res = Vec3::Zero();
    res.x    = v.x * f;
    res.y    = v.y * f;
    res.z    = v.z * f;
    return res;
}

float Vec3::operator[](const int& index) { return this->x + index * sizeof(float); }

float Vec3::Dot(const Vec3& v) { return x * v.x + y * v.y + z * v.z; }
