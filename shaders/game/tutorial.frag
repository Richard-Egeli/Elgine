#version 410 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture0;

void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0); // texture(texture0, TexCoord);
}
