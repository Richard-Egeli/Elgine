#include "player.hpp"

#include <iostream>

#include "physics_update.hpp"
#include "transform.hpp"

void Player::Setup(void) { AddComponent<Transform>(); }
