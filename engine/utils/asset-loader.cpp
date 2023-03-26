#include "asset-loader.hpp"

#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

#include "opengl.hpp"
#include "stb_image.hpp"
#include "texture.hpp"

Texture* AssetLoader::LoadTexture(const char* path) {
    int width, height, bpp;
    std::string p;
    p += "../assets/";
    p += path;

    stbi_set_flip_vertically_on_load(1);
    const unsigned char* buffer = stbi_load(p.c_str(), &width, &height, &bpp, 4);

    if (!buffer) std::cout << "Failed to load texture " << path << std::endl;

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum err = glGetError();
    if (err) std::cout << "Failed to generate texture, ERR: " << err << std::endl;

    // std::cout << "TEXTURE " << texture << std::endl;

    if (buffer) stbi_image_free((void*)buffer);

    return new Texture(texture, width, height, bpp, path);
}
