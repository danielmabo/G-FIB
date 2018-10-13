#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float amplitude;
uniform float freq;
uniform float time;
uniform float Pi;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z, N.z, N.z, 1); //vec4(N.z);
    vtexCoord = texCoord;
    vec3 traslacio = normalize(normal) * (amplitude * sin(2 * Pi * freq * time));
    vec3 vertexTras = vertex + traslacio;
    gl_Position = modelViewProjectionMatrix * vec4(vertexTras, 1.0);
}