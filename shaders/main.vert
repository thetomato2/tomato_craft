#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_coord;

out vec2 tex_coord;

uniform mat4 model;
uniform mat4 vp;


void main()
{
   gl_Position = vp * model * vec4(a_pos, 1.0f);
   tex_coord = a_tex_coord;
};