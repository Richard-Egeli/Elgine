#pragma once

#include <iostream>
#include <vector>

#include "base.hpp"
#include "component-pool.hpp"
#include "component.hpp"

struct Scene;

typedef void (*System)(Scene& scene);

enum SystemType { Input, Update, Physics, Render };

struct SystemDesc {
    size_t dependents;
    System func;
};

struct Scene {
    std::vector<Base> entities;
    std::vector<ComponentPool*> components;

    std::vector<SystemDesc> input;
    std::vector<SystemDesc> update;
    std::vector<SystemDesc> physics;
    std::vector<SystemDesc> render;

    bool disabled;

    Scene() : disabled(false) {}

    void AddEntity(Base& entity) {
        for (int i = 0; i < entities.size(); i++) {
            if (entities[i].destroyed) {
                entity.id   = i;
                entities[i] = entity;
                return;
            }
        }

        entity.id = entities.size();
        entities.push_back(entity);
    }

    void DestroyEntity(Base& entity) {
        entities[entity.id].destroyed = true;
        entity.destroyed              = true;
    }

    Scene& AddSystem(System func, SystemType type) {
        std::vector<SystemDesc>* data;

        switch (type) {
            case SystemType::Input:
                data = &input;
                break;
            case SystemType::Update:
                data = &update;
                break;
            case SystemType::Physics:
                data = &physics;
                break;
            case SystemType::Render:
                data = &render;
                break;
        }

        for (int i = 0; i < data->size(); i++) {
            if (data->at(i).func == func) {
                data->at(i).dependents++;
                return *this;
            }
        }

        SystemDesc d;
        d.func       = func;
        d.dependents = 1;
        data->push_back(d);
        return *this;
    }

    template <typename T>
    T* AddComponent(Base& entity) {
        ComponentId componentId = Component::GetId<T>();

        if (componentId >= components.size()) {
            components.push_back(new ComponentPool(sizeof(T)));
        }

        T* component = new (components[componentId]->Get(entity.id)) T();
        entities[entity.id].mask.set(componentId);

        return component;
    }

    template <typename T>
    T* GetComponent(Base& entity) {
        ComponentId componentId = Component::GetId<T>();

        if (!entities[entity.id].mask.test(componentId)) return nullptr;

        T* component = static_cast<T*>(components[componentId]->Get(entity.id));
        return component;
    }

    template <typename T>
    void RemoveComponent(Base& entity) {
        ComponentId componentId = Component::GetId<T>();

        entities[entity.id].mask.reset(componentId);
    }
};
