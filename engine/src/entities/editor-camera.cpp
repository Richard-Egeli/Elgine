#include "editor-camera.hpp"

#include "camera-movement-system.hpp"
#include "camera-movement.hpp"
#include "scene.hpp"
#include "transform-component.hpp"

void EditorCamera::Setup(Scene& scene) {
    TransformComponent* transform = scene.AddComponent<TransformComponent>(*this);
    CameraMovement* camMovement   = scene.AddComponent<CameraMovement>(*this);
    scene.AddSystem(CameraMovementSystem, SystemType::Physics);
}
