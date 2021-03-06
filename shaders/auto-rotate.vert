#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;
uniform float speed;

mat4 rotateY(float phi){
    return transpose( mat4 (vec4(cos(phi),0.,sin(phi),0.),
                            vec4(0.,1.,0.,0.),
                            vec4(-sin(phi),0,cos(phi),0),
                            vec4(0,0,0,1)));
}

void main()
{
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;

    float phi = speed * time;
    mat4 RY = rotateY(phi);

    vec4 vertexRotated = RY * vec4(vertex, 1.0);
    gl_Position = modelViewProjectionMatrix * vertexRotated;

}
