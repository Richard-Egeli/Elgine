#include "transform-component.hpp"

Vec3 operator*(const float& f, const Vec3& v) {
    Vec3 res = Vec3::Zero();
    res.x    = v.x * f;
    res.y    = v.y * f;
    res.z    = v.z * f;
    return res;
}

void Transform::Translate(Vec3 position) {
    this->position = matrices.SetPosition(this->position + position);
}

void Transform::SetPosition(Vec3 position) { this->position = matrices.SetPosition(position); }

void Transform::Rotate(float angle, Vec3 axis) {
    this->rotation = matrices.Rotate(Quat(angle, axis.x, axis.y, axis.z));
}

void Transform::Scale(Vec3 scale) { matrices.Scale(scale); }

Vec3 Transform::Forward() const { return matrices.Forward(); }
Vec3 Transform::Right() const { return Forward().Cross(Vec3::Up()); }
Vec3 Transform::Up() const { return Vec3::Up(); }
