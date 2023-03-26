#ifndef ELGINE_ENGINE_TYPES_VECTOR2_HPP_
#define ELGINE_ENGINE_TYPES_VECTOR2_HPP_

struct Vector2 {
    float x;
    float y;

    void SetPosition(float x, float y) {
        this->x = x;
        this->y = y;
    }
};

#endif  // ELGINE_ENGINE_TYPES_VECTOR2_HPP_
