#ifndef ELGINE_COMPONENTS_MESH_HPP_
#define ELGINE_COMPONENTS_MESH_HPP_

#include <array>
#include <vector>

#include "../opengl.hpp"
#include "../types/shader.hpp"
#include "../types/texture.hpp"
#include "../types/vertex.hpp"

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
    void ClearShader();

    void SetTexture(Texture texture, unsigned int slot = 0);
    void ClearTexture(unsigned int slot);

 private:
    void UpdateShaderTextures();
};

#endif  // ELGINE_COMPONENTS_MESH_HPP_
