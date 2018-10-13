#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
 

uniform float t;
uniform float scale;


void main()
{
    //Calculem color
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    
    //Calculem c com una interpolacio entre el minim i el maxim i el parametre t
    float c = mix(boundingBoxMin.y, boundingBoxMax.y, t);
    vec3 vertexDeform = vertex;
    
    //Calculem la traslacio que s'haura de fer si no s'escala
    float tras = (scale -1.) * c;
    
    //Escalem per sota el valor limit (nomes comp Y)
    if (vertex.y < c)
        vertexDeform.y = scale * vertex.y;
    //Traslladem per sobre el valor limit nomes en Y
    else
        vertexDeform.y = tras + vertex.y;
    
    //Apliquem transf de model, i camera
    gl_Position = modelViewProjectionMatrix * vec4(vertexDeform, 1.0);
}
