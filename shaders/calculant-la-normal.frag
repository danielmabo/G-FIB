#version 330 core

in vec3 vEye;
in vec4 frontColor;
out vec4 fragColor;

void main(){
    //Calculem vector direccio X (x2 - x1)
    //on x2 x1 son les posicions del vertex en Eye space d'aquest fragment i el seguent (o anterior)
    vec3 dvx = dFdx(vEye);
    //Calculem vector direccio Y (y2 - y1)
    vec3 dvy = dFdy(vEye);
    //Apliquem producte vectorial per treure vector perpendicular al pla(dvx, dvy) -> Tenim la Normal
    vec3 normalCalc = cross(dvx,dvy);
	vec3 N = normalize(normalCalc);
    fragColor = frontColor * N.z;
}
