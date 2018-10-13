#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void emitFloor(){
    float plaY = boundingBoxMin.y - 0.01;
    vec4 colorCian = vec4(0., 1., 1., 1.);
    float R = distance(boundingBoxMax, boundingBoxMin)/2.;
    vec3 boundingBoxCenter = (boundingBoxMax + boundingBoxMin)/2.;
    vec4 vertexFloor1 = vec4(boundingBoxCenter.x - R , plaY, boundingBoxCenter.z - R ,1.);
    vec4 vertexFloor2 = vec4(boundingBoxCenter.x - R , plaY, boundingBoxCenter.z + R ,1.);
    vec4 vertexFloor3 = vec4(boundingBoxCenter.x + R , plaY, boundingBoxCenter.z + R ,1.);
    vec4 vertexFloor4 = vec4(boundingBoxCenter.x + R , plaY, boundingBoxCenter.z - R ,1.);
    gfrontColor = colorCian;
    gl_Position = modelViewProjectionMatrix * vertexFloor1;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vertexFloor2;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vertexFloor4;
    EmitVertex();
    EndPrimitive();
    gl_Position = modelViewProjectionMatrix * vertexFloor2;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vertexFloor3;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vertexFloor4;
    EmitVertex();
    EndPrimitive();
}

void main( void ){
    vec4 colorBlack = vec4(0., 0., 0., 1.);
    if (gl_PrimitiveIDIn == 0){
        emitFloor();
    }

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
