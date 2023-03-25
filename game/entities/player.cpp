#include "player.hpp"

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <iostream>

#include "mesh.hpp"
#include "scene.hpp"
#include "shaders.hpp"
#include "time.hpp"
#include "transform.hpp"

void Player::Setup(Scene& scene) {
    //;
    scene.AddComponent<Transform>(*this);
    Mesh* mesh = scene.AddComponent<Mesh>(*this);

    std::array<float, 65535> vertices = {
        0.5f,
        0.5f,
        0.0f,  // top right
        0.5f,
        -0.5f,
        0.0f,  // bottom right
        -0.5f,
        -0.5f,
        0.0f,  // bottom left
        -0.5f,
        0.5f,
        0.0f  // top left
    };
    std::array<unsigned int, 6> indices = {
        // note that we start from 0!
        0,
        1,
        3,  // first triangle
        1,
        2,
        3  // second triangle
    };

    mesh->SetMesh(vertices, indices);
    mesh->SetShader(SHADER_tutorial_vert, SHADER_tutorial_frag);
}
