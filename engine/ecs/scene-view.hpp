#ifndef ENGINE_ECS_SCENE_VIEW_HPP_
#define ENGINE_ECS_SCENE_VIEW_HPP_

#include <iostream>

#include "entity.hpp"
#include "scene.hpp"

template <typename... ComponentTypes>
struct SceneView {
    SceneView() {
        if (sizeof...(ComponentTypes) == 0) {
            all = true;
        } else {
            // Unpack the template parameters into an initializer list
            ComponentId componentIds[] = {0, Component::GetId<ComponentTypes>()...};

            for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++) {
                componentMask.set(componentIds[i]);
            }
        }
    }

    struct Iterator {
        Iterator(EntityIndex index, ComponentMask mask, bool all)
            : index(index), mask(mask), all(all) {}

        Entity* operator*() const { return &Scene::GetEntities()[index]; }

        bool operator==(const Iterator& other) const {
            return index == other.index || index == Scene::GetEntities().size();
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index && index != Scene::GetEntities().size();
        }

        bool ValidIndex() {
            return
                // It has the correct component mask
                (all || mask == (mask & Scene::GetEntities()[index].mask));
        }

        Iterator& operator++() {
            // Move the iterator forward
            do {
                index++;
            } while (index < Scene::GetEntities().size() && !ValidIndex() &&
                     Scene::GetEntities()[index].destroyed);
            return *this;
        }

        EntityIndex index;
        ComponentMask mask;
        bool all{false};
    };

    const Iterator begin() const {
        int firstIndex = 0;
        size_t size    = Scene::GetEntities().size();

        while (firstIndex < size) {
            ComponentMask mask = componentMask & Scene::GetEntities()[firstIndex].mask;
            bool destroyed     = Scene::GetEntities()[firstIndex].destroyed;
            if (mask == componentMask && !destroyed) {
                break;
            }

            firstIndex++;
        }

        return Iterator(firstIndex, componentMask, all);
    }

    const Iterator end() const {
        return Iterator(EntityIndex(Scene::GetEntities().size()), componentMask, all);
    }

    ComponentMask componentMask;
    bool all{false};
};

#endif  // ENGINE_ECS_SCENE_VIEW_HPP_
