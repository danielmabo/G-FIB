#version 330 core

in vec3 vertex_v;
in vec3 normal_v;

out vec4 fragColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform mat4 modelViewMatrixInverse;

uniform vec4 matAmbient, matDiffuse, matSpecular, lightSpecular;
uniform float matShininess;

vec4 light(vec3 N, vec3 V, vec3 P, vec3 L, vec3 C){
	float shininess = matShininess;
	V = normalize(V);
	N = normalize(N);
	L = normalize(L - P);
	vec3 R = reflect(-L, N);
	float NdotL = max(0.0, dot(N,L));
	float RdotV = max(0.0, dot(R,V));
	float Ispec = 0;
	if (NdotL > 0)
		Ispec = pow(RdotV, shininess);
    //Mantenim els calculs de les components, sense tenir en compte la ocmponent ambient, i posant per color difus el color del focus!
	return matDiffuse * vec4(C,1.) * NdotL +
			matSpecular * lightSpecular * Ispec;
}

void main()
{
    //Considerem posicions infinitament allunyades en model space com a 1 milio de unitats! En cadascun dels 3 eixos
	vec3 L1 = vec3(0, 1000000, 0);	//SCM
	vec3 L2 = vec3(0, 0, 1000000);	//SCM
	vec3 L3 = vec3(1000000, 0, 0);	//SCM
	//Declarem els colors de cada focus de llum
	vec3 C1 = vec3(0, 1, 0); 	//Color Verd
    vec3 C2 = vec3(0, 0, 1); 	//Color Blau
    vec3 C3 = vec3(1, 0, 0); 	//Color Vermell

    //Calculem els components en SCM==object space (en aquest cas vertex i normal ja venen donades en SCM)
	vec3 P = vertex_v; //SCM
	vec3 N = normal_v; //SCM
	//Transformem elvector que va desde el origen de SCO a SCM
	vec3 V = (modelViewMatrixInverse * vec4(0.0,0.0,0.0,1.0)).xyz - P; //SCM (Pq passa el (0,0,0) en SCO a SCM)
    //Apliquem el calcul de llum per a cada focus
	fragColor = light(N, V, P, L1, C1) + light(N, V, P, L2, C2) +
				light(N, V, P, L3, C3);
}
