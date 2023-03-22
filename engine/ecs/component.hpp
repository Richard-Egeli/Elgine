#ifndef ENGINE_ECS_COMPONENT_HPP_
#define ENGINE_ECS_COMPONENT_HPP_

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

#endif  // ENGINE_ECS_COMPONENT_HPP_
