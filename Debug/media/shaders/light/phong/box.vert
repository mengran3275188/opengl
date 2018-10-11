
#version 450 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void
main()
{
    gl_Position = projection * view * model * vec4(vPosition, 1.0f);
	FragPos = vec3(view * model * vec4(vPosition, 1.0f));
	Normal = mat3(transpose(inverse(view * model))) * vNormal;
}