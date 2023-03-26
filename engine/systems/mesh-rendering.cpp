#include "mesh-rendering.hpp"

#include <iostream>

#include "mesh.hpp"
#include "opengl.hpp"
#include "scene-view.hpp"
#include "transform.hpp"

void MeshRendering(Scene& scene) {
    for (auto& entity : SceneView<Mesh, Transform>(scene)) {
        Mesh* mesh = scene.GetComponent<Mesh>(entity);

        if (mesh == nullptr) continue;

        glUseProgram(mesh->shaderProgram);

        if (mesh->texture) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mesh->texture->id);
        }

        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
