#version 330 core

in vec4 frontColor;
in vec3 vEye;
in vec3 nEye;
out vec4 fragColor;

uniform float epsilon = 0.1;
uniform float light = 0.5;
uniform vec4 colorDarkYell = vec4(.7, .6, 0., 1.);

void main(){
    float dotVN = abs(dot(normalize(vEye), normalize(nEye)));
    if (dotVN < epsilon)
        fragColor = colorDarkYell;
    else
        fragColor = frontColor * light * nEye.z;

}
