#version 410 core

out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

uniform vec3 viewPos;
uniform vec3 sunPos;

uniform DirLight dirLight;
uniform Material material;

uniform sampler2D ourTexture;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb * material.ambient;

    vec3 lightDir = normalize(sunPos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = light.specular * spec * texture(material.diffuse, TexCoord).rgb;

    return (ambient + diffuse);
}

void main()
{
    vec3 result = vec3(0.0);
    
    result += CalcDirLight(dirLight, Normal, normalize(viewPos - FragPos), FragPos);
    FragColor = vec4(result, 1.0);
} 
