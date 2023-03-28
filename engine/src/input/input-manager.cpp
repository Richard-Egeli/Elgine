#include "input-manager.hpp"

#include <SDL2/SDL_events.h>

#include <array>
#include <iostream>

#include "elgine.hpp"

static std::array<InputEvent, 256> Inputs;

void InputManager::EnableDefaultBindings() {
    //
    InputManager::Bind(InputEvent::Quit, SDLK_ESCAPE);
}

void InputManager::Bind(InputEvent event, InputKey key) {
    if (EventInvalid(event) || KeyInvalid(key)) return;

    Inputs[key] = event;
}

void InputManager::HandleMouseMotionEvents(SDL_MouseMotionEvent event) {}

void InputManager::HandleMouseButtonEvents(SDL_MouseButtonEvent event) {}

void InputManager::HandleMouseWheelEvents(SDL_MouseWheelEvent event) {}

void InputManager::HandleKeyboardEvents(SDL_KeyboardEvent event) {
    if (KeyInvalid(event.keysym.sym) || EventInvalid(Inputs[event.keysym.sym])) return;

    EventResponseHandler(Inputs[event.keysym.sym]);
}

bool InputManager::KeyInvalid(InputKey key) { return (key < 0 || key > 255); }

bool InputManager::EventInvalid(InputEvent event) {
    return (event == InputEvent::Invalid || event == InputEvent::Last);
}

void InputManager::EventResponseHandler(InputEvent event) {
    switch (event) {
        case InputEvent::Quit:
            Elgine::Stop();
            break;
        default:
            break;
    }
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
            case SDL_KEYDOWN:
                HandleKeyboardEvents(event.key);
                break;
        }
    }
}
