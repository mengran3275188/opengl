#version 450 core

in vec4 Color;
out vec4 fColor;

uniform sampler2D OurTexture0;
uniform sampler2D OurTexture1;

void main()
{
    fColor = Color * vec4(1.0, 0.5, 0.31, 1);
}
