#include "quat.hpp"

#include <iostream>

#include "math.hpp"

Quat Quat::Normalize() {
    const float n = 1 / Math::Sqrt(x * x + y * y + z * z + w * w);
    return Quat(w * n, x * n, y * n, z * n);
}

void Quat::Print() {
    std::cout << "w: " << w << ", x: " << x << ", y: " << y << ", z: " << z << std::endl;
}
