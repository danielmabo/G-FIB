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

    //LA MANERA STANDARD D'APLICAR GRADIENTS ES FER_HO ENTRE 0..1

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

    float amplitude_interval = (boundingBoxMax.y - boundingBoxMin.y)/n;
    int i = int((vertex.y-boundingBoxMin.y)/amplitude_interval);
    float percent = fract((vertex.y-boundingBoxMin.y)/amplitude_interval);

    vec3 color_out = mix(color_interp[i], color_interp[i+1], percent);
    
    frontColor = vec4(color_out,1.0) ;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
