#ifndef GAME_COMPONENTS_PLAYER_HPP_
#define GAME_COMPONENTS_PLAYER_HPP_

#include "elgine/ecs.hpp"

struct Player : public Entity {
 public:
    virtual void Setup(Scene& scene);
};

#endif  // GAME_COMPONENTS_PLAYER_HPP_
