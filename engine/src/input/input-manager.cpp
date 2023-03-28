#include "input-manager.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

#include <array>
#include <iostream>

#include "elgine.hpp"
#include "input-event.hpp"
#include "input-key.hpp"

static std::array<InputEvent, InputKey::Last> InputKeyBinds = {InputKey::Invalid};

void InputManager::HandleMouseMotionEvents(SDL_MouseMotionEvent event) {}

void InputManager::HandleMouseButtonEvents(SDL_MouseButtonEvent event) {}

void InputManager::HandleMouseWheelEvents(SDL_MouseWheelEvent event) {}

void InputManager::HandleKeyboardEvents(SDL_KeyboardEvent event, bool isPressed) {
    InputKey key = KeyValid(event.keysym.sym);

    if (key != InputKey::Invalid) {
        InputKeyBinds[key].SetPressed(isPressed);
    }
}

InputKey InputManager::KeyValid(int key) {
    return (key > 0 && key < InputKey::Last) ? (InputKey)key : InputKey::Invalid;
}

bool InputManager::GetKeyDown(InputKey key) { return InputKeyBinds[key].JustPressed(); }

bool InputManager::GetKeyUp(InputKey key) { return InputKeyBinds[key].JustReleased(); }

float InputManager::GetAxis(InputKey key) { return InputKeyBinds[key].axis; }

void InputManager::UpdateAxisValues() {
    for (auto& k : InputKeyBinds) k.BlendValue();
}

void InputManager::PollEvents() {
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
            case SDL_MOUSEBUTTONDOWN:
                HandleMouseButtonEvents(event.button);
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
