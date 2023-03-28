#include "time.hpp"

double Time::deltaTime = 0.0;
double Time::time      = 0.0;

unsigned int Time::framesPerSecond      = 0;
unsigned int Time::framesPerSecondFixed = 0;

void FixedFPSTick() {
    static unsigned long long int ticks;
    static double time;

    if (Time::time > time + 1.0) {
        Time::framesPerSecondFixed = ticks;
        time                       = Time::time;
        ticks                      = 0;
    }

    ticks++;
}

void FPSTick() {
    static unsigned long long int ticks;
    static double time;

    if (Time::time > time + 1.0) {
        Time::framesPerSecond = ticks;
        time                  = Time::time;
        ticks                 = 0;
    }

    ticks++;
}
