#include "gamemanager.hpp"

#include "elgine/components.hpp"
#include "elgine/ecs/component.hpp"
#include "elgine/elgine.hpp"
#include "elgine/entities/plane.hpp"
#include "elgine/systems/camera-movement-system.hpp"
#include "elgine/utils.hpp"
#include "player.hpp"

void GameManager::Init() {
    Scene& scene  = Elgine::CreateScene();
    Player player = Entity::Create<Player>(scene);
    Plane plane   = Entity::Create<Plane>(scene);

    Entity ent = Entity::Create<Entity>(scene);
    scene.AddComponent<CameraMovement>(ent);
    scene.AddComponent<Transform>(ent);

    scene.AddSystem(MeshRendering, SystemType::Render);
    scene.AddSystem(CameraMovementSystem, SystemType::Physics);
}
