#include "editor-camera.hpp"

#include "camera-movement-system.hpp"
#include "camera-movement.hpp"
#include "scene.hpp"
#include "transform.hpp"

void EditorCamera::Setup(Scene& scene) {
    Transform* transform        = scene.AddComponent<Transform>(*this);
    CameraMovement* camMovement = scene.AddComponent<CameraMovement>(*this);
    scene.AddSystem(CameraMovementSystem, SystemType::Physics);
}
