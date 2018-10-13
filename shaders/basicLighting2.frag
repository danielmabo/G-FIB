#version 330 core

out vec4 fragColor;

in vec3 normal_v;
in vec3 color_v;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec3 N = normalize(normalMatrix * normal_v);
    fragColor = vec4(color_v,1.0) * N.z;
}
