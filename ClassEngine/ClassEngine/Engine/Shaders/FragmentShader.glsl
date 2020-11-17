#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fColour;

struct Material {
	sampler2D diffuseMap;
    float shininess; // Ns
    float transparency; //d
    vec3 ambient; //Ka
    vec3 diffuse; //Kd
    vec3 specular; //Ks
};

uniform Material material;

struct Light {
	vec3 lightPos;
	float ambient;
	float diffuse;
	vec3 lightColour;
};

//uniform sampler2D inputTexture;
uniform Light light;
uniform vec3 viewPosition;

void main()
{

    //ambient
    vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;
    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.lightPos - FragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse)* texture(material.diffuseMap, TexCoords).rgb * light.lightColour;
    //specular
	//float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.lightColour;

    vec3 result = ambient + diffuse + specular;

    fColour = vec4(result, 0.8f);

}