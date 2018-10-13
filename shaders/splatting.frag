#version 330 core

out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()
{
    float coordS = vtexCoord.s;
    float coordT = vtexCoord.t;
    
    vec4 grass = texture(grass2, vec2(coordS, coordT));
    vec4 rock  = texture(rock1, vec2(coordS, coordT));
    float noise = texture(noise0, vec2(coordS, coordT)).r;

    fragColor = mix(rock, grass, noise);
}
