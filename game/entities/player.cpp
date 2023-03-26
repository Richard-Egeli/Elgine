#include "player.hpp"

#include <iostream>

#include "asset-loader.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "time.hpp"
#include "transform.hpp"
#include "vertex.hpp"

void Player::Setup(Scene& scene) {
    //;
    scene.AddComponent<Transform>(*this);
    Mesh* mesh       = scene.AddComponent<Mesh>(*this);
    Texture* texture = AssetLoader::Load<Texture>("wall.jpg");

    std::array<Vertex, 65535> vertices = {
        Vertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
        Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
        Vertex(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
    };

    std::array<unsigned int, 6> indices = {
        // note that we start from 0!
        0,
        1,
        3,
        1,
        2,
        3,
    };

    mesh->SetMesh(vertices, indices);
    mesh->SetShader(SHADER_tutorial_vert, SHADER_tutorial_frag);
    mesh->SetTexture(texture);
}
