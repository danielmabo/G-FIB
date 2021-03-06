#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float n;
//El color s'ha obtingut fent proves amb els test realment per l'enunciat havia de ser (1.,1.,1.)
const vec4 colorWhite = vec4(.8, .8, .8, 1.);
const vec4 colorBlack = vec4(0., 0., 0., 1.);

void main()
{
    //Les coord de textura van entre [0..1] per tant hem de dividir entre 1/n
    //per fer parts i si aquella part mod 2 es 0 pintem blanc sino negre
    float step = 1./n;
    float amplitude = 0.1;
    //Primer escalem i  fem el modul mirar el quadrant (color) i per comparar
    //els colors si que s'ha de passar a enter, el valor 0.1 es va posar aleatoriament
    //(conceptualment potser te mse sentit que el gruix sigui el step pero quan escales
    //els pixels aleshores no surt constant)
    if (fract(mod(vtexCoord.s / step, 2)) < amplitude || fract(mod(vtexCoord.t / step, 2)) < amplitude){
        fragColor = colorBlack;
    }
    else
        fragColor = colorWhite;
}
