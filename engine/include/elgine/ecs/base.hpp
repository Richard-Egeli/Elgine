#pragma once

#include <bitset>

const int MAX_COMPONENTS = 64;
using EntityId           = unsigned int;
using EntityIndex        = unsigned int;
using ComponentMask      = std::bitset<MAX_COMPONENTS>;

struct Base {
    EntityId id;
    ComponentMask mask;
    bool destroyed;
};
