#pragma once

#include <array>
#include <vector>

#include "elgine/types.hpp"

struct Mesh {
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    unsigned int size;
    Shader shader;

    std::array<Texture, 8> textures;

    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<Triangle> indices);
    // Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    ~Mesh();

    // void SetMesh(std::vector<Vertex> vertices, std::vector<Triangle> indices);
    void SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void SetShader(const char* vertexShader, const char* fragmentShader);
    void ClearShader();

    void Draw() const;

    void SetTexture(Texture texture, unsigned int slot = 0);
    void ClearTexture(unsigned int slot);

 private:
    void UpdateShaderTextures();
};
