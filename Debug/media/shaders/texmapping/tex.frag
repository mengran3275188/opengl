#version 450 core

in vec2 TexCoord;

out vec4 fColor;

uniform sampler2D OurTexture0;
uniform sampler2D OurTexture1;

void main()
{
    fColor = mix(texture(OurTexture0, TexCoord), texture(OurTexture1, TexCoord), 0.2);
}
