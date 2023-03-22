#include "elgine.hpp"

#include <SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "debug.hpp"
#include "ecs.hpp"
#include "time.hpp"

OnStart Elgine::Start             = nullptr;
OnUpdate Elgine::Update           = nullptr;
OnFixedUpdate Elgine::FixedUpdate = nullptr;
OnRender Elgine::Render           = nullptr;

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
                }

                break;
            default:
                SDL_PumpEvents();
                break;
        }
    }
}

void Elgine::GameLoop() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    double t  = 0.0;
    double dt = 1.0 / 60.0;

    double currentTime = SDL_GetTicks64() / 1000.0;
    double accumulator = 0.0;

    Elgine::Start();

    while (isRunning) {
        Input();

        double newTime   = SDL_GetTicks64() / 1000.0;
        double frameTime = newTime - currentTime;

        if (frameTime > 0.25)
            frameTime = 0.25;

        currentTime = newTime;
        accumulator += frameTime;

        Elgine::Update();

        while (accumulator >= dt) {
            Elgine::FixedUpdate();

            accumulator -= dt;
            t += dt;
        }

        Time::deltaTime = accumulator / dt;
        Time::time      = currentTime;

        SDL_RenderClear(renderer);

        // DRAW GRAPHICS
        Elgine::Render();

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
