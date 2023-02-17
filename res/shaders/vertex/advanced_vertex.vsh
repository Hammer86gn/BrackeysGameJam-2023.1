#version 400 core

layout ( location = 0 ) in vec3 pos;
layout ( location = 1 ) in vec3 color;
layout ( location = 2 ) in vec2 t_coord;

out vec2 texture_coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main()
{
    gl_Position = projection * view * transform * vec4( pos, 1.0 );
    texture_coord = t_coord;
}