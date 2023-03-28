#pragma once
#include <bitset>
#include <iostream>
#include <memory>

#include "math.hpp"
struct InputEvent {
    std::bitset<3> mask;

    float axis     = 0.0f;
    float strength = 0.02f;
    float interp   = 0.0f;

    bool Pressed() { return mask.test(0); }

    bool JustPressed() {
        if (mask.test(0) && !mask.test(1)) {
            mask.set(1);
            return true;
        }

        return false;
    }

    bool JustReleased() {
        if (!mask.test(0) && mask.test(1)) {
            mask.reset(1);
            return true;
        }

        return false;
    }

    void SetPressed(bool pressed) { (pressed) ? mask.set(0) : mask.reset(0); }

    void BlendValue() {
        // Somehow this interpolates correctly
        interp += Pressed() ? strength : -strength;
        interp = Math::Clamp(interp, 0.0, 1.0);
        axis   = (1.0 - Math::Pow(1.0 / (interp + 1.0), 2)) + 0.25 * interp;
    }
};
