#include "gamemanager.hpp"

#include "elgine/components.hpp"
#include "elgine/elgine.hpp"
#include "elgine/opengl.hpp"
#include "elgine/shader-library.hpp"
#include "elgine/systems.hpp"
#include "elgine/utils.hpp"
#include "player.hpp"

void GameManager::Init() {
    Scene &scene = Elgine::CreateScene();

    // Create a player
    Player player = Entity::Create<Player>(scene);

    // Create a visual representation of the sun
    Entity sun                       = Entity::Create<Entity>(scene);
    TransformComponent *sunTransform = scene.AddComponent<TransformComponent>(sun);
    MeshComponent *sunMesh           = scene.AddComponent<MeshComponent>(sun);
    scene.AddComponent<SunComponent>(sun);
    sunTransform->SetPosition({5.f, 5.f, 3.f});
    sunMesh->SetShader(SHADER_sun_vert, SHADER_sun_frag);
    AssetLoader::LoadMesh("circle.fbx", sunMesh);

    // Create a camera
    Entity ent = Entity::Create<Entity>(scene);
    scene.AddComponent<CameraMovement>(ent);
    scene.AddComponent<TransformComponent>(ent);

    scene.AddSystem(MeshRendering, SystemType::Render)
        .AddSystem(CameraMovementSystem, SystemType::Physics)
        .AddSystem(SunMovementSystem, SystemType::Physics);
}
