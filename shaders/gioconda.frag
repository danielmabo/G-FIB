#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D sampler;

void main()
{
    vec2 centerEye = vec2(0.393, 0.652);
    vec2 centerMouth = vec2(0.45, 0.48);
    vec2 dist = centerEye - centerMouth;
    float r = 0.025;
    float coordS = vtexCoord.s;
    float coordT = vtexCoord.t;
    if (fract(time) > 0.5 && distance(vtexCoord, centerEye) <= r){
        coordS = vtexCoord.s - dist.s;
        coordT = vtexCoord.t - dist.t;
    }

    fragColor = texture(sampler, vec2(coordS, coordT));
}
