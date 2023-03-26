#ifndef ENGINE_ELGINE_H_
#define ENGINE_ELGINE_H_

#include <SDL.h>
#include <SDL2/SDL_video.h>

#include <vector>

#include "elgine/components.hpp"
#include "elgine/utils.hpp"

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
