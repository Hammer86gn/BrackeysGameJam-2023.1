#version 400 core

out vec4 fragment_color;

in vec2 texture_coord;
in vec3 color;

uniform sampler2D utexture; // We use a white texture to denote a simple color. This will allow us to store less shaders.

void main()
{
    fragment_color = texture(utexture, texture_coord) * vec4(color, 1.0);
}


