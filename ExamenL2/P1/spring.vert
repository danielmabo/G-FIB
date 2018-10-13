#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z, N.z, N.z, 1);
    float temps = mod(time, 3.5);
    vec3 vOrig = vec3(0.,0.,0.);
    vec3 vertexTras;
    if (temps <= 0.5){
        float interp = pow(temps/0.5, 3);
        vertexTras = mix(vOrig, vertex, interp);
    }
    else {
        float interp = (temps - 0.5)/3.;
        vertexTras = mix(vertex, vOrig, interp);
    }
    gl_Position = modelViewProjectionMatrix * vec4(vertexTras, 1.0);
}
