#ifndef ENGINE_ELGINE_H_
#define ENGINE_ELGINE_H_

#include <vector>

#include "component.hpp"
#include "debug.hpp"
#include "time.hpp"

class SDL_Window;
class SDL_Renderer;
struct Scene;

class Elgine {
 public:
    Elgine();
    ~Elgine();
    void Run();

 public:
    static SDL_Window* Window;
    static SDL_Renderer* Renderer;

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
