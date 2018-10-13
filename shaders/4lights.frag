#version 330 core

in vec3 vertex_v;
in vec3 normal_v;

out vec4 fragColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform mat4 modelViewMatrixInverse;

uniform float time;
uniform bool rotate = true;

vec4 light(vec3 N, vec3 V, vec3 P, vec3 L, vec3 C){
	const float shininess = 100.0;
	const float Kd = 0.5;
	V = normalize(V);
	N = normalize(N);
	L = normalize(L - P);
	vec3 R = reflect(-L, N);
	float NdotL = max(0.0, dot(N,L));
	float RdotV = max(0.0, dot(R,V));
	float Ispec = 0;
	if (NdotL > 0)
		Ispec = pow(RdotV, shininess);
	return vec4(Kd * C * NdotL + vec3(Ispec), 0);
}

void main()
{
	vec3 L1 = vec3(0, 10, 0);	//SCO
	vec3 L2 = vec3(0, -10, 0);	//SCO
	vec3 L3 = vec3(10, 0, 0);	//SCO
	vec3 L4 = vec3(-10, 0, 0); 	//SCO
	vec3 C1 = vec3(0, 1, 0); 	//Color Verd
    vec3 C2 = vec3(1, 1, 0); 	//Color Groc
    vec3 C3 = vec3(0, 0, 1); 	//Color Blau
    vec3 C4 = vec3(1, 0, 0); 	//Color Vermell

	//S'ha de rotar respecte l'eixZ 'time' cops.
	if (rotate){
  		mat3 Rot = mat3(vec3(  cos(time), 	sin(time),	0),
						vec3(- sin(time), 	cos(time),	0),
						vec3(		   0,			0,	1));
  		L1 = Rot * L1;
  		L2 = Rot * L2;
  		L3 = Rot * L3;
  		L4 = Rot * L4;
	}

	//Els calculs s'han de fer en coordenades de SCM (Object Space)
	//SCO = Eye Space		-> Vector ja multiplicat per ModelTrans(TG) i ViewTrans(VM)
	//SCA = World Space		-> Vector ja multiplicat per ModelTrans(TG)
	//SCM = Object Space	-> Vector sense multiplicar
	//Els vectors de llum (lightPos) s'han donat en coordenades de SCO (Eye space) per tant hem de desfer el canvi.

	L1 = (modelViewMatrixInverse*vec4(L1, 1)).xyz; //SCM
	L2 = (modelViewMatrixInverse*vec4(L2, 1)).xyz; //SCM
	L3 = (modelViewMatrixInverse*vec4(L3, 1)).xyz; //SCM
	L4 = (modelViewMatrixInverse*vec4(L4, 1)).xyz; //SCM

	vec3 P = vertex_v; //SCM
	vec3 N = normal_v; //SCM
	vec3 V = (modelViewMatrixInverse * vec4(0.0,0.0,0.0,1.0)).xyz - P; //SCM (Pq passa el (0,0,0) en SCO a SCM)

	fragColor = light(N, V, P, L1, C1) + light(N, V, P, L2, C2) +
				light(N, V, P, L3, C3) + light(N, V, P, L4, C4);
}
