#include "player.hpp"

#include "elgine/components.hpp"
#include "elgine/default-shader.hpp"
#include "elgine/opengl.hpp"
#include "elgine/types.hpp"
#include "elgine/types/mat4.hpp"
#include "elgine/utils.hpp"
#include "elgine/utils/asset-loader.hpp"
#include "shader-library.hpp"

void Player::Setup(Scene& scene) {
    Transform* transform = scene.AddComponent<Transform>(*this);
    Mesh* mesh           = scene.AddComponent<Mesh>(*this);
    // Texture texture      = AssetLoader::Load<Texture>("wall.jpg");
    // Texture awesome      = AssetLoader::Load<Texture>("awesomeface.png");

    // transform->Rotate(-45, {1.0, 0.0, 0.0});

    // std::vector<Vertex> vertices = {
    //     Vertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
    //     Vertex(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
    //     Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
    //     Vertex(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
    // };
    //
    // std::vector<Triangle> indices = {Triangle(0, 1, 3), Triangle(1, 2, 3)};

    // mesh->SetMesh(vertices, indices);
    AssetLoader::LoadMesh("test.fbx", mesh);
    std::cout << "AFTER SET SHADER " << glGetError() << std::endl;
    mesh->SetShader(SHADER_default_vert, SHADER_default_frag);

    std::cout << "AFTER SET SHADER " << glGetError() << std::endl;
    // mesh->SetTexture(texture, 0);
    // mesh->SetTexture(awesome, 1);
}
