#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;

uniform float slice = 0.1;
uniform float time;

const float maxSample = 4.;

void main(){
    float currentSample = mod(floor(time / slice), maxSample);
    switch (int(currentSample)) {
        case 0:
            fragColor = frontColor * texture(sampler0, vtexCoord);
            break;
        case 1:
            fragColor = frontColor * texture(sampler1, vtexCoord);
            break;
        case 2:
            fragColor = frontColor * texture(sampler2, vtexCoord);
            break;
        case 3:
            fragColor = frontColor * texture(sampler3, vtexCoord);
            break;
    }
}
