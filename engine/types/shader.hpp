#ifndef ELGINE_ENGINE_TYPES_SHADER_HPP_
#define ELGINE_ENGINE_TYPES_SHADER_HPP_

#include <string>
#include <type_traits>

using FragmentShader = const char*;
using VertexShader   = char*;

struct Shader {
    unsigned int vertex;
    unsigned int fragment;
    unsigned int id;

 private:
    void Link();
    void SetVertex(VertexShader source);
    void SetFragment(FragmentShader source);

    void SetInt(const char* key, int value) const;
    void SetFloat(const char* key, float value) const;

 public:
    Shader();
    ~Shader();

    void Use() const;
    void Clear();

    template <typename T>
    void Set(const char* source) {
        if (std::is_same_v<T, VertexShader>)
            SetVertex((VertexShader)source);
        else if (std::is_same_v<T, FragmentShader>)
            SetFragment((FragmentShader)source);
    }

    template <typename T>
    void Set(const char* key, T value) const {
        if (std::is_same_v<T, int>)
            SetInt(key, value);
        else if (std::is_same_v<T, float>)
            SetFloat(key, value);
    }
};

#endif  // ELGINE_ENGINE_TYPES_SHADER_HPP_
