#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float n;
const vec4 colorWhite = vec4(.8, .8, .8, 1.);
const vec4 colorBlack = vec4(0., 0., 0., 1.);

void main()
{
    //Les coord de textura van entre [0..1] per tant hem de dividir entre 1/n
    //per fer parts i si aquella part mod 2 es 0 pintem blanc sino negre
    float step = 1./n;

    //Primer escalem i  fem el modul mirar el quadrant (color) i per comparar
    //els colors si que s'ha de passar a enter
    if (int(mod(vtexCoord.s / step, 2)) == int(mod(vtexCoord.t / step, 2))){
        fragColor = colorWhite;
    }
    else
        fragColor = colorBlack;
}
