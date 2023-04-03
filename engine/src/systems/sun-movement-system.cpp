#include "sun-movement-system.hpp"

#include "elgine/components.hpp"
#include "elgine/ecs.hpp"
#include "elgine/globals.hpp"
#include "elgine/utils.hpp"

void SunMovementSystem(Scene& scene) {
    for (auto& entity : SceneView<TransformComponent, SunComponent>(scene)) {
        TransformComponent* transform = scene.GetComponent<TransformComponent>(entity);

        float x = Math::Sin(Time::time * 0.5f) * 5.f;
        float z = Math::Cos(Time::time * 0.5f) * 5.f;

        Vec3 position = Vec3(x, 5.f, z);
        transform->SetPosition(position);

        Globals::SunPosition = position;
    }
}
