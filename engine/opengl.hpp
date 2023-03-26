#ifndef ELGINE_ENGINE_LIB_OPENGL_HPP_
#define ELGINE_ENGINE_LIB_OPENGL_HPP_

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
// #include <OpenGL/OpenGL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#endif  // ELGINE_ENGINE_LIB_OPENGL_HPP_
