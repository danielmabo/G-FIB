#version 330 core

in vec2 vtexCoord;
in vec4 vertexEye;
out vec4 fragColor;

uniform sampler2D sampler;

void main(){
    //Calculem vector direccio X (x2 - x1)
    //on x2 x1 son les posicions del vertex en Eye space d'aquest fragment i el seguent (o anterior)
    vec3 dvx = dFdx(vertexEye.xyz);
    //Calculem vector direccio Y (y2 - y1)
    vec3 dvy = dFdy(vertexEye.xyz);
    //Apliquem producte vectorial per treure vector perpendicular al pla(dvx, dvy) -> Tenim la Normal
    vec3 normalCalc = cross(dvx, dvy);
    vec3 N = normalize(normalCalc);
    fragColor = texture(sampler, vec2(N.x, N.y)) * N.z;
}
