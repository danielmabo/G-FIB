#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrixInverse;


uniform vec4 lightPosition;

uniform float n = 4;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z, N.z, N.z, 1); //vec4(N.z);
    vtexCoord = texCoord;

    vec4 lightPositionSCM = modelViewMatrixInverse * lightPosition;
    float distN = pow(distance(vertex, lightPositionSCM.xyz), n);
    float w = clamp(1./distN, 0, 1);

    vec4 vertexTras = (1. - w) * vec4(vertex, 1.0) + w * lightPositionSCM;
    gl_Position = modelViewProjectionMatrix * vertexTras;
}
