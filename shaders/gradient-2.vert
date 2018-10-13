#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main(){
    float n = 4.;
    vec3 C_red   = vec3(1.,0.,0.);
    vec3 C_yell  = vec3(1.,1.,0.);
    vec3 C_green = vec3(0.,1.,0.);
    vec3 C_cian  = vec3(0.,1.,1.);
    vec3 C_blue  = vec3(0.,0.,1.);
    vec3 color_interp[5] = vec3[](C_red,
                                  C_yell,
                                  C_green,
                                  C_cian,
                                  C_blue);

    //X,Y,Z en coord normalitzades van ente [-1,1]
    float yMax =  1.;
    float yMin = -1.;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    vec3 vertex_homogeneous = (gl_Position/gl_Position.w).xyz; //x,y,z van entre [-1,1]
    float amplitude_interval = (yMax - yMin)/n;
    int i = int((vertex_homogeneous.y - yMin)/amplitude_interval);
    float percent = fract((vertex_homogeneous.y - yMin)/amplitude_interval);
    vec3 color_out = mix(color_interp[i], color_interp[i+1], percent);
    frontColor = vec4(color_out,1.0);
}
