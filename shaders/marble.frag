#version 330 core

in vec2 vtexCoord;
in vec4 vertexObj;
in vec3 normalObj;
out vec4 fragColor;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform sampler2D noise;

vec4 shading(vec3 N, vec3 Pos, vec4 diffuse) {
    vec3 lightPos = vec3(0.0,0.0,2.0);
    vec3 L = normalize( lightPos - Pos );
    vec3 V = normalize( -Pos);
    vec3 R = reflect(-L,N);
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Ispec = pow( RdotV, 20.0 );
    return diffuse * NdotL + Ispec;
}

void main(){
    vec4 colorWhite = vec4(1., 1., 1., 1.);
    vec4 colorRedish = vec4(0.5, 0.2, 0.2, 1.);
    vec4 plaS = 0.3 * vec4(0., 1., -1., 0.);
    vec4 plaT = 0.3 * vec4(-2., -1., 1., 0.);
    float coordS = dot(plaS, vertexObj);
    float coordT = dot(plaT, vertexObj);
    float v = texture(noise, vec2(coordS, coordT)).x;
    float threshold = 0.5;

    //Calc color difus: v=0 doni white, v=0.5 doni redish, i v=1.0 doni un altre cop white.
    vec4 colorDifus = colorWhite;
    if (v < threshold)
        colorDifus = mix(colorWhite, colorRedish, fract(v / threshold));
    else
        colorDifus = mix(colorRedish, colorWhite, fract(v / threshold));

    vec3 vertexEye = (modelViewMatrix * vertexObj).xyz;
    vec3 normalEye = normalize(normalMatrix * normalObj);

    fragColor = shading(normalEye, vertexEye, colorDifus);
}
