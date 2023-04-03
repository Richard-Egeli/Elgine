#include "mesh-component.hpp"

#include <OpenGL/OpenGL.h>

#include "asset-loader.hpp"
#include "camera.hpp"
#include "math.hpp"
#include "opengl.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "vertex.hpp"

MeshComponent::MeshComponent() {}

MeshComponent::MeshComponent(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    SetMesh(vertices, indices);
}

MeshComponent::~MeshComponent() {}

void MeshComponent::Draw() const {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void MeshComponent::SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    size_t vertex_buffer_size = vertices.size() * sizeof(Vertex);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    size                     = indices.size();
    size_t index_buffer_size = size * sizeof(unsigned int);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, &indices[0], GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // vertex color
    // glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void MeshComponent::UpdateShaderTextures() {
    // if (material.id) {
    //     material.Draw();

    //     for (int i = 0; i < textures.size(); i++) {
    //         std::string name = "texture" + std::to_string(i);
    //         material.SetInt(name.c_str(), i);
    //     }
    // }
}

void MeshComponent::SetShader(const char* vertexShader, const char* fragmentShader) {
    material.SetVertexShader(vertexShader);
    material.SetFragmentShader(fragmentShader);

    if (textures.size()) UpdateShaderTextures();
}

void MeshComponent::ClearShader() { material.Clear(); }

void MeshComponent::SetTexture(Texture texture, std::string name, unsigned int slot) {
    if (slot < this->textures.size()) {
        // Clean up the old texture if it exists
        if (!this->textures[slot].texture)
            AssetLoader::Unload<Texture>(this->textures[slot].texture);

        this->textures[slot].texture = texture;
        this->textures[slot].name    = name;
        UpdateShaderTextures();
    }
}

void MeshComponent::ClearTexture(unsigned int slot) {
    if (this->textures[slot].texture != 0) {
        AssetLoader::Unload<Texture>(this->textures[slot].texture);
        this->textures[slot].texture = 0;
    }
}
