#pragma once

#include <iostream>

#include "scene.hpp"

template <typename... ComponentTypes>
struct SceneView {
    SceneView(Scene& scene) : scene(&scene) {
        if (sizeof...(ComponentTypes) == 0) {
            all = true;
        } else {
            ComponentId componentIds[] = {0, Component::GetId<ComponentTypes>()...};

            for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++) {
                componentMask.set(componentIds[i]);
            }
        }
    }

    struct Iterator {
        Iterator(Scene* scene, EntityIndex index, ComponentMask mask, bool all)
            : scene(scene), index(index), componentMask(mask), all(all) {}

        Base& operator*() const { return scene->entities[index]; }

        bool operator==(const Iterator& other) const {
            return index == other.index || index == scene->entities.size();
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index && index != scene->entities.size();
        }

        bool ValidIndex() {
            ComponentMask mask = componentMask & scene->entities[index].mask;
            bool destroyed     = scene->entities[index].destroyed;
            bool result        = mask == componentMask && !destroyed;

            return result;
        }

        Iterator& operator++() {
            // Move the iterator forward
            do {
                index++;
            } while (index < scene->entities.size() && !ValidIndex());

            return *this;
        }

        EntityIndex index;
        ComponentMask componentMask;
        bool all{false};
        Scene* scene;
    };

    const Iterator begin() const {
        size_t size    = scene->entities.size();
        int startIndex = 0;

        while (startIndex < size) {
            ComponentMask mask = componentMask & scene->entities[startIndex].mask;
            bool destroyed     = scene->entities[startIndex].destroyed;

            if (mask == componentMask && !destroyed) {
                break;
            }

            startIndex++;
        }

        return Iterator(scene, startIndex, componentMask, all);
    }

    const Iterator end() const {
        return Iterator(scene, scene->entities.size(), componentMask, all);
    }

    ComponentMask componentMask;
    bool all{false};
    Scene* scene;
};
