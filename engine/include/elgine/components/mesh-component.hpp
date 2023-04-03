#pragma once

#include <array>
#include <vector>

#include "elgine/types.hpp"

struct MeshComponent {
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    unsigned int size;
    Material material;

    struct TextureContainer {
        std::string name;
        Texture texture;
    };

    std::array<TextureContainer, 8> textures;

    MeshComponent();
    MeshComponent(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    ~MeshComponent();

    // void SetMesh(std::vector<Vertex> vertices, std::vector<Triangle> indices);

    /**
     * @brief Sets or updates the mesh for this mesh component
     *    If the mesh is already set, it will be replaced.
     *
     * @param vertices The vertices of the mesh
     * @param indices The indices of the mesh
     */
    void SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    /**
     * @brief Sets the vertex and fragment shader for this mesh
     *    If the shader is already set, it will be replaced, else it will be created
     *
     * @param vertexShader The vertex shader source code
     * @param fragmentShader The fragment shader source code
     */
    void SetShader(const char* vertexShader, const char* fragmentShader);

    /**
     * @brief Clears the shader for this mesh
     * If will free the texture slots and delete the shader programs
     */
    void ClearShader();

    void Draw() const;

    void SetTexture(Texture texture, std::string name, unsigned int slot = 0);
    void ClearTexture(unsigned int slot);

 private:
    void UpdateShaderTextures();
};
