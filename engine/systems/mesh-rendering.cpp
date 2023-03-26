#include "mesh-rendering.hpp"

#include <iostream>

#include "mesh.hpp"
#include "opengl.hpp"
#include "scene-view.hpp"
#include "transform.hpp"

void MeshRendering(Scene& scene) {
    for (auto& entity : SceneView<Mesh, Transform>(scene)) {
        Mesh* mesh = scene.GetComponent<Mesh>(entity);

        if (mesh == nullptr || !mesh->shader.id) continue;

        glUseProgram(mesh->shader.id);

        for (int i = 0; i < mesh->textures.size(); i++) {
            if (mesh->textures[i] != 0) {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, mesh->textures[i]);
            }
        }

        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
