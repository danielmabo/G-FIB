#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;
out float topFace;
out vec3 gNormal;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float step = 0.2;

void pintarCara(vec4 v1, vec4 v2, vec4 v3, vec4 v4, float isTop, vec3 N){
    gfrontColor = (vfrontColor[0] + vfrontColor[1] + vfrontColor[2]) / 3.;
    topFace = isTop;
    gNormal = N;
	gl_Position = modelViewProjectionMatrix * v1;
    gtexCoord = vec2(1., 0.);
	EmitVertex();
    gfrontColor = (vfrontColor[0] + vfrontColor[1] + vfrontColor[2]) / 3.;
    topFace = isTop;
    gNormal = N;
	gl_Position = modelViewProjectionMatrix * v2;
    gtexCoord = vec2(1., 1.);
	EmitVertex();
    gfrontColor = (vfrontColor[0] + vfrontColor[1] + vfrontColor[2]) / 3.;
    topFace = isTop;
    gNormal = N;
	gl_Position = modelViewProjectionMatrix * v3;
    gtexCoord = vec2(0., 0.);
	EmitVertex();
    gfrontColor = (vfrontColor[0] + vfrontColor[1] + vfrontColor[2]) / 3.;
    topFace = isTop;
    gNormal = N;
	gl_Position = modelViewProjectionMatrix * v4;
    gtexCoord = vec2(0., 1.);
	EmitVertex();
	EndPrimitive();
}

void main( void ){
    vec4 BT = vec4(round((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position).xyz/(3*step)) * step, 1.0);


    float r = step /2.;
    vec4 v1 = BT + vec4( r,  r,  r, 1.0);
    vec4 v2 = BT + vec4(-r,  r,  r, 1.0);
	vec4 v3 = BT + vec4( r, -r,  r, 1.0);
    vec4 v4 = BT + vec4(-r, -r,  r, 1.0);
	vec4 v5 = BT + vec4( r,  r, -r, 1.0);
    vec4 v6 = BT + vec4(-r,  r, -r, 1.0);
	vec4 v7 = BT + vec4( r, -r, -r, 1.0);
    vec4 v8 = BT + vec4(-r, -r, -r, 1.0);
    vec3 N;
    //Aquesta distribucio de cares es deguda a que la cara de sobre es la direccioY en openGL i Z es la profunditat
    //RIGHT
    N = normalize(normalMatrix * vec3(1.,0.,0.));
    pintarCara(v1, v2, v3, v4, 0, N);
    //LEFT
    N = normalize(normalMatrix * vec3(-1.,0.,0.));
    pintarCara(v5, v6, v7, v8, 0, N);
    //FRONT
    N = normalize(normalMatrix * vec3(0.,0.,1.));
    pintarCara(v1, v3, v5, v7, 0, N);
    //BACK
    N = normalize(normalMatrix * vec3(0.,0.,-1.));
    pintarCara(v2, v4, v6, v8, 0, N);
    //TOP
    N = normalize(normalMatrix * vec3(0.,1.,0.));
    pintarCara(v1, v2, v5, v6, 1, N);
    //BOTTOM
    N = normalize(normalMatrix * vec3(0.,-1.,0.));
    pintarCara(v2, v3, v7, v8, 0, N);
}
