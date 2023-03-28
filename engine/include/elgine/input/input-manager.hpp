#pragma once

#include "input-event.hpp"

class SDL_KeyboardEvent;
class SDL_MouseWheelEvent;
class SDL_MouseMotionEvent;
class SDL_MouseButtonEvent;

using InputKey = unsigned char;

class InputManager {
 public:
    static void PollEvents();

    static void Bind(InputEvent event, InputKey key);
    static void Unbind(InputKey key);
    static void EnableDefaultBindings(void);

 private:
    static bool KeyInvalid(InputKey key);
    static bool EventInvalid(InputEvent event);
    static void EventResponseHandler(InputEvent event);

    static void HandleMouseWheelEvents(SDL_MouseWheelEvent event);
    static void HandleMouseMotionEvents(SDL_MouseMotionEvent event);
    static void HandleMouseButtonEvents(SDL_MouseButtonEvent event);
    static void HandleKeyboardEvents(SDL_KeyboardEvent event);
};
