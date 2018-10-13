#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 normalObj[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float step = 0.2;

void pintarCara(vec4 v1, vec4 v2, vec4 v3, vec4 v4){
    gfrontColor = vfrontColor[0];
	gl_Position = modelViewProjectionMatrix * v1;
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * v2;
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * v3;
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * v4;
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
    //TOP
    pintarCara(v1, v2, v3, v4);
    //BOTTOM
    pintarCara(v5, v6, v7, v8);
    //FRONT
    pintarCara(v1, v3, v5, v7);
    //BACK
    pintarCara(v2, v4, v6, v8);
    //RIGHT
    pintarCara(v1, v2, v5, v6);
    //LEFT
    pintarCara(v2, v3, v7, v8);
}
