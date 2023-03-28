#include "camera-movement-system.hpp"

#include "camera-movement.hpp"
#include "scene-view.hpp"

void CameraMovementSystem(Scene& scene) {
    for (auto& e : SceneView<CameraMovement>(scene)) {
        CameraMovement* movement = scene.GetComponent<CameraMovement>(e);

        // Apply various inputs to movement
    }
}
