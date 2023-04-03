#pragma once

#include "elgine/types/shader.hpp"
#include "elgine/types/vec3.hpp"

class Material : public Shader {
 public:
    unsigned int diffuse;
    Vec3 specular;
    Vec3 ambient;

    Material();

    virtual void Use() override;
};
