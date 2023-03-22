#ifndef ELGINE_GAME_GAMEMANAGER_HPP_
#define ELGINE_GAME_GAMEMANAGER_HPP_

#include <type_traits>

#include "entity.hpp"

class GameManager {
 public:
    static void Init();

    template <typename T>
    static T CreateEntity() {
        static_assert(std::is_base_of_v<Entity, T>, "Template not base of Entity");
        T entity;
        entity.Setup();

        return entity;
    }
};

#endif  // ELGINE_GAME_GAMEMANAGER_HPP_
