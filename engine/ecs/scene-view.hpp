#ifndef ENGINE_ECS_SCENE_VIEW_HPP_
#define ENGINE_ECS_SCENE_VIEW_HPP_

#include "scene.hpp"

template <typename... ComponentTypes>
struct SceneView {
    SceneView(Scene& scene) : scene(&scene) {
        if (sizeof...(ComponentTypes) == 0) {
            all = true;
        } else {
            // Unpack the template parameters into an initializer list
            int componentIds[] = {0, Component::GetId<ComponentTypes>()...};
            for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
                componentMask.set(componentIds[i]);
        }
    }

    struct Iterator {
        Iterator(Scene* scene, EntityIndex index, ComponentMask mask, bool all)
            : scene(scene), index(index), mask(mask), all(all) {}

        EntityId operator*() const { return scene->entities[index].id; }

        bool operator==(const Iterator& other) const {
            return index == other.index || index == scene->entities.size();
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index && index != scene->entities.size();
        }

        bool ValidIndex() {
            return
                // It's a valid entity ID
                IsEntityValid(scene->entities[index].id) &&
                // It has the correct component mask
                (all || mask == (mask & scene->entities[index].mask));
        }

        Iterator& operator++() {
            // Move the iterator forward
            do {
                index++;
            } while (index < scene->entities.size() && !ValidIndex());
            return *this;
        }

        EntityIndex index;
        Scene* scene;
        ComponentMask mask;
        bool all{false};
    };

    const Iterator begin() const {
        int firstIndex = 0;
        while (firstIndex < scene->entities.size() &&
               (componentMask != (componentMask & scene->entities[firstIndex].mask) ||
                !IsEntityValid(scene->entities[firstIndex].id))) {
            firstIndex++;
        }
        return Iterator(scene, firstIndex, componentMask, all);
    }

    const Iterator end() const {
        return Iterator(scene, EntityIndex(scene->entities.size()), componentMask, all);
    }

    Scene* scene{nullptr};
    ComponentMask componentMask;
    bool all{false};
};

#endif  // ENGINE_ECS_SCENE_VIEW_HPP_
