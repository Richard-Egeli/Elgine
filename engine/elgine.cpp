#include "elgine.hpp"

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "debug.hpp"
#include "ecs.hpp"
#include "frame-manager.hpp"
#include "loader.hpp"
#include "shaders.hpp"
#include "time.hpp"

std::vector<Scene> Elgine::Scenes;
//
SDL_Window* Elgine::Window;
SDL_GLContext Elgine::Context;

static GLuint VBO, VAO, vShader, fShader, program;

static void GL_Draw() {
    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

static void GL_InitDraw() {
    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &SHADER_tutorial_vert, NULL);
    glCompileShader(vShader);

    int success;
    char infoLog[512];

    glGetShaderiv(1, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "SHADER FAILED TO COMPILE: " << infoLog << std::endl;
    }

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &SHADER_tutorial_frag, NULL);
    glCompileShader(fShader);

    program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "PROGRAM FAILED TO LINK: " << infoLog << std::endl;
    }

    glUseProgram(program);
}

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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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

    // Scene to add development tools to
    Scene& scene              = Elgine::CreateScene();
    FrameManager frameManager = Entity::Create<FrameManager>(scene);

    SDL_GL_SetSwapInterval(1);

    GL_InitDraw();
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

        for (Scene& scene : Scenes) {
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

        // DRAW GRAPHICS
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        GL_Draw();

        for (Scene& scene : Scenes) {
            if (scene.disabled) continue;

            for (auto system : scene.render) system.func(scene);
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
