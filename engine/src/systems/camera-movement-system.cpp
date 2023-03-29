#include "camera-movement-system.hpp"

#include "camera-movement.hpp"
#include "camera.hpp"
#include "mat4.hpp"
#include "math.hpp"
#include "scene-view.hpp"
#include "time.hpp"
#include "transform.hpp"

void CameraMovementSystem(Scene& scene) {
    for (auto& e : SceneView<CameraMovement, Transform>(scene)) {
        CameraMovement* cam = scene.GetComponent<CameraMovement>(e);
        Transform* trans    = scene.GetComponent<Transform>(e);

        const float radius = 10.f;
        const float camX   = Math::Sin(Time::time) * radius;
        const float camZ   = Math::Cos(Time::time) * radius;

        Camera::View.LookAt({camX, 0.f, camZ}, Vec3::Zero(), Vec3::Up());
    }
}
