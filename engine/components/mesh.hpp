#ifndef ELGINE_ENGINE_COMPONENTS_MESH_HPP_
#define ELGINE_ENGINE_COMPONENTS_MESH_HPP_

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#include <array>
#include <vector>

struct Mesh {
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;

    void SetMesh(std::array<float, 65535> vertices, std::array<unsigned int, 6> indices) {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void SetShader(const char* vertexShader, const char* fragmentShader) {
        glDeleteShader(this->vertexShader);
        glDeleteShader(this->fragmentShader);
        glDeleteProgram(this->shaderProgram);

        this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(this->vertexShader, 1, &vertexShader, NULL);
        glCompileShader(this->vertexShader);

        this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(this->fragmentShader, 1, &fragmentShader, NULL);
        glCompileShader(this->fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, this->vertexShader);
        glAttachShader(shaderProgram, this->fragmentShader);
        glLinkProgram(shaderProgram);
    }
};

#endif  // ELGINE_ENGINE_COMPONENTS_MESH_HPP_
