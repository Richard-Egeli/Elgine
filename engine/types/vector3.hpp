#ifndef ELGINE_ENGINE_TYPES_VECTOR3_HPP_
#define ELGINE_ENGINE_TYPES_VECTOR3_HPP_

struct Vector3 {
    float x;
    float y;
    float z;

    void SetPosition(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

#endif  // ELGINE_ENGINE_TYPES_VECTOR3_HPP_
