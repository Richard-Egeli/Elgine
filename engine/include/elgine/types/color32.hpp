#pragma once

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
