#version 410 core

out vec4 FragColor;

in vec3 Normal;  
in vec2 TexCoords;
in vec3 FragPos;  

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
  
uniform vec3 viewPos;

uniform DirectionalLight dirLight;
uniform PointLight pointLight;
uniform Material material;

float calculate_point_light_strength() {
    float distance = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
    return attenuation;
}

void main()
{
    vec3 ambient = dirLight.ambient *  material.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-dirLight.direction);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = dirLight.diffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = dirLight.specular * (spec * material.specular);  

    vec3 result = ambient + diffuse;
    FragColor = vec4(result, 1.0);
} 
