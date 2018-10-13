#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 vertObj;

uniform mat4 modelViewProjectionMatrix;


void main()
{
    vertObj =  vec4(vertex, 1.0);
    gl_Position = modelViewProjectionMatrix * vertObj;
}
