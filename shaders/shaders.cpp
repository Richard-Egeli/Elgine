#include "shaders.hpp"

const char* SHADER_tutorial_vert = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}";

const char* SHADER_tutorial_frag = "#version 150\n"
"precision highp float;\n"
"in  vec3 ex_Color;\n"
"out vec4 gl_FragColor;\n"
"void main(void) {\n"
"gl_FragColor = vec4(ex_Color,1.0);\n"
"}";

