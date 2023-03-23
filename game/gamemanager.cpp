#include "gamemanager.hpp"

#include <iostream>

#include "elgine.hpp"
#include "player.hpp"
#include "time.hpp"

struct Transform {
    float x;
};

struct Health {
    float health;
};

struct Damage {
    float damage;
};

struct UpdateComponent {};

void GameManager::Init() {
    Scene& scene  = Elgine::CreateScene();
    Player player = Entity::Create<Player>(scene);

    scene.AddComponent<Transform>(player);
    scene.AddComponent<Health>(player);
    scene.AddComponent<UpdateComponent>(player);

    Player ei = Entity::Create<Player>(scene);
    scene.AddComponent<Health>(ei);
    scene.AddComponent<Transform>(ei);
}
