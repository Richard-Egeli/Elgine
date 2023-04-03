#include "player.hpp"

#include "btBulletDynamicsCommon.h"
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
    mesh->SetShader(SHADER_default_vert, SHADER_default_frag);
    AssetLoader::LoadMesh("test.fbx", mesh);
}
