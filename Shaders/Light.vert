#version 400 core

layout (location = 0) in vec3 position;


out float size;

void main()
{
    size = 0.2;
    gl_Position = vec4(position, 1.0);
}