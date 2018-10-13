#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec2 vtexCoord;
out vec4 vertexObj;
out vec3 normalObj;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    //Passem el vertex i la normal en OBject Space
    vertexObj = vec4(vertex, 1.);
    normalObj = normal;

    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
