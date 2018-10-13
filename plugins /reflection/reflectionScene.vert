#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;

uniform vec4 planeVec1;
uniform vec4 planeVec2;
uniform vec4 planePoint;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

mat4 reflectionMatrix(vec4 v1, vec4 v2, vec4 p){
    vec4 vN = normalize(dot(v1, v2));
    float a = vN.x;
    float b = vN.y;
    float c = vN.z;
    float d = - (vN.xyz * p);
    return transpose( mat4 (vec4(1-2*a*a,-2*b*a,-2*c*a,-2*d*a),
                            vec4(-2*a*b,1-2*b*b,-2*c*b,-2*d*b),
                            vec4(-2*a*c,-2*b*c,1-2*c*c,-2*d*c),
                            vec4(0,0,0,1)));
}

void main(){
    mat4 RM = reflectionMatrix(modelViewMatrix * planeVec1, modelViewMatrix * planeVec2, modelViewMatrix * planePoint);
    frontColor = vec4(abs(normal),0.25);
    gl_Position = projectionMatrix * RM * modelViewMatrix * vec4(vertex,1.0);
}
