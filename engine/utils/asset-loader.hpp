#ifndef ELGINE_ENGINE_UTILS_ASSET_LOADER_HPP_
#define ELGINE_ENGINE_UTILS_ASSET_LOADER_HPP_

#include <string>
#include <type_traits>

#include "texture.hpp"

struct AssetLoader {
    const char* ASSET_PATH = "./assets/";

    static Texture* LoadTexture(const char* path);

    template <typename T>
    static T* Load(const char* path) {
        if (std::is_same<T, Texture>::value) {
            return AssetLoader::LoadTexture(path);
        }
    }
};

#endif  // ELGINE_ENGINE_UTILS_ASSET_LOADER_HPP_
