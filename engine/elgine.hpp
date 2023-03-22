#ifndef ENGINE_ELGINE_H_
#define ENGINE_ELGINE_H_

#include "component.hpp"
#include "debug.hpp"
#include "time.hpp"

class SDL_Window;
class SDL_Renderer;
struct Scene;

typedef void (*OnStart)(void);
typedef void (*OnUpdate)(void);
typedef void (*OnFixedUpdate)(void);
typedef void (*OnRender)(void);

class Elgine {
 public:
    Elgine();
    ~Elgine();
    void Run();

 public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    static Scene Scene;

    static OnStart Start;
    static OnUpdate Update;
    static OnFixedUpdate FixedUpdate;
    static OnRender Render;

 private:
    bool isRunning;

 private:
    void Init();
    void GameLoop();
    void Input();
};

#endif
