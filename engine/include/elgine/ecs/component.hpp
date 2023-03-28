#pragma once

#include <bitset>

using ComponentId = unsigned long long int;

static ComponentId componentIdCounter;

struct Component {
    ComponentId id;

    template <typename T>
    static ComponentId GetId() {
        static ComponentId id = componentIdCounter++;
        return id;
    }
};
