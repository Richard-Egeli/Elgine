#include "frame-manager.hpp"

#include "scene-view.hpp"
#include "time.hpp"

static void Fixed(Scene& scene) {
    static unsigned long long int ticks;
    static double time;

    if (Time::time > time + 1.0) {
        Time::fixedFrames = ticks;
        time              = Time::time;
        ticks             = 0;
    }

    ticks++;
}

static void Normal(Scene& scene) {
    static unsigned long long int ticks;
    static double time;

    if (Time::time > time + 1.0) {
        Time::frames = ticks;
        time         = Time::time;
        ticks        = 0;
    }

    ticks++;
}

void FrameManager::Setup(Scene& scene) {
    scene.AddSystem(Normal, SystemType::Update);
    scene.AddSystem(Fixed, SystemType::Physics);
}
