#include "player.hpp"

#include <../lib/glm/glm.hpp>
#include <../lib/glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "elgine/components.hpp"
#include "elgine/opengl.hpp"
#include "elgine/types.hpp"
#include "elgine/utils.hpp"
#include "shaders.hpp"

void Player::Setup(Scene& scene) {
    Transform* transform = scene.AddComponent<Transform>(*this);
    Mesh* mesh           = scene.AddComponent<Mesh>(*this);
    Texture texture      = AssetLoader::Load<Texture>("wall.jpg");
    Texture awesome      = AssetLoader::Load<Texture>("awesomeface.png");

    std::vector<Vertex> vertices = {
        Vertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
        Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
        Vertex(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
    };

    std::vector<unsigned int> indices = {
        0,
        1,
        3,
        1,
        2,
        3,
    };

    mesh->SetMesh(vertices, indices);
    mesh->SetShader(SHADER_tutorial_vert, SHADER_tutorial_frag);
    mesh->SetTexture(texture, 0);
    mesh->SetTexture(awesome, 1);

    // transform->Translate(Vec3(0.3f, 0.2f, 0.1f));
    // transform->Rotate(70.f, Vec3(0.f, 1.f, 0.f));

    unsigned int transformLoc = glGetUniformLocation(mesh->shader.id, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform->matrices.data);
}
