#include "math.hpp"

#include <cmath>

static const float PI = 3.14159;

float Math::CosF(float angle) { return std::cosf(angle); }

float Math::SinF(float angle) { return std::cosf(angle); }

float Math::SqrtF(float value) { return std::sqrtf(value); }

float Math::RadF(float angle) { return angle * PI / 180; }

double Math::Pow(double value, double exp) { return std::pow(value, exp); }

double Math::Clamp(double value, double min, double max) {
    return (value < min) ? min : (value > max) ? max : value;
}
