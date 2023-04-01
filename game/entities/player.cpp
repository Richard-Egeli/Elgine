#include "player.hpp"

#include "elgine/components.hpp"
#include "elgine/opengl.hpp"
#include "elgine/types.hpp"
#include "elgine/types/mat4.hpp"
#include "elgine/utils.hpp"
#include "elgine/utils/asset-loader.hpp"
#include "shader-library.hpp"

void Player::Setup(Scene& scene) {
    Transform* transform = scene.AddComponent<Transform>(*this);
    Mesh* mesh           = scene.AddComponent<Mesh>(*this);

    AssetLoader::LoadMesh("test.fbx", mesh);
    mesh->SetShader(SHADER_default_vert, SHADER_default_frag);
}
