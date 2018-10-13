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
const float angSpeed = 8.0;

mat4 explodeTransl(){
    vec3 normalMix = speed * time * (normalObj[0] + normalObj[1] + normalObj[2])/3;
    return mat4 (vec4(1.,0.,0.,0.),
                 vec4(0.,1.,0.,0.),
                 vec4(0.,0.,1.,0.),
                 vec4(normalMix,1.));
}

mat4 explodeRotZ(){
    float phi = angSpeed * time;
    return transpose( mat4 (vec4(cos(phi),-sin(phi),0.,0.),
                            vec4(sin(phi),cos(phi),0.,0.),
                            vec4(0.,0.,1.,0.),
                            vec4(0,0,0,1)));
}

void main( void ){
    mat4 TG = explodeTransl();
    mat4 RZ = explodeRotZ();
    //Calculem el centre del triangle, ja que rotarem respecte aquell centre cada punt!
    vec4 BT = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3;
	for (int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
        vec4 vertexRotat = BT + RZ * (gl_in[i].gl_Position - BT);
		gl_Position = modelViewProjectionMatrix * TG * vertexRotat;
		EmitVertex();
	}
    EndPrimitive();
    
}
