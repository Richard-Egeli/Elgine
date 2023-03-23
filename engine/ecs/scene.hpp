#ifndef ENGINE_ECS_SCENE_HPP_
#define ENGINE_ECS_SCENE_HPP_

#include <iostream>
#include <vector>

#include "component.hpp"
#include "entity.hpp"
#include "pool.hpp"

static std::vector<Entity> entities;
static std::vector<Pool*> components;

struct Scene {
    static std::vector<Entity>& GetEntities() { return entities; }

    static Entity CreateEntity() {
        Entity entity;
        for (int i = 0; i < entities.size(); i++) {
            if (entities[i].destroyed) {
                entity.id   = i;
                entities[i] = entity;
                return entities[i];
            }
        }

        entity.id = entities.size();
        entities.push_back(entity);

        return entities.back();
    }

    static void DestroyEntity(Entity& entity) {
        entities[entity.id].destroyed = true;
        entity.destroyed              = true;
    }

    template <typename T>
    static T* AddComponent(Entity& entity) {
        ComponentId componentId = Component::GetId<T>();

        if (componentId >= components.size()) {
            components.push_back(new Pool(sizeof(T)));
        }

        T* component = new (components[componentId]->Get(entity.id)) T();
        entities[entity.id].mask.set(componentId);

        return component;
    }

    template <typename T>
    static void RemoveComponent(Entity& entity) {
        ComponentId componentId = Component::GetId<T>();

        entities[entity.id].mask.reset(componentId);
    }
};

#endif  // ENGINE_ECS_SCENE_HPP_
