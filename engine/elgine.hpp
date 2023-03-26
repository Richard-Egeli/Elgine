#ifndef ENGINE_ELGINE_H_
#define ENGINE_ELGINE_H_

#include <SDL.h>

#include <vector>

#include "debug.hpp"
#include "ecs/component.hpp"
#include "time.hpp"

class SDL_Window;
struct Scene;

class Elgine {
 public:
    Elgine();
    ~Elgine();
    void Run();

 public:
    static SDL_Window* Window;
    static SDL_GLContext Context;
    static std::vector<Scene> Scenes;
    static Scene& CreateScene(void);

 private:
    bool isRunning;

 private:
    void Init();
    void GameLoop();
    void Input();
};

#endif
