#include "elgine.hpp"

#include <OpenGL/OpenGL.h>
#include <SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <string>

#include "debug.hpp"
#include "elgine/input/input-manager.hpp"
#include "elgine/systems/mesh-rendering.hpp"
#include "time.hpp"

std::vector<Scene> Elgine::Scenes;
bool Elgine::isRunning;

SDL_Window* Elgine::Window;
static SDL_GLContext Context;

void Elgine::Stop() { isRunning = false; }

Elgine::Elgine() {
    isRunning = true;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    Window = SDL_CreateWindow("Elgine",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800,
                              600,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (Debug::CheckNull(Window, "Window is NULL!")) return;

    Context = SDL_GL_CreateContext(Window);

    if (Context == nullptr) {
        std::cout << "Failed to create OpenGL Context: " << SDL_GetError() << "\n";
    }

    SDL_GL_MakeCurrent(Window, Context);

    std::string err = SDL_GetError();
    if (err.length() > 0) {
        std::cout << RED << "SDL2 ERROR: " << err << NOR << std::endl;
    }

    Debug::Log("SDL2 Initialized!");
    InputManager::EnableDefaultBindings();
    SDL_GL_SetSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
}

Elgine::~Elgine() {}

void Elgine::GameLoop() {
    double t  = 0.0;
    double dt = 1.0 / 60.0;

    double currentTime = SDL_GetTicks64() / 1000.0;
    double accumulator = 0.0;

    while (isRunning) {
        // Dev Inputs
        // Input();

        double newTime   = SDL_GetTicks64() / 1000.0;
        double frameTime = newTime - currentTime;

        if (frameTime > 0.25) frameTime = 0.25;

        currentTime = newTime;
        accumulator += frameTime;

        FPSTick();

        for (Scene& scene : Scenes) {
            if (scene.disabled) continue;

            for (auto system : scene.update) system.func(scene);
        }

        while (accumulator >= dt) {
            FixedFPSTick();

            for (Scene& scene : Scenes) {
                if (scene.disabled) continue;

                for (auto system : scene.physics) system.func(scene);
            }

            accumulator -= dt;
            t += dt;
        }

        Time::deltaTime = accumulator / dt;
        Time::time      = currentTime;

        // DRAW GRAPHICS
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (Scene& scene : Scenes) {
            if (scene.disabled) continue;

            for (auto system : scene.render) {
                system.func(scene);
            }
        }

        SDL_GL_SwapWindow(Window);
        InputManager::PollEvents();
    }
}

void Elgine::Run() {
    Debug::Log("Elgine Game Loop Starting!");
    GameLoop();

    SDL_DestroyWindow(Window);
    SDL_Quit();
}

Scene& Elgine::CreateScene(void) {
    Scene scene;
    Scenes.push_back(scene);

    return Scenes.back();
}
