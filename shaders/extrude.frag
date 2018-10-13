#version 330 core

in vec3 gNormal;
out vec4 fragColor;

uniform mat3 normalMatrix;

const float alphaG = 0.7;
const vec4 colorGrey = vec4(alphaG, alphaG, alphaG, 1.);

void main()
{
    fragColor = colorGrey * normalize(normalMatrix * gNormal).z;
}
