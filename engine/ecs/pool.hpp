#ifndef ENGINE_ECS_POOL_HPP_
#define ENGINE_ECS_POOL_HPP_

#include <cstddef>
#include <cstring>
#include <iostream>

#include "entity.hpp"

struct Pool {
    char* data{nullptr};
    size_t elementSize{0};

    Pool(size_t elementSize) {
        this->elementSize = elementSize;
        this->data        = new char[elementSize * MAX_COMPONENTS];
    }

    ~Pool() { delete[] this->data; }

    inline void* Get(size_t index) { return this->data + index * this->elementSize; }
};

#endif  // ENGINE_ECS_POOL_HPP_
