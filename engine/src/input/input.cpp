#include "input.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

#include <array>
#include <iostream>

#include "elgine.hpp"
#include "input-event.hpp"
#include "input-key.hpp"

static std::array<InputEvent, InputKey::Last> InputKeyBinds;

void Input::Init() {
    InputKeyBinds[InputKey::MouseY].type = InputEventType::AxisOnly;
    InputKeyBinds[InputKey::MouseX].type = InputEventType::AxisOnly;
}

void Input::HandleMouseMotionEvents(SDL_MouseMotionEvent event) {
    InputKeyBinds[InputKey::MouseX].axis = -(float)event.xrel / 1000.f;
    InputKeyBinds[InputKey::MouseY].axis = -(float)event.yrel / 1000.f;
}

void Input::HandleMouseButtonEvents(SDL_MouseButtonEvent event, bool isPressed) {
    switch (SDL_BUTTON(event.button)) {
        case 1:
            InputKeyBinds[InputKey::MouseButtonLeft].SetPressed(isPressed);
            break;
        case 2:
            InputKeyBinds[InputKey::MouseButtonMiddle].SetPressed(isPressed);
            break;
        case 3:
            InputKeyBinds[InputKey::MouseButtonRight].SetPressed(isPressed);
            break;
    }
}

void Input::HandleMouseWheelEvents(SDL_MouseWheelEvent event) {}

void Input::HandleKeyboardEvents(SDL_KeyboardEvent event, bool isPressed) {
    InputKey key = KeyValid(event.keysym.sym);

    if (key != InputKey::Invalid) InputKeyBinds[key].SetPressed(isPressed);
}

InputKey Input::KeyValid(unsigned int key) {
    return (key < InputKey::Last) ? (InputKey)key : InputKey::Invalid;
}

bool Input::GetKey(InputKey key) { return InputKeyBinds[key].Pressed(); }

bool Input::GetKeyDown(InputKey key) { return InputKeyBinds[key].JustPressed(); }

bool Input::GetKeyUp(InputKey key) { return InputKeyBinds[key].JustReleased(); }

float Input::GetAxis(InputKey key) { return InputKeyBinds[key].axis; }

void Input::FixedAxisBlend() {
    for (auto& k : InputKeyBinds) k.FixedInterpAxis();
}

void Input::PollEvents() {
    // Updates JustPressed / JustReleased Flags
    for (auto& key : InputKeyBinds) key.UpdateEvent();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Elgine::Stop();
                break;
            case SDL_MOUSEWHEEL:
                HandleMouseWheelEvents(event.wheel);
                break;
            case SDL_MOUSEMOTION:
                HandleMouseMotionEvents(event.motion);
                break;
            case SDL_MOUSEBUTTONUP:
                HandleMouseButtonEvents(event.button, false);
                break;
            case SDL_MOUSEBUTTONDOWN:
                HandleMouseButtonEvents(event.button, true);
                break;
            case SDL_KEYUP:
                HandleKeyboardEvents(event.key, false);
                break;
            case SDL_KEYDOWN:
                HandleKeyboardEvents(event.key, true);
                break;
        }
    }
}
