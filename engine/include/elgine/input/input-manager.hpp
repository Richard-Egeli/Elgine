#pragma once

#include "input-event.hpp"
#include "input-key.hpp"

class SDL_KeyboardEvent;
class SDL_MouseWheelEvent;
class SDL_MouseMotionEvent;
class SDL_MouseButtonEvent;

class InputManager {
 public:
    friend class Elgine;

    static bool GetKeyDown(InputKey key);
    static bool GetKeyUp(InputKey key);
    static bool GetKey(InputKey key);
    static float GetAxis(InputKey key);

 private:
    static void PollEvents();
    static void UpdateAxisValues();
    static InputKey KeyValid(int key);

    static void EventResponseHandler(InputKey event);
    static void HandleMouseWheelEvents(SDL_MouseWheelEvent event);
    static void HandleMouseMotionEvents(SDL_MouseMotionEvent event);
    static void HandleMouseButtonEvents(SDL_MouseButtonEvent event);
    static void HandleKeyboardEvents(SDL_KeyboardEvent event, bool isPressed);
};
