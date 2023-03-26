#ifndef ELGINE_ENGINE_TYPES_COLOR_HPP_
#define ELGINE_ENGINE_TYPES_COLOR_HPP_

struct Color {
    float r;
    float g;
    float b;

    void SetColor(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

#endif  // ELGINE_ENGINE_TYPES_COLOR_HPP_
