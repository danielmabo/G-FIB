#version 330 core

in vec3 vertex_v;
in vec3 normal_v;

out vec4 fragColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;  //nMatrix   = inverse(transpose(mat3(view * TG)));
uniform mat4 viewMatrix;

uniform mat4 modelMatrix;
uniform mat4 viewMatrixInverse;
uniform mat4 modelViewMatrixInverse;

uniform vec4 lightAmbient, lightDiffuse, lightSpecular;
uniform vec4 lightPosition;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;

uniform bool world;
const bool object = false;

vec4 light(vec3 N, vec3 V, vec3 L)
{
	N=normalize(N);
	V=normalize(V);
	L=normalize(L);
	vec3 R = reflect(-L, N);//vec3 R = normalize( 2.0*dot(N,L)*N-L );
	float NdotL = max( 0.0, dot( N,L ) );
	float RdotV = max( 0.0, dot( R,V ) );
	float Idiff = NdotL;
	float Ispec = 0;
	if (NdotL>0) Ispec=pow( RdotV, matShininess );
	return 	matAmbient * lightAmbient +
			matDiffuse * lightDiffuse * Idiff +
			matSpecular * lightSpecular * Ispec;
}

//SCO = Eye Space		-> Vector ja multiplicat per ModelTrans(TG) i ViewTrans(VM)
//SCA = World Space		-> Vector ja multiplicat per ModelTrans(TG)
//SCM = Object Space	-> Vector sense multiplicar
void main(){
	vec3 P;
	vec3 N;
	vec3 V;
	vec3 L;

	if (object){ //SCM (Object Space)
		N = normal_v;
		P = vertex_v;
		V = (modelViewMatrixInverse * vec4(0.0,0.0,0.0,1.0)).xyz - P;
		L = (modelViewMatrixInverse * lightPosition).xyz - P;
	}
	else if (world){ //SCA (WorldSpace)
		mat3 nMatrix = inverse(transpose(mat3(modelMatrix)));
		N = normalize(nMatrix * normal_v);
		P = (modelMatrix * vec4(vertex_v.xyz, 1.0)).xyz;
		V = (viewMatrixInverse * vec4(0.0,0.0,0.0,1.0)).xyz -P;
		L = (viewMatrixInverse * lightPosition).xyz -P;

	}
	else { //SCO (Eye Space)
		P = (modelViewMatrix * vec4(vertex_v.xyz, 1.0)).xyz;
		N = normalMatrix * normal_v;
		V = -P;
		L = (lightPosition.xyz - P);
	}
	fragColor = light(N, V, L);
}
