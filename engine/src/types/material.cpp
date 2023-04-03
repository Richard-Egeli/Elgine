#include "material.hpp"

#include "elgine/camera/camera.hpp"
#include "elgine/opengl.hpp"
#include "elgine/shader-library.hpp"
#include "elgine/types.hpp"

Material::Material() {
    // // diffuse = {0.9f, 0.9f, 0.9f};
    diffuse  = AssetLoader::Load<Texture>("container.png");
    specular = {1, 1, 1};
    ambient  = {0.3f, 0.3f, 0.3f};

    SetInt("material.diffuse", 0);
}

void Material::Use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse);

    Shader::Use();
    SetVec3("material.specular", specular);
    SetVec3("material.ambient", ambient);
    SetFloat("material.shininess", 32.f);
}
