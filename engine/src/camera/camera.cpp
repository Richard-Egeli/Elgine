#include "camera.hpp"

Mat4 Camera::View       = Mat4(1.0f);
Mat4 Camera::Projection = Mat4(1.0f);

void Camera::Init() {
    View.Translate({0, 0, -3});
    Projection.Perspective(Math::RadF(45.0f), 800.f / 600.f, 0.1f, 100.f);
}

Mat4 Camera::GetView() { return View; }

Mat4 Camera::GetProjection() { return Projection; }
