#ifndef ENGINE_ECS_ENTITY_HPP_
#define ENGINE_ECS_ENTITY_HPP_

#include <bitset>

const int MAX_COMPONENTS = 64;
using EntityId           = unsigned long long int;
using EntityIndex        = unsigned int;
using EntityVersion      = unsigned int;
using EntityDestroy      = bool;
using ComponentMask      = std::bitset<MAX_COMPONENTS>;

struct Base {
    EntityId id;
    ComponentMask mask;
    EntityDestroy destroyed;
};

#endif  // ENGINE_ECS_ENTITY_HPP_
