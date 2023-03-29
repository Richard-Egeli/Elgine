#pragma once

#include <string>
#include <type_traits>

#include "elgine/types.hpp"

using FragmentShader = const char*;
using VertexShader   = const char*;

struct Shader {
    unsigned int vertex;
    unsigned int fragment;
    unsigned int id;

 private:
    void Link();

 public:
    Shader();
    ~Shader();

    void Use() const;
    void Clear();

    void SetVertexShader(VertexShader source);
    void SetFragmentShader(FragmentShader source);

    void SetInt(const char* key, int value) const;
    void SetFloat(const char* key, float value) const;
    void SetMat4(const char* key, Mat4 value) const;
};
