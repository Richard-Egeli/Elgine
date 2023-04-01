#include "shader.hpp"

#include <OpenGL/OpenGL.h>

#include <iostream>

#include "../opengl.hpp"

Shader::Shader() {}

Shader::~Shader() { Clear(); }

void Shader::CheckCompileError(unsigned int id) {
    int err;
    int size;

    glGetShaderiv(id, GL_COMPILE_STATUS, &err);
    if (err != GL_TRUE) {
        std::cout << "Shader failed to compile, ERR: " << err << std::endl;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);

        if (size > 0) {
            char message[size + 1];
            glGetShaderInfoLog(id, 512, NULL, message);
            std::cout << message << std::endl;
        }
    }
}

int Shader::CheckLinkError(unsigned int id) {
    int err;
    int size;

    glGetProgramiv(id, GL_LINK_STATUS, &err);
    if (err != GL_TRUE) {
        std::cout << "Failed to link program, ERR: " << err << std::endl;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &size);

        char message[512] = {0};
        glGetProgramInfoLog(id, 512, NULL, message);
        std::cout << message << std::endl;
        return 1;
    }

    return 0;
}

void Shader::Link() {
    if (this->vertex != 0 && this->fragment != 0) {
        if (this->id != 0) glDeleteProgram(this->id);

        this->id = glCreateProgram();
        glAttachShader(this->id, this->vertex);
        glAttachShader(this->id, this->fragment);

        glLinkProgram(this->id);
    }

    glGetError();
}

void Shader::Use() const { glUseProgram(this->id); }

void Shader::Clear() {
    glDeleteShader(this->vertex);
    glDeleteShader(this->fragment);
    glDeleteProgram(this->id);

    this->vertex   = 0;
    this->fragment = 0;
    this->id       = 0;
}

void Shader::SetVertexShader(VertexShader source) {
    if (this->vertex != 0) glDeleteShader(this->vertex);

    this->vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertex, 1, &source, nullptr);
    glCompileShader(this->vertex);
    CheckCompileError(this->vertex);

    Link();
}

void Shader::SetFragmentShader(FragmentShader source) {
    if (this->fragment != 0) glDeleteShader(this->fragment);

    this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragment, 1, &source, nullptr);
    glCompileShader(this->fragment);
    CheckCompileError(this->fragment);

    Link();
}

void Shader::SetMat4(const char* key, Mat4 value) const {
    unsigned int location = glGetUniformLocation(this->id, key);
    glUniformMatrix4fv(location, 1, GL_FALSE, value.Value());
}

// void Shader::SetTransform(const char* key, const Transform value) const {
//     SetMat4(key, value.matrices);
// }

void Shader::SetInt(const char* key, int value) const {
    glUniform1i(glGetUniformLocation(this->id, key), value);
}

void Shader::SetFloat(const char* key, float value) const {
    glUniform1f(glGetUniformLocation(this->id, key), value);
}
