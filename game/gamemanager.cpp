#include "gamemanager.hpp"

#include "elgine/elgine.hpp"
#include "elgine/systems.hpp"
#include "elgine/utils.hpp"
#include "player.hpp"

void GameManager::Init() {
    Scene& scene  = Elgine::CreateScene();
    Player player = Entity::Create<Player>(scene);

    scene.AddSystem(MeshRendering, SystemType::Render);
}
