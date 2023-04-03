#include "shader-library.hpp"

const char* SHADER_sun_frag = "#version 410 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"FragColor = vec4(1.0);\n"
"}";

const char* SHADER_default_vert = "\n"
"#version 410 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 FragPos;\n"
"out vec3 Normal;\n"
"out vec2 TexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"FragPos = vec3(model * vec4(aPos, 1.0));\n"
"Normal = mat3(transpose(inverse(model))) * aNormal; \n"
"TexCoord = aTexCoord; \n"
"gl_Position = projection * view * vec4(FragPos, 1.0);\n"
"}";

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
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
"FragColor = texture(ourTexture, TexCoord);\n"
"}";

const char* SHADER_default_frag = "#version 410 core\n"
"out vec4 FragColor;\n"
"in vec3 FragPos;  \n"
"in vec3 Normal;  \n"
"in vec2 TexCoord;\n"
"struct DirLight {\n"
"vec3 direction;\n"
"vec3 ambient;\n"
"vec3 diffuse;\n"
"vec3 specular;\n"
"};\n"
"struct Material {\n"
"vec3 ambient;\n"
"sampler2D diffuse;\n"
"vec3 specular;\n"
"float shininess;\n"
"};\n"
"uniform vec3 viewPos;\n"
"uniform vec3 sunPos;\n"
"uniform DirLight dirLight;\n"
"uniform Material material;\n"
"uniform sampler2D ourTexture;\n"
"vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 fragPos)\n"
"{\n"
"vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb * material.ambient;\n"
"vec3 lightDir = normalize(sunPos - fragPos);\n"
"float diff = max(dot(normal, lightDir), 0.0);\n"
"vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;\n"
"return (ambient + diffuse);\n"
"}\n"
"void main()\n"
"{\n"
"vec3 result = vec3(0.0);\n"
"result += CalcDirLight(dirLight, Normal, normalize(viewPos - FragPos), FragPos);\n"
"FragColor = vec4(result, 1.0);\n"
"} ";

const char* SHADER_sun_vert = "#version 410 core\n"
"layout (location = 0) in vec3 position;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"gl_Position = projection * view * model * vec4(position, 1.0f);\n"
"}";

