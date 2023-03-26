#ifndef ELGINE_ENGINE_TYPES_TEXTURE_HPP_
#define ELGINE_ENGINE_TYPES_TEXTURE_HPP_

#include <string>

#include "opengl.hpp"

using Texture = unsigned int;

struct TextureData {
    Texture id;
    std::string path;
    unsigned char* buffer;
    int width, height, bpp;
    unsigned int dependents;

    TextureData(unsigned int id,
                int width,
                int height,
                int bpp,
                std::string path,
                int dependents = 1)
        : id(id), width(width), height(height), bpp(bpp), path(path), dependents(dependents) {}
};

#endif  // ELGINE_ENGINE_TYPES_TEXTURE_HPP_
