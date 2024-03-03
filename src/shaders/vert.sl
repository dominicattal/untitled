#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCol;

out vec2 Col;

uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * vec4(aPos, 1.0f);
    Col = aCol;
}