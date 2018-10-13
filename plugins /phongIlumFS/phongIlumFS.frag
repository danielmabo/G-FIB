#version 330 core

in vec3 vertex_v;
in vec3 normal_v;

out vec4 fragColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;

vec4 light(vec3 N, vec3 V, vec3 L)
{
	N=normalize(N);
	V=normalize(V);
	L=normalize(L);
	vec3 R = normalize( 2.0*dot(N,L)*N-L );
	float NdotL = max( 0.0, dot( N,L ) );
	float RdotV = max( 0.0, dot( R,V ) );
	float Idiff = NdotL;
	float Ispec = 0;
	if (NdotL>0) Ispec=pow( RdotV, matShininess );
	return 	matAmbient * lightAmbient +
		matDiffuse * lightDiffuse * Idiff +
		matSpecular * lightSpecular * Ispec;
}


void main()
{
	vec3 P = (modelViewMatrix * vec4(vertex_v.xyz, 1.0)).xyz;
	vec3 N = normalize(normalMatrix * normal_v);
	vec3 V = -P;
	vec3 L = (lightPosition.xyz - P);
	fragColor = light(N, V, L);
}
