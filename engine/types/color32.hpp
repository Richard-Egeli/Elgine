#ifndef ELGINE_ENGINE_TYPES_COLOR32_HPP_
#define ELGINE_ENGINE_TYPES_COLOR32_HPP_

struct Color32 {
    float r;
    float g;
    float b;
    float a;

    void SetColor(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

#endif  // ELGINE_ENGINE_TYPES_COLOR32_HPP_
