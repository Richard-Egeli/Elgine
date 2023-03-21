#ifndef ENGINE_ELGINE_H_
#define ENGINE_ELGINE_H_

#include "component.hpp"
#include "debug.hpp"
#include "quaternion.hpp"
#include "time.hpp"
#include "transform.hpp"
#include "vector3.hpp"

class SDL_Window;
class SDL_Renderer;
struct Scene;

class Elgine {
 public:
    Elgine();
    ~Elgine();
    void Run();

 public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    static Scene Scene;

 private:
    bool isRunning;

 private:
    void Init();
    void GameLoop();
    void Input();
};

#endif
