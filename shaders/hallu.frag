#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D map;
uniform float time;
uniform float a = 0.5;
const float PI = 3.141592;

mat2 rotate2D(float phi){
    return transpose( mat2(vec2(cos(phi),sin(phi)),
                           vec2(-sin(phi),cos(phi))));
}

void main()
{
    vec4 texColor = texture(map, vtexCoord);
    float m = max(texColor.x, max(texColor.y, texColor.z));
    vec2 u = vec2(m, m);
    float phi = 2 * PI * time;
    vec2 offset = (a / 100.) * rotate2D(phi) * u;
    fragColor = texture(map, vtexCoord + offset);
}
