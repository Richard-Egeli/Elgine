#pragma once

struct Math {
    static float CosF(float angle);
    static float SinF(float angle);
    static float SqrtF(float value);
    static float RadF(float angle);
    static double Pow(double value, double exp);
    static double Clamp(double value, double min, double max);
};
