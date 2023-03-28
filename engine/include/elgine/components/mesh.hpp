#pragma once

#include <array>
#include <vector>

#include "elgine/types.hpp"

struct Mesh {
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    Shader shader;

    Mat4 model;
    Mat4 view;
    Mat4 projection;

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
