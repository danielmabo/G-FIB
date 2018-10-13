#version 330 core

out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;

void main()
{
    float coordS = vtexCoord.s;
    float coordT = vtexCoord.t;

    vec4 grass = texture(sampler2, vec2(coordS, coordT));
    vec4 rock  = texture(sampler1, vec2(coordS, coordT));
    float noise = texture(sampler0, vec2(coordS, coordT)).r;

    fragColor = mix(rock, grass, noise);
}
