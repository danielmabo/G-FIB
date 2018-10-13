#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D explosion;

uniform float time;

const float slice = 1./30.;
const float maxFrame = 48.;
const float maxS = 8.;
const float maxT = 6.;
const float dS = 1./maxS;
const float dT = 1./maxT;
const float coordIniT = (1 - dT); //Comencem per dalt

void main(){
    float currentSlice = mod(floor(time / slice), maxFrame);
    float incrementS = mod(currentSlice, maxS);
    float incrementT = float(int(currentSlice)/int(maxS));
    float coordS = dS * vtexCoord.s + incrementS * dS;
    float coordT = coordIniT + dT * vtexCoord.t  - incrementT * dT;

    fragColor = frontColor * texture(explosion, vec2(coordS, coordT));
    fragColor = fragColor.w * fragColor;
}
