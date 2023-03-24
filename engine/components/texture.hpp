#ifndef ELGINE_ENGINE_TEXTURE_HPP_
#define ELGINE_ENGINE_TEXTURE_HPP_

#include <SDL.h>
#include <SDL2_image/SDL_image.h>

#include <string>

#include "elgine.hpp"

struct Texture {
    SDL_Texture* texture;
    size_t x;
    size_t y;
    size_t width;
    size_t height;

    static Texture& Create(const std::string path) {
        SDL_Texture* texture = IMG_LoadTexture(Elgine::Renderer, path);
    }
};

#endif  // ELGINE_ENGINE_TEXTURE_HPP_
