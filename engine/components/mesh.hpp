#ifndef ELGINE_ENGINE_COMPONENTS_MESH_HPP_
#define ELGINE_ENGINE_COMPONENTS_MESH_HPP_

#include <array>

#include "opengl.hpp"
#include "texture.hpp"
#include "vertex.hpp"

struct Mesh {
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;

    Texture* texture;

    Mesh();
    ~Mesh();

    void SetMesh(std::array<Vertex, 65535> vertices, std::array<unsigned int, 6> indices);

    void SetShader(const char* vertexShader, const char* fragmentShader);

    void SetTexture(Texture* texture);
};

#endif  // ELGINE_ENGINE_COMPONENTS_MESH_HPP_
