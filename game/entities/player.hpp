#ifndef GAME_COMPONENTS_PLAYER_HPP_
#define GAME_COMPONENTS_PLAYER_HPP_

#include "ecs/entity.hpp"

struct Player : public Entity {
 public:
    virtual void Setup(Scene& scene);
};

#endif  // GAME_COMPONENTS_PLAYER_HPP_
