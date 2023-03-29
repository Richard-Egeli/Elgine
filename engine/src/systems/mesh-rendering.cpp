#include "mesh-rendering.hpp"

#include "camera.hpp"
#include "mesh.hpp"
#include "opengl.hpp"
#include "quat.hpp"
#include "transform.hpp"

void MeshRendering(Scene& scene) {
    for (auto& entity : SceneView<Mesh, Transform>(scene)) {
        Mesh* mesh           = scene.GetComponent<Mesh>(entity);
        Transform* transform = scene.GetComponent<Transform>(entity);
        if (mesh == nullptr || !mesh->shader.id) continue;

        mesh->shader.Use();
        for (int i = 0; i < mesh->textures.size(); i++) {
            if (mesh->textures[i] != 0) {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, mesh->textures[i]);
            }
        }

        mesh->shader.SetMat4("view", Camera::GetView());
        mesh->shader.SetMat4("model", transform->matrices);
        mesh->shader.SetMat4("projection", Camera::Projection);
        mesh->Draw();
    }
}
