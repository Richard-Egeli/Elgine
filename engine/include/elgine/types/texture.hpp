#pragma once

#include <string>

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
