#include "player.hpp"

#include "elgine/components.hpp"
#include "elgine/opengl.hpp"
#include "elgine/shader-library.hpp"
#include "elgine/types.hpp"
#include "elgine/types/mat4.hpp"
#include "elgine/utils.hpp"
#include "elgine/utils/asset-loader.hpp"

void Player::Setup(Scene& scene) {
    TransformComponent* transform = scene.AddComponent<TransformComponent>(*this);
    MeshComponent* mesh           = scene.AddComponent<MeshComponent>(*this);
    AssetLoader::LoadMesh("test.fbx", mesh);

    // Texture texture = AssetLoader::Load<Texture>("container.png");
    // mesh->SetTexture(texture, "material.diffuse", 0);

    mesh->material.SetVec3("material.diffuse", {0.9f, 0.9f, 0.9f});
    mesh->material.SetVec3("material.specular", {0.5f, 0.5f, 0.5f});
    mesh->material.SetFloat("material.shininess", 64.0f);

    // transform->Rotate(0.f, {1.f, 0.f, 0.f});
    mesh->SetShader(SHADER_default_vert, SHADER_default_frag);

    std::cout << "Player setup" << std::endl;
}
