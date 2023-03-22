#include "gamemanager.hpp"

#include <iostream>

#include "player.hpp"

void GameManager::Init() {
    std::cout << "Player Created\n";
    Player player = GameManager::CreateEntity<Player>();
    Player p2     = GameManager::CreateEntity<Player>();
}
