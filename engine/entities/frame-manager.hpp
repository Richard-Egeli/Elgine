#ifndef ELGINE_ENGINE_ENTITIES_FRAME_MANAGER_HPP_
#define ELGINE_ENGINE_ENTITIES_FRAME_MANAGER_HPP_

#include "entity.hpp"

struct FrameManager : public Entity {
 public:
    virtual void Setup(Scene& scene);
};

#endif  // ELGINE_ENGINE_ENTITIES_FRAME_MANAGER_HPP_
