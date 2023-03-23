#ifndef ENGINE_ECS_COMPONENT_POOL_HPP_
#define ENGINE_ECS_COMPONENT_POOL_HPP_

#include <cstddef>
#include <cstring>
#include <iostream>

#include "base.hpp"

struct ComponentPool {
    char* data{nullptr};
    size_t elementSize{0};
    size_t length;

    ComponentPool(size_t elementSize) {
        this->elementSize = elementSize;
        this->data        = new char[elementSize * MAX_COMPONENTS];
    }

    ~ComponentPool() { delete[] this->data; }

    inline void* Get(size_t index) { return this->data + index * this->elementSize; }
};

#endif  // ENGINE_ECS_COMPONENT_POOL_HPP_
