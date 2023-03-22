#include "elgine.hpp"

#include <SDL.h>

#include <future>
#include <iostream>
#include <mutex>

#include "debug.hpp"
#include "ecs.hpp"
#include "time.hpp"

Scene Elgine::Scene;

Elgine::Elgine() {
    isRunning = true;
    CHECK_TRUE(SDL_Init(SDL_INIT_EVERYTHING) == 0);
    CHECK_NULL(window = SDL_CreateWindow("Elgine",
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         800,
                                         600,
                                         0));

    CHECK_NULL(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    Debug::Log("Elgine Initialized!");
}

Elgine::~Elgine() {}

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
                    break;
                }
            default:
                break;
        }
    }
}

void Elgine::GameLoop() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    double t  = 0.0;
    double dt = 0.01;

    double currentTime = SDL_GetTicks64();
    double accumulator = 0.0;

    while (isRunning) {
        Input();

        Scene.RunSystem();

        double newTime   = SDL_GetTicks64();
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25)
            frameTime = 0.25;

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) {
            accumulator -= dt;
            t += dt;

            Time::time      = t;
            Time::deltaTime = dt;

            for (auto entity : SceneView<Transform>(Scene)) {
                std::cout << entity << " TICK\n";
            }
        }

        SDL_RenderClear(renderer);

        // DRAW GRAPHICS

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
