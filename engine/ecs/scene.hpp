#ifndef ENGINE_ECS_SCENE_HPP_
#define ENGINE_ECS_SCENE_HPP_

#include <bitset>
#include <iostream>
#include <vector>

#include "component-pool.hpp"
#include "component.hpp"

struct Scene;

typedef unsigned int EntityIndex;
typedef unsigned int EntityVersion;
typedef unsigned long long EntityId;

typedef void (*System)(Scene& scene);

inline EntityId CreateEntityId(EntityIndex index, EntityVersion version) {
    return ((EntityId)index << 32) | ((EntityId)version);
}

inline EntityIndex GetEntityIndex(EntityId id) { return id >> 32; }

inline EntityVersion GetEntityVersion(EntityId id) { return (EntityVersion)id; }

inline bool IsEntityValid(EntityId id) { return (id >> 32) != EntityIndex(-1); }

#define INVALID_ENTITY CreateEntityId(CreateIndex(-1), 0);

struct Scene {
    struct EntityDesc {
        EntityId id;
        ComponentMask mask;
    };

    std::vector<EntityDesc> entities;
    std::vector<System> systems;
    std::vector<ComponentPool*> componentPools;
    std::vector<EntityIndex> freeEntities;

    EntityId CreateEntity() {
        if (!freeEntities.empty()) {
            EntityIndex newIndex = freeEntities.back();
            freeEntities.pop_back();
            EntityId newId = CreateEntityId(newIndex, GetEntityVersion(entities[newIndex].id));
            entities[newIndex].id = newId;
            return entities[newIndex].id;
        }

        entities.push_back({entities.size(), ComponentMask()});
        return entities.back().id;
    };

    void DestroyEntity(EntityId id) {
        EntityId newId                  = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
        entities[GetEntityIndex(id)].id = newId;
        entities[GetEntityIndex(id)].mask.reset();
        freeEntities.push_back(GetEntityIndex(id));
    }

    void AddSystem(System& system) {
        for (int i = 0; i < systems.size(); i++) {
            if (&systems[i] == &system)
                return;
        }

        systems.push_back(system);
    }

    void RunSystem() {
        for (auto sys : systems) sys(*this);
    }

    template <typename T>
    void RemoveComponent(EntityId id) {
        if (entities[GetEntityIndex(id)].id != id)
            return;

        int componentId = Component::GetId<T>();
        entities[GetEntityIndex(id)].mask.reset(componentId);
    }

    template <typename T>
    T* AddComponent(EntityId id) {
        int componentId = Component::GetId<T>();

        if (componentPools.size() <= componentId) {
            componentPools.resize(componentId + 1, nullptr);
        }

        if (componentPools[componentId] == nullptr) {
            componentPools[componentId] = new ComponentPool(sizeof(T));
        }

        T* pComponent = new (componentPools[componentId]->get(id)) T();
        entities[id].mask.set(componentId);
        return nullptr;
    }

    template <typename T>
    T* GetComponent(EntityId id) {
        int componentId = Component::GetId<T>();

        if (entities[id].mask.test(componentId))
            return nullptr;

        T* comp = static_cast<T*>(componentPools[componentId]->get(id));
        return comp;
    }
};

#endif  // ENGINE_ECS_ENTITY_HPP_
