#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;


void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    
    //Sobre el model cada vertex es com un "vector" que surt del origen per tant si volem que
    //Tots estiguin a radi unitat nomes cal nomralitzar perque el modul (distancia) sigui 1.
    gl_Position = modelViewProjectionMatrix * vec4(normalize(vertex), 1.0);

}
