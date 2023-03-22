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

void GameManager::Init() {
    Entity* player = Scene::CreateEntity();
    Scene::AddComponent<Transform>(player);
    Scene::AddComponent<Health>(player);

    Elgine::Render      = Render;
    Elgine::FixedUpdate = FixedUpdate;
    Elgine::Update      = Update;
    Elgine::Start       = Start;

    for (Entity* e : SceneView<Transform, Health>()) {
        std::cout << "Hello!\n";
    }

    for (Entity* e : SceneView<>()) {
        std::cout << e->id << " All\n";
    }
}

void GameManager::Start() {}

void GameManager::Update() {}

void GameManager::FixedUpdate() {}

void GameManager::Render() {}
