#include "gamemanager.hpp"

#include "elgine.hpp"
#include "mesh-rendering.hpp"
#include "mesh.hpp"
#include "player.hpp"
#include "time.hpp"
#include "transform.hpp"

void GameManager::Init() {
    Scene& scene  = Elgine::CreateScene();
    Player player = Entity::Create<Player>(scene);

    scene.AddSystem(MeshRendering, SystemType::Render);
}
