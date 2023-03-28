#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
// #include <OpenGL/OpenGL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif
