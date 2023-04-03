#pragma once

#define uniform
#define sampler2D

struct vec3;

struct vec2 {
    double x, y;
    vec2(double x = 0, double y = 0) : x(x), y(y) {}

    vec2 operator=(const vec3& v);
    vec2 operator=(const vec2& v);
    vec2 operator*(const vec2& v);
    vec2 operator/(const vec2& v);
    vec2 operator-(const vec2& v);
    vec2 operator+(const vec2& v);
};

struct vec3 {
    double x, y, z;
    vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    vec3 operator=(const vec2& v);
    vec3 operator=(const vec3& v);
    vec3 operator*(const vec3& v);
    vec3 operator/(const vec3& v);
    vec3 operator-(const vec3& v);
    vec3 operator+(const vec3& v);
};

struct vec4 {
    double x, y, z, w;
    vec4(double x = 0, double y = 0, double z = 0, double w = 0) : x(x), y(y), z(z), w(w) {}
};

template <typename T>
T mix(T value, ...);

template <typename T>
T ceil(T value);

template <typename T>
T floor(T value);

template <typename T>
T abs(T value){};

template <typename T>
T normalize(T value){};

template <typename T>
T pow(T value, T exp);

template <typename T>
T dot(T v1, T v2);
