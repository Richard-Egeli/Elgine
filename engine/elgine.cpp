#include "elgine.hpp"

#include <SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include <iostream>
#include <vector>

#include "debug.hpp"
#include "ecs.hpp"
#include "time.hpp"

std::vector<Scene> Elgine::scenes;

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

    window =
        SDL_CreateWindow("Elgine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (Debug::CheckNull(window, "Window is NULL!")) return;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (Debug::CheckNull(renderer, "Renderer is NULL!")) return;

    Debug::Log("Elgine Initialized!");
}

Elgine::~Elgine() {}

void Elgine::GameLoop() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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

        for (Scene& scene : scenes) {
            if (scene.disabled) continue;

            for (auto system : scene.update) system.func(scene);
        }

        while (accumulator >= dt) {
            for (Scene& scene : scenes) {
                if (scene.disabled) continue;

                for (auto system : scene.physics) system.func(scene);
            }

            accumulator -= dt;
            t += dt;
        }

        Time::deltaTime = accumulator / dt;
        Time::time      = currentTime;

        SDL_RenderClear(renderer);

        // DRAW GRAPHICS
        for (Scene& scene : scenes) {
            if (scene.disabled) continue;

            for (auto system : scene.render) system.func(scene);
        }

        SDL_RenderPresent(renderer);
    }
}

void Elgine::Run() {
    Debug::Log("Elgine Game Loop Starting!");
    GameLoop();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Scene& Elgine::CreateScene(void) {
    Scene scene;
    scenes.push_back(scene);

    return scenes.back();
}
