#pragma once
#include <bitset>
#include <iostream>
#include <memory>

#include "math.hpp"

enum InputEventType {
    ClickAndAxis,
    ClickOnly,
    AxisOnly,
};

struct InputEvent {
    std::bitset<2> mask;

    float axis          = 0.0f;
    float strength      = 0.04f;
    float interp        = 0.0f;
    InputEventType type = InputEventType::ClickAndAxis;

    bool Pressed() { return mask.test(0); }

    bool JustPressed() { return mask.test(0) && !mask.test(1); }

    bool JustReleased() { return !mask.test(0) && mask.test(1); }

    void SetPressed(bool pressed) {
        if (type != InputEventType::AxisOnly) mask.test(0) ? mask.set(1) : mask.reset(1);
        pressed ? mask.set(0) : mask.reset(0);
    }

    /** A method that updates the flags for JustPressed & JustReleased at the end of each gameloop
     */
    void UpdateEvent() {
        switch (type) {
            case InputEventType::AxisOnly:
                axis = 0.0f;
                break;
            default:
                mask.test(0) ? mask.set(1) : mask.reset(1);
                break;
        }
    }

    void FixedInterpAxis() {
        // Somehow this interpolates correctly
        if (type == InputEventType::ClickAndAxis) {
            interp += Pressed() ? strength : -strength;
            interp = Math::Clamp(interp, 0.0, 1.0);
            axis   = (1.0 - Math::Pow(1.0 / (interp + 1.0), 2)) + 0.25 * interp;
        }
    }
};
