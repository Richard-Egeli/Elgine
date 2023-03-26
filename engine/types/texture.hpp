#ifndef ELGINE_ENGINE_TYPES_TEXTURE_HPP_
#define ELGINE_ENGINE_TYPES_TEXTURE_HPP_

#include <string>

#include "opengl.hpp"
struct Texture {
    unsigned int id;
    std::string path;
    unsigned char* buffer;

    int width, height, bpp;

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    Texture(unsigned int id, int width, int height, int bpp, std::string path)
        : id(id), width(width), height(height), bpp(bpp), path(path) {}

    ~Texture() { glDeleteTextures(1, &this->id); }
};

#endif  // ELGINE_ENGINE_TYPES_TEXTURE_HPP_
