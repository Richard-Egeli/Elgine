#include "gamemanager.hpp"

#include <iostream>

#include "ecs.hpp"
#include "elgine.hpp"
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

void GameManager::Init() {
    Entity player = Scene::CreateEntity();
    Scene::AddComponent<Transform>(player);
    Scene::AddComponent<Health>(player);
    Scene::AddComponent<Damage>(player);

    Entity ai = Scene::CreateEntity();
    // Scene::AddComponent<Health>(ai);
    Scene::AddComponent<Transform>(ai);

    Entity ei = Scene::CreateEntity();
    Scene::AddComponent<Transform>(ei);
    Scene::AddComponent<Health>(ei);

    Elgine::Render      = Render;
    Elgine::FixedUpdate = FixedUpdate;
    Elgine::Update      = Update;
    Elgine::Start       = Start;

    std::cout << "Before Loop\n";

    for (Entity& e : SceneView<Transform, Health>()) {
        std::cout << e.id << " Hello!\n";
    }

    for (auto& e : SceneView<>()) {
        std::cout << e.id << " ALL\n";
    }
}

void GameManager::Start() {}

void GameManager::Update() {}

void GameManager::FixedUpdate() {}

void GameManager::Render() {}
