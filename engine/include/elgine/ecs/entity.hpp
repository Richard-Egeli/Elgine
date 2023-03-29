#pragma once

#include <type_traits>

#include "scene.hpp"

struct Entity : public Base {
    template <typename T>
    static T Create(Scene& scene) {
        static_assert(std::is_base_of<Entity, T>::value, "Type is not base of Entity");

        T entity;
        scene.AddEntity(entity);
        entity.Setup(scene);

        return entity;
    }

    virtual void Setup(Scene& scene){};
};
