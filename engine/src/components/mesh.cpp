#include "mesh.hpp"

#include <OpenGL/OpenGL.h>

#include "asset-loader.hpp"
#include "camera.hpp"
#include "math.hpp"
#include "opengl.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "vertex.hpp"

Mesh::Mesh() {}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Triangle> indices) {
    // SetMesh(vertices, indices);
}

Mesh::~Mesh() {}

void Mesh::Draw() const {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
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
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // texture coords
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(10 * sizeof(float)));
    glEnableVertexAttribArray(3);

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
