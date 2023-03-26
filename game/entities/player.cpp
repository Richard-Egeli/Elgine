#include "player.hpp"

#include <iostream>

#include "elgine/components.hpp"
#include "elgine/types.hpp"
#include "elgine/utils.hpp"
#include "shaders.hpp"

void Player::Setup(Scene& scene) {
    //;
    scene.AddComponent<Transform>(*this);
    Mesh* mesh      = scene.AddComponent<Mesh>(*this);
    Texture texture = AssetLoader::Load<Texture>("wall.jpg");
    Texture awesome = AssetLoader::Load<Texture>("awesomeface.png");

    std::vector<Vertex> vertices = {
        Vertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
        Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
        Vertex(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
    };

    std::vector<unsigned int> indices = {
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
    mesh->SetTexture(texture, 0);
    mesh->SetTexture(awesome, 1);
}
