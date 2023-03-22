#ifndef ENGINE_ECS_ENTITY_HPP_
#define ENGINE_ECS_ENTITY_HPP_

#include <iostream>

#include "component.hpp"
#include "elgine.hpp"
#include "scene.hpp"

struct Entity {
 public:
    EntityId id;

    Entity() { this->id = Elgine::Scene.CreateEntity(); }

    virtual void Setup() = 0;

    template <typename T>
    void AddComponent() {
        Elgine::Scene.AddComponent<T>(this->id);
    };

    void AddSystem(System& system) { Elgine::Scene.AddSystem(system); }

    template <typename T>
    void RemoveComponent() {
        Elgine::Scene.RemoveComponent<T>(this->id);
    }

    template <typename T>
    void GetComponent() {
        Elgine::Scene.GetComponent<T>(this->id);
    }
};

#endif  // ENGINE_ECS_ENTITY_HPP_
