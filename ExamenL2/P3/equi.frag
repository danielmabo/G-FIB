#version 330 core

in vec4 vertObj;
out vec4 fragColor;

uniform sampler2D panorama; 
const float PI = 3.141592;  


void main()
{
    float phi = asin(vertObj.y);
    float theta = atan(vertObj.z, vertObj.x);
    vec2 st = vec2(theta/(2*PI), phi/PI + 0.5);
    fragColor = texture(panorama, st);
}
