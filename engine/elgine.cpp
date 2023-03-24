#include "elgine.hpp"

#include <SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include <iostream>
#include <vector>

#include "debug.hpp"
#include "ecs.hpp"
#include "frame-manager.hpp"
#include "time.hpp"

std::vector<Scene> Elgine::Scenes;

SDL_Renderer* Elgine::Renderer = nullptr;
SDL_Window* Elgine::Window     = nullptr;

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
    SDL_Init(SDL_INIT_EVERYTHING);

    Window =
        SDL_CreateWindow("Elgine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (Debug::CheckNull(Window, "Window is NULL!")) return;

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Debug::CheckNull(Renderer, "Renderer is NULL!")) return;

    Debug::Log("Elgine Initialized!");

    // Scene to add development tools to
    Scene& scene              = Elgine::CreateScene();
    FrameManager frameManager = Entity::Create<FrameManager>(scene);
}

Elgine::~Elgine() {}

void Elgine::GameLoop() {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);

    double t  = 0.0;
    double dt = 1.0 / 60.0;

    double currentTime = SDL_GetTicks64() / 1000.0;
    double accumulator = 0.0;

    while (isRunning) {
        // Dev Inputs
        Input();
        //

        double newTime   = SDL_GetTicks64() / 1000.0;
        double frameTime = newTime - currentTime;

        if (frameTime > 0.25) frameTime = 0.25;

        currentTime = newTime;
        accumulator += frameTime;

        for (Scene& scene : Scenes) {
            // std::cout << "TRIGGER\n";
            if (scene.disabled) continue;

            for (auto system : scene.update) system.func(scene);
        }

        while (accumulator >= dt) {
            for (Scene& scene : Scenes) {
                if (scene.disabled) continue;

                for (auto system : scene.physics) system.func(scene);
            }

            accumulator -= dt;
            t += dt;
        }

        Time::deltaTime = accumulator / dt;
        Time::time      = currentTime;

        SDL_RenderClear(Renderer);

        // DRAW GRAPHICS
        for (Scene& scene : Scenes) {
            if (scene.disabled) continue;

            for (auto system : scene.render) system.func(scene);
        }

        SDL_RenderPresent(Renderer);
    }
}

void Elgine::Run() {
    Debug::Log("Elgine Game Loop Starting!");
    GameLoop();

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

Scene& Elgine::CreateScene(void) {
    Scene scene;
    Scenes.push_back(scene);

    return Scenes.back();
}
