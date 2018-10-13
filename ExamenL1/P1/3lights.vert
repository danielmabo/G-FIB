#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;


out vec3 normal_v;
out vec3 vertex_v;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    //Enviem normal i vertex en objectSpace al FS
	normal_v = normal;
	vertex_v = vertex;
	gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
