#pragma once

#include <vector>

#include "components.hpp"
#include "ecs.hpp"
#include "systems.hpp"
#include "types.hpp"
#include "utils.hpp"

class SDL_Window;
struct Scene;

class Elgine {
 public:
    Elgine();
    ~Elgine();
    void Run();

 public:
    static SDL_Window* Window;
    static std::vector<Scene> Scenes;
    static Scene& CreateScene(void);

 private:
    bool isRunning;

 private:
    void Init();
    void GameLoop();
    void Input();
};
