#ifndef ELGINE_ENGINE_COMPONENTS_MESH_HPP_
#define ELGINE_ENGINE_COMPONENTS_MESH_HPP_

#include <array>
#include <vector>

#include "opengl.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex.hpp"

struct Mesh {
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    Shader shader;

    std::array<Texture, 8> textures;

    Mesh();
    ~Mesh();

    void SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void SetShader(const char* vertexShader, const char* fragmentShader);

    void SetTexture(Texture texture, unsigned int slot = 0);

 private:
    void UpdateShaderTextures();
};

#endif  // ELGINE_ENGINE_COMPONENTS_MESH_HPP_
