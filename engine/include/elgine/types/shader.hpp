#pragma once

#include <string>
#include <type_traits>

struct Vec3;
struct Mat4;

class Shader {
 public:
    unsigned int vertex;
    unsigned int fragment;
    unsigned int id;

 private:
    void Link();

 public:
    Shader();
    ~Shader();

    virtual void Use();
    void Clear();

    static void CheckCompileError(unsigned int id);
    static int CheckLinkError(unsigned int id);

    void SetVertexShader(const char* source);
    void SetFragmentShader(const char* source);

    void SetInt(const char* key, int value) const;
    void SetFloat(const char* key, float value) const;
    void SetVec3(const char* key, const Vec3& value) const;
    void SetMat4(const char* key, Mat4 value) const;
};
