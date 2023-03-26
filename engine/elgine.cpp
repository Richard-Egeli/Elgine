#include "elgine.hpp"
//
#include <SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <string>

#include "debug.hpp"
#include "mesh-rendering.hpp"
#include "time.hpp"

std::vector<Scene> Elgine::Scenes;

SDL_Window* Elgine::Window;
SDL_GLContext Elgine::Context;

void Elgine::Input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }

                break;
        }
    }
}

Elgine::Elgine() {
    isRunning = true;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    this->Window = SDL_CreateWindow("Elgine",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    800,
                                    600,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (Debug::CheckNull(Window, "Window is NULL!")) return;

    this->Context = SDL_GL_CreateContext(Window);

    if (this->Context == nullptr) {
        std::cout << "Failed to create OpenGL Context: " << SDL_GetError() << "\n";
    }

    SDL_GL_MakeCurrent(Window, Context);

    std::string err = SDL_GetError();
    if (err.length() > 0) {
        std::cout << RED << "SDL2 ERROR: " << err << NOR << std::endl;
    }

    Debug::Log("SDL2 Initialized!");

    SDL_GL_SetSwapInterval(1);
}

Elgine::~Elgine() {}

void Elgine::GameLoop() {
    double t  = 0.0;
    double dt = 1.0 / 60.0;

    double currentTime = SDL_GetTicks64() / 1000.0;
    double accumulator = 0.0;

    while (isRunning) {
        // Dev Inputs
        Input();

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
        glClear(GL_COLOR_BUFFER_BIT);

        for (Scene& scene : Scenes) {
            if (scene.disabled) continue;

            for (auto system : scene.render) {
                system.func(scene);
            }
        }

        SDL_GL_SwapWindow(Window);
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
