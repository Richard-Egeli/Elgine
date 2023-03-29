#include "math.hpp"

#include <cmath>

static const double PI = 3.14159;

double Math::Cos(double angle) { return std::cos(angle); }

double Math::Sin(double angle) { return std::sin(angle); }

float Math::SqrtF(float value) { return std::sqrtf(value); }

float Math::RadF(float angle) { return angle * PI / 180; }

double Math::Pow(double value, double exp) { return std::pow(value, exp); }

double Math::Clamp(double value, double min, double max) {
    return (value < min) ? min : (value > max) ? max : value;
}
