#include "asset-loader.hpp"

#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

#include "elgine.hpp"
#include "opengl.hpp"
#include "stb_image.hpp"
#include "texture.hpp"

std::vector<TextureData> AssetLoader::Textures;

const char* AssetLoader::ASSET_PATH = "../assets/";

Texture AssetLoader::HasTexture(const char* path) {
    for (auto& tex : Textures)
        if (tex.path == path) return tex.id;

    return 0;
}

Texture AssetLoader::LoadTexture(const char* path) {
    Texture texture;
    int width, height, bpp;
    std::string asset_path;

    if ((texture = HasTexture(path)) != 0) {
        Textures[texture - 1].dependents++;
        return texture;
    }

    asset_path += ASSET_PATH;
    asset_path += path;
    stbi_set_flip_vertically_on_load(1);
    const unsigned char* buffer = stbi_load(asset_path.c_str(), &width, &height, &bpp, 4);

    if (!buffer) std::cout << "Failed to load texture " << path << std::endl;

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

    stbi_image_free((void*)buffer);

    TextureData data = TextureData(texture, width, height, bpp, path);
    Textures.insert(Textures.begin() + texture - 1, data);

    return texture;
}

void AssetLoader::UnloadTexture(const Texture texture) {
    if (Textures.size() <= texture - 1) return;
    Textures[texture - 1].dependents--;
    if (Textures[texture - 1].dependents == 0) glDeleteTextures(1, &texture);
}
