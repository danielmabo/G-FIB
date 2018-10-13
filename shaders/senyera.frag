#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float n;
const vec4 colorRed = vec4(1., 0., 0., 1.);
const vec4 colorYel = vec4(1., 1., 0., 1.);

void main()
{
    float a = 1./9.;
    float f = fract(vtexCoord.s);
    if (mod(f, 2*a) < a){
        fragColor = colorYel;
    }
    else
        fragColor = colorRed;
}
