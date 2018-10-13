#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;


void emmitCara(vec4 v1, vec4 v2, vec4 v3, vec4 v4 ,vec4 color){
	gfrontColor = color;
	gl_Position = v1;
	EmitVertex();
    gfrontColor = color;
	gl_Position = v2;
	EmitVertex();
    gfrontColor = color;
	gl_Position = v3;
	EmitVertex();
    gfrontColor = color;
	gl_Position = v4;
	EmitVertex();
	EndPrimitive();
}

void boundingBoxPrimitives(){
	vec3 N;
	vec4 color;
	vec4 P;
	vec4 v1 = modelViewProjectionMatrix * vec4(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMin.z,1.);
	vec4 v2 = modelViewProjectionMatrix * vec4(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMin.z,1.);
	vec4 v3 = modelViewProjectionMatrix * vec4(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMax.z,1.);
	vec4 v4 = modelViewProjectionMatrix * vec4(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMax.z,1.);
	vec4 v5 = modelViewProjectionMatrix * vec4(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMin.z,1.);
	vec4 v6 = modelViewProjectionMatrix * vec4(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMin.z,1.);
	vec4 v7 = modelViewProjectionMatrix * vec4(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMax.z,1.);
	vec4 v8 = modelViewProjectionMatrix * vec4(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMax.z,1.);

	//Cara 1
	N = normalize(normalMatrix * vec3(1.,0.,0.));
	color = vec4(1.,0.,0.,1.); //RED
	P = normalize(modelViewMatrix * vec4(boundingBoxMax,1.));
	if (dot(P.xyz, N) > 0){
		emmitCara(v4, v8,  v2, v6 , color);
	}
	//Cara 2
	N = normalize(normalMatrix * vec3(-1.,0.,0.));
	color = vec4(1.,0.,0.,1.); //RED
	P = normalize(modelViewMatrix * vec4(boundingBoxMin,1.));
	if (dot(P.xyz, N) > 0){
		emmitCara(v7, v3, v5, v1 , color);
	}
	//Cara 3
	N = normalize(normalMatrix * vec3(0.,0.,1.));
	color = vec4(0.,0.,1.,1.); //Blue
	P = normalize(modelViewMatrix * vec4(boundingBoxMax,1.));
	if (dot(P.xyz, N) > 0){
		emmitCara(v7, v3,  v8,  v4 , color);
	}
	//Cara 4
	N = normalize(normalMatrix * vec3(0.,0.,-1.));
	color = vec4(0.,0.,1.,1.); //Blue
	P = normalize(modelViewMatrix * vec4(boundingBoxMin,1.));
	if (dot(P.xyz, N) > 0){
		emmitCara(v5, v1,  v6,  v2 , color);
	}
	//Cara 5
	N = normalize(normalMatrix * vec3(0.,1.,0.));
	color = vec4(0.,1.,0.,1.); //Green
	P = normalize(modelViewMatrix * vec4(boundingBoxMax,1.));
	if (dot(P.xyz, N) > 0){
		emmitCara(v5, v6,  v7,  v8 , color);
	}
	//Cara 6
	N = normalize(normalMatrix * vec3(0.,-1.,0.));
	color = vec4(0.,1.,0.,1.); //Green
	P = normalize(modelViewMatrix * vec4(boundingBoxMin,1.));
	if (dot(P.xyz, N) > 0){
		emmitCara(v1, v2,  v3,  v4 , color);
	}

}



void main( void ){
	if (gl_PrimitiveIDIn == 0)
		boundingBoxPrimitives();
	for (int i = 0 ; i < 3 ; i++ ){
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}
