#ifndef ENGINE_ECS_COMPONENT_HPP_
#define ENGINE_ECS_COMPONENT_HPP_

#include <bitset>
#include <cstddef>

const size_t MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

struct Component {
    int id;

 public:
    template <class T>
    static int GetId();

    Component() { this->id = GetId<Component>(); }
};

static int componentCounter;
template <class T>
int Component::GetId() {
    static int componentId = componentCounter++;
    return componentId;
}

#endif  // ENGINE_ECS_COMPONENT_HPP_
