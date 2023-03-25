#include "mesh-rendering.hpp"

#include <OpenGL/OpenGL.h>

#include <iostream>

#include "mesh.hpp"
#include "scene-view.hpp"
#include "transform.hpp"

void MeshRendering(Scene& scene) {
    for (auto& entity : SceneView<Mesh, Transform>(scene)) {
        Mesh* mesh = scene.GetComponent<Mesh>(entity);

        if (mesh == nullptr) continue;

        glUseProgram(mesh->shaderProgram);
        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
