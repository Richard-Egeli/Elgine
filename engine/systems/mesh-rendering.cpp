#include "mesh-rendering.hpp"

#include <algorithm>
#include <iostream>

#include "mesh.hpp"
#include "opengl.hpp"
#include "quat.hpp"
#include "transform.hpp"
#include "vec3.hpp"

static bool direction;
void MeshRendering(Scene& scene) {
    for (auto& entity : SceneView<Mesh, Transform>(scene)) {
        Mesh* mesh           = scene.GetComponent<Mesh>(entity);
        Transform* transform = scene.GetComponent<Transform>(entity);

        if (mesh == nullptr || !mesh->shader.id) continue;

        glUseProgram(mesh->shader.id);

        for (int i = 0; i < mesh->textures.size(); i++) {
            if (mesh->textures[i] != 0) {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, mesh->textures[i]);
            }
        }

        if (transform->position.x > 1.f)
            direction = true;
        else if (transform->position.x < -1.f)
            direction = false;

        float horMove = (direction) ? -0.01f : 0.01f;
        static float dir;
        dir += horMove;

        transform->position.Print();
        transform->Translate({horMove, 0.0f, 0.0f});

        // push the updated matrix data to the shader
        unsigned int transformLoc = glGetUniformLocation(mesh->shader.id, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform->matrices.Value());

        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
