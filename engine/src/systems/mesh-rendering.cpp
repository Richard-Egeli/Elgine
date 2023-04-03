#include "mesh-rendering.hpp"

#include "camera.hpp"
#include "elgine/components.hpp"
#include "elgine/globals.hpp"
#include "opengl.hpp"
#include "quat.hpp"

void MeshRendering(Scene& scene) {
    for (auto& entity : SceneView<MeshComponent, TransformComponent>(scene)) {
        MeshComponent* mesh           = scene.GetComponent<MeshComponent>(entity);
        TransformComponent* transform = scene.GetComponent<TransformComponent>(entity);
        if (mesh == nullptr || !mesh->material.id) continue;

        mesh->material.Use();

        Vec3 direction = (Globals::SunPosition - transform->position);
        mesh->material.SetVec3("dirLight.direction", {-direction.x, -direction.y, -direction.z});
        mesh->material.SetVec3("sunPos", Globals::SunPosition);

        mesh->material.SetVec3("dirLight.diffuse", {0.9f, 0.9f, 0.9f});
        mesh->material.SetVec3("dirLight.ambient", {0.9f, 0.9f, 0.9f});
        mesh->material.SetVec3("dirLight.specular", {1.f, 1.f, 1.f});

        mesh->material.SetMat4("view", Camera::GetView());
        mesh->material.SetMat4("model", transform->matrices);
        mesh->material.SetMat4("projection", Camera::Projection);
        mesh->Draw();
    }
}
