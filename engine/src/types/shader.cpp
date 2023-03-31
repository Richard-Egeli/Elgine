#include "shader.hpp"

#include <iostream>

#include "../opengl.hpp"

Shader::Shader() {}

Shader::~Shader() {}

void Shader::Link() {
    glDeleteProgram(this->id);

    this->id = glCreateProgram();

    if (this->vertex != 0) glAttachShader(this->id, this->vertex);
    if (this->fragment != 0) glAttachShader(this->id, this->fragment);

    glLinkProgram(this->id);

    std::cout << "ERR " << glGetError() << std::endl;
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
    glDeleteShader(this->vertex);

    this->vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertex, 1, &source, nullptr);
    glCompileShader(this->vertex);

    Link();
}

void Shader::SetFragmentShader(FragmentShader source) {
    glDeleteShader(this->fragment);

    this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragment, 1, &source, nullptr);
    glCompileShader(this->fragment);

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
