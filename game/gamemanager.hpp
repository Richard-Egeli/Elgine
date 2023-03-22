#ifndef ELGINE_GAME_GAMEMANAGER_HPP_
#define ELGINE_GAME_GAMEMANAGER_HPP_

#include <type_traits>

#include "entity.hpp"

class GameManager {
 public:
    static void Init();

    static void Start();

    static void Update();

    static void FixedUpdate();

    static void Render();
};

#endif  // ELGINE_GAME_GAMEMANAGER_HPP_
