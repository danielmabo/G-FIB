#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec2 vtexCoord;
out vec4 vertexEye;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

mat4 rotateY(float phi){
    return transpose( mat4 (vec4(cos(phi),0.,-sin(phi),0.),
                            vec4(0.,1.,0.,0.),
                            vec4(sin(phi),0,cos(phi),0),
                            vec4(0,0,0,1)));
}

void main(){
    float speed = 0.1;
    vtexCoord = texCoord;
    //SCM -> Object Space apliquem la rotacio
    vec4 vertexRot = rotateY(speed * time) * vec4(vertex, 1.);
    //SCO -> Eye space per al FS
    vertexEye = modelViewMatrix * vertexRot;
    //Tornem glPos en coordenades de clipping com sempre!!!
    gl_Position = projectionMatrix * vertexEye;
}
