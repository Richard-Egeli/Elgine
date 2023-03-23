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
            : index(index), componentMask(mask), all(all) {}

        Entity& operator*() const { return Scene::GetEntities()[index]; }

        bool operator==(const Iterator& other) const {
            return index == other.index || index == Scene::GetEntities().size();
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index && index != Scene::GetEntities().size();
        }

        bool ValidIndex() {
            ComponentMask mask = componentMask & Scene::GetEntities()[index].mask;
            bool destroyed     = Scene::GetEntities()[index].destroyed;
            bool result        = mask == componentMask && !destroyed;

            return result;
        }

        Iterator& operator++() {
            // Move the iterator forward
            do {
                index++;
            } while (index < Scene::GetEntities().size() && !ValidIndex());

            return *this;
        }

        EntityIndex index;
        ComponentMask componentMask;
        bool all{false};
    };

    const Iterator begin() const {
        size_t size    = Scene::GetEntities().size();
        int startIndex = 0;

        while (startIndex < size) {
            ComponentMask mask = componentMask & Scene::GetEntities()[startIndex].mask;
            bool destroyed     = Scene::GetEntities()[startIndex].destroyed;

            if (mask == componentMask && !destroyed) {
                break;
            }

            startIndex++;
        }

        return Iterator(startIndex, componentMask, all);
    }

    const Iterator end() const { return Iterator(Scene::GetEntities().size(), componentMask, all); }

    ComponentMask componentMask;
    bool all{false};
};

#endif  // ENGINE_ECS_SCENE_VIEW_HPP_
