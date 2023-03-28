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

void Shader::SetVertex(VertexShader source) {
    glDeleteShader(this->vertex);

    this->vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertex, 1, &source, nullptr);
    glCompileShader(this->vertex);

    Link();
}

void Shader::SetFragment(FragmentShader source) {
    glDeleteShader(this->fragment);

    this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragment, 1, &source, nullptr);
    glCompileShader(this->fragment);

    Link();
}

void Shader::SetInt(const char* key, int value) const {
    glUniform1i(glGetUniformLocation(this->id, key), value);
}

void Shader::SetFloat(const char* key, float value) const {
    glUniform1f(glGetUniformLocation(this->id, key), value);
}
