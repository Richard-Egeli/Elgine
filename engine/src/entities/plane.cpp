#include "plane.hpp"

#include <vector>

#include "default-shader.hpp"
#include "mesh.hpp"
#include "transform-component.hpp"

void Plane::Setup(Scene& scene) {
    Transform* trans = scene.AddComponent<Transform>(*this);
    Mesh* mesh       = scene.AddComponent<Mesh>(*this);

    std::vector<Vertex> vertices = {
        Vertex(0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
        Vertex(-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
        Vertex(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
    };

    std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};
    mesh->SetMesh(vertices, indices);

    const char* vertex = DefaultShader::VertexShader;
    mesh->SetShader(DefaultShader::VertexShader, DefaultShader::FragmentShader);
}
