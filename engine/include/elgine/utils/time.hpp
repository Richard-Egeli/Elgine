#pragma once

/**
 * Called once per game loop to count the number of frames per second
 */
extern void FPSTick();

/**
 * Called once per physics timestep to count the number of fixed frames
 */
extern void FixedFPSTick();

class Time {
 public:
    static double deltaTime;
    static double time;

    static unsigned int framesPerSecond;
    static unsigned int framesPerSecondFixed;
};
