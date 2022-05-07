
#version 330 core

layout (location = 0) in vec3 a_pos;

uniform mat4 model;
uniform mat4 vp;


void main()
{
   gl_Position = vp * model * vec4(a_pos, 1.0f);
};