#include "mesh.hpp"

#include "asset-loader.hpp"
#include "camera.hpp"
#include "math.hpp"
#include "opengl.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "vertex.hpp"

Mesh::Mesh() {}

Mesh::~Mesh() {}

void Mesh::Draw() const {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::SetMesh(std::vector<Vertex> vertices, std::vector<Triangle> indices) {
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
    size_t index_buffer_size = indices.size() * sizeof(Triangle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, &indices[0], GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::UpdateShaderTextures() {
    if (shader.id) {
        shader.Use();

        for (int i = 0; i < textures.size(); i++) {
            std::string name = "texture" + std::to_string(i);
            shader.SetInt(name.c_str(), i);
        }
    }
}

void Mesh::SetShader(const char* vertexShader, const char* fragmentShader) {
    shader.SetVertexShader(vertexShader);
    shader.SetFragmentShader(fragmentShader);

    if (textures.size()) UpdateShaderTextures();
}

void Mesh::ClearShader() { shader.Clear(); }

void Mesh::SetTexture(Texture texture, unsigned int slot) {
    if (slot < this->textures.size()) {
        // Clean up the old texture if it exists
        if (!this->textures[slot]) AssetLoader::Unload<Texture>(this->textures[slot]);

        this->textures[slot] = texture;
        UpdateShaderTextures();
    }
}

void Mesh::ClearTexture(unsigned int slot) {
    if (this->textures[slot] != 0) {
        AssetLoader::Unload<Texture>(this->textures[slot]);
        this->textures[slot] = 0;
    }
}
