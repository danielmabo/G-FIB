#version 330 core

// IDI: glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

uniform vec3 boundingBoxMin;// cantonada de la capsa englobant
uniform vec3 boundingBoxMax;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
vec3 VRP;
mat4 TG;


void calcVRP(){
    VRP = vec3 ((boundingBoxMin.x + boundingBoxMax.x)/2.0,
                (boundingBoxMin.y + boundingBoxMax.y)/2.0,
                (boundingBoxMin.z + boundingBoxMax.z)/2.0);
}

void calcTG(){
    calcVRP();
    //TG = mat4(1.);
    TG = mat4 ( vec4(1,0,0,0),
                vec4(0,1,0,0),
                vec4(0,0,1,0),
                vec4(0,0,0,1));
    TG = TG -  mat4(vec4(0,0,0,0),
                    vec4(0,0,0,0),
                    vec4(0,0,0,0),
                    vec4(VRP, 0));
}

void main(){

    /*TG = mat4 (vec4(1,0,0,5),
               vec4(0,1,0,5),
               vec4(0,0,1,5),
               vec4(0,0,0,1));
    TG = transpose(TG);
    */
    calcTG();

    vec3 N      = normalize(normalMatrix * normal);
    frontColor  = vec4(N.z, N.z, N.z, 1); //vec4(N.z);
    vtexCoord   = texCoord;
    gl_Position = projectionMatrix * viewMatrix * TG * vec4(vertex, 1.0);
}






//TG = glm::translate(TG, posPatricioTerra);
//TG = glm::scale(TG, glm::vec3(escala, escala, escala));
//TG = glm::translate(TG, -centrePatr);
