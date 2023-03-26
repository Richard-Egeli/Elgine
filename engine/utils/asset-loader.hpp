#ifndef ELGINE_ENGINE_UTILS_ASSET_LOADER_HPP_
#define ELGINE_ENGINE_UTILS_ASSET_LOADER_HPP_

#include <string>
#include <type_traits>
#include <vector>

#include "texture.hpp"

class AssetLoader {
 private:
    const static char* ASSET_PATH;
    static std::vector<TextureData> Textures;

    static Texture HasTexture(const char* path);
    static Texture LoadTexture(const char* path);
    static void UnloadTexture(const Texture texture);

 public:
    template <typename T>
    static T Load(const char* path) {
        if (std::is_same<T, Texture>::value) {
            return AssetLoader::LoadTexture(path);
        }
    }

    template <typename T>
    static void Unload(unsigned int id) {
        if (std::is_same_v<T, Texture>) AssetLoader::UnloadTexture(id);
    }
};

#endif  // ELGINE_ENGINE_UTILS_ASSET_LOADER_HPP_
