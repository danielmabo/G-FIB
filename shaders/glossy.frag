#version 330 core

in vec3 N;
in vec3 P;
out vec4 fragColor;


uniform sampler2D glossy;
uniform int r = 0;

vec4 sampleTexture(sampler2D sampler, vec2 st, int r)
{
	float width = 512.;
	float height = 512.;
	vec4 loopRes = vec4(0.,0.,0.,0.);
	for (int i = -r; i <= r; i++){
		for (int j = -r; j <= r; j++){
			vec2 texCoordI = vec2(st.s + i/width, st.t + j/height);
			loopRes += texture(sampler, texCoordI);
		}
	}

	vec4 colorRes = (1. / pow((2*r + 1), 2)) * loopRes;
	return colorRes;
}

vec4 sampleSphereMap(sampler2D sampler, vec3 R)
{
	float z = sqrt((R.z+1.0)/2.0);
	vec2 st = vec2((R.x/(2.0*z)+1.0)/2.0, (R.y/(2.0*z)+1.0)/2.0);
    st.y = -st.y;
	return sampleTexture(sampler, st, r);
}

void main()
{
	vec3 obs = vec3(0.0);
	vec3 I = normalize(P-obs);
	vec3 R = reflect(I, N);

	fragColor = sampleSphereMap(glossy, R);
}
