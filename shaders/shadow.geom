#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;

void main( void ){
    vec4 colorBlack = vec4(0., 0., 0., 1.);
	for (int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

    for (int i = 0 ; i < 3 ; i++ ){
        gfrontColor = colorBlack;
        vec4 vertexPla = gl_in[i].gl_Position;
        vertexPla.y = boundingBoxMin.y;
        gl_Position = modelViewProjectionMatrix * vertexPla;
		EmitVertex();
	}
    EndPrimitive();
}
