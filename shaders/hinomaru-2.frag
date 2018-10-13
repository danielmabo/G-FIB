#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform bool classic = false;
const float PI = 3.141592;

void main()
{
    vec4 colorRed = vec4(1., 0., 0., 1.);
    vec4 colorWhite = vec4(1., 1., 1., 1.);
    vec2 centerFrag = vec2(0.5, 0.5);
    float r = 0.2;
    float d = distance(vtexCoord.st, centerFrag); //distance(x,y)
    if (classic){
        if (d <= r)
            fragColor = colorRed;
        else
            fragColor = colorWhite;
    }
    else {
        float phi = PI/16.;
        vec2 direction = vtexCoord - centerFrag;
        float theta = atan(direction.t, direction.s);
        if (d <= r || mod(theta/phi + 0.5, 2.) < 1.)
            fragColor = colorRed;
        else
            fragColor = colorWhite;
    }

}
