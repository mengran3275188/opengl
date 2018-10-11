
#version 450 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;

out vec4 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightpos;


void
main()
{
    gl_Position = projection * view * model * vec4(vPosition, 1.0f);
	
	vec3 lightColor = vec3(1, 1, 1);
	float ambientStrength = 0.1f;
	float specularStrength = 0.5f;
	vec3 ambient = ambientStrength * lightColor;
	
	vec3 FragPos = vec3(view * model * vec4(vPosition, 1.0f));
	vec3 Normal = mat3(transpose(inverse(view * model))) * vNormal;
	vec3 viewLightPos = vec3(view * vec4(lightpos, 1));
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(viewLightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
    Color = vec4(ambient + diffuse + specular, 1.0f) * vec4(1.0, 0.5, 0.31, 1);
}
