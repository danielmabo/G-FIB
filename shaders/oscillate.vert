#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform float time;
uniform bool eyespace;
const float Pi = 3.141592;
const float period = 2 * Pi;

float boundingBoxDigonal(){
    return sqrt(pow(boundingBoxMax.x-boundingBoxMin.x, 2.) +
                pow(boundingBoxMax.y-boundingBoxMin.y, 2.) +
                pow(boundingBoxMax.z-boundingBoxMin.z, 2.));
}

void main(){
    //SCO = Eye Space		-> Vector ja multiplicat per ModelTrans(TG) i ViewTrans(VM)
    //SCA = World Space		-> Vector ja multiplicat per ModelTrans(TG)
    //SCM = Object Space	-> Vector sense multiplicar
    vec3 N = normalize(normal);
    frontColor = vec4(color,1.0);
    float valueY = vertex.y;
    if (eyespace){
        valueY = (modelViewMatrix * vec4(vertex, 1.0)).y;
    }
    float d = valueY * (boundingBoxDigonal()/2) / 10;
    vec3 vertOsc = vertex + d * sin(2 * Pi * time / period) * N;

    gl_Position = modelViewProjectionMatrix * vec4(vertOsc, 1.0);
}
