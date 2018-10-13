#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 normalObj[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform float time;
//Per al test, per al video 1.2
const float speed = 0.5;

mat4 explodeTransl(){
    vec3 normalMix = speed * time * (normalObj[0] + normalObj[1] + normalObj[2])/3;
    return mat4 (vec4(1.,0.,0.,0.),
                 vec4(0.,1.,0.,0.),
                 vec4(0.,0.,1.,0.),
                 vec4(normalMix,1.));
}

void main( void ){
    mat4 TG = explodeTransl();
	for (int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * TG * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
