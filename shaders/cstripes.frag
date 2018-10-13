#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform int nstripes;
uniform vec2 origin;

const vec4 colorRed = vec4(1., 0., 0., 1.);
const vec4 colorYel = vec4(1., 1., 0., 1.);

void main()
{
    float a = (1./nstripes);
    float l = length(vtexCoord - origin); //La funcio length fa la norma del vec
    if (mod(l, 2*a) < a){
        fragColor = colorRed;
    }
    else
        fragColor = colorYel;
}
