#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform int textureSize = 1024;
uniform int edgeSize = 2;
uniform float threshold = 0.1;

uniform sampler2D sampler;

void main(){
    vec4 colorBlack = vec4(0., 0., 0., 1.);
    vec2 left   = vtexCoord + edgeSize * vec2(-1., 0.) / textureSize;
    vec2 right  = vtexCoord + edgeSize * vec2(1., 0.) / textureSize;
    vec2 top    = vtexCoord + edgeSize * vec2(0., 1.) / textureSize;
    vec2 bottom = vtexCoord + edgeSize * vec2(0., -1.) / textureSize;

    float Gx = length(texture(sampler, right) - texture(sampler, left));
    float Gy = length(texture(sampler, top) - texture(sampler, bottom));
    float colorChange = length(vec2(Gx, Gy));

    if (colorChange > threshold)
        fragColor = colorBlack;
    else
        fragColor = texture(sampler, vtexCoord);
}
