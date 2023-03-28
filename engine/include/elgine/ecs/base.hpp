#pragma once

#include <bitset>

const unsigned char MAX_COMPONENTS = 32;
using EntityId                     = unsigned int;
using ComponentMask                = std::bitset<MAX_COMPONENTS>;

struct Base {
    EntityId id;
    ComponentMask mask;
    bool destroyed;
};
