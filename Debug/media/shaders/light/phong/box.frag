#version 450 core

in vec3 Normal;
in vec3 FragPos;
out vec4 fColor;

uniform sampler2D OurTexture0;
uniform sampler2D OurTexture1;
uniform vec3 LightPos;

uniform vec3 LightColor;

uniform vec3 ViewPos;

void main()
{
	float ambientStrength = 0.1f;
	float specularStrength = 0.5f;
	
	vec3 ambient = ambientStrength * LightColor;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * LightColor;
	
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * LightColor;
    fColor = vec4(ambient + diffuse + specular, 1.0f) * vec4(1.0, 0.5, 0.31, 1);
}
