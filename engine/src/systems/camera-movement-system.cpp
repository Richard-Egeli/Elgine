#include "camera-movement-system.hpp"

#include "camera-movement.hpp"
#include "camera.hpp"
#include "input-key.hpp"
#include "input.hpp"
#include "mat4.hpp"
#include "math.hpp"
#include "scene-view.hpp"
#include "time.hpp"
#include "transform-component.hpp"

void CameraMovementSystem(Scene& scene) {
    for (auto& entity : SceneView<CameraMovement, TransformComponent>(scene)) {
        CameraMovement* cam       = scene.GetComponent<CameraMovement>(entity);
        TransformComponent* trans = scene.GetComponent<TransformComponent>(entity);

        Vec3 input    = Vec3::Zero();
        Vec3 rotation = Vec3::Zero();
        Vec3 movement = Vec3::Zero();

        input.x += Input::GetKey(InputKey::D) - Input::GetKey(InputKey::A);
        input.y += Input::GetKey(InputKey::SPACE) - Input::GetKey(InputKey::Z);
        input.z += Input::GetKey(InputKey::W) - Input::GetKey(InputKey::S);

        rotation.x += Input::GetAxis(InputKey::MouseX);
        rotation.y += Input::GetAxis(InputKey::MouseY);

        Vec3 forward = input.z * trans->Forward();
        Vec3 right   = input.x * trans->Right();
        Vec3 up      = input.y * trans->Up();
        movement     = (forward + right + up).Normalize();

        trans->Translate(movement * 0.1);
        trans->Rotate(rotation.x, Vec3::Up());
        trans->Rotate(rotation.y, trans->Right());

        Camera::View.LookAt(trans->position, trans->position + trans->Forward(), Vec3::Up());
    }
}
