#include "shaders.hpp"

const char* SHADER_tutorial_vert = "#version 410 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"TexCoord = aTexCoord;\n"
"}";

const char* SHADER_tutorial_frag = "#version 410 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D texture0;\n"
"uniform sampler2D texture1;\n"
"void main()\n"
"{\n"
"FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);\n"
"}";

