#pragma once

struct Math {
    static double Cos(double angle);
    static double Sin(double angle);
    static float SqrtF(float value);
    static float RadF(float angle);
    static double Pow(double value, double exp);
    static double Clamp(double value, double min, double max);
};
