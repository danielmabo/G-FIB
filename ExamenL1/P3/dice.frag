#version 330 core

in vec4 frontColor;
in vec3 N;
in vec4 vertexObj;
out vec4 fragColor;

int calcEix(vec3 N){
    //Per a calcular la distancia a un eix 
    vec3 eixX = vec3(1.,0.,0.);
    vec3 eixY = vec3(0.,1.,0.);
    vec3 eixZ = vec3(0.,0.,1.);
    //Fem el valabs de la normal per tenir en compte el cas negatiu
    N = abs(normalize(N));
    //Aproximem considerant que si el dot product es menor a 0.1 sera paralela la normal al eix (realment seria 0 exacte pero hem d'evitar errors d'aprox)
    if (distance (N, eixX) < 0.1)
        return 1;
    else if (distance (N, eixY) < 0.1)
        return 2;
    return 3;
}

void main()
{
    //Definim un vector Q que segons els eixos sera el valor en aquell pla
    vec2 Q;
    //Definim el radi limit
    float r = 0.2;
    //el color dels punts del dau
    vec4 colorBlack = vec4(0.,0.,0.,1.);
    
    //Calculem quin dels 3 eixos es X -> 1, Y -> 2 , Z -> 3
    int indicadorEix = calcEix(N);
    
    //Segons el eix assignem color negre (generem un punt si es compleix la distancia a 1, 2 o 3 punts fixats del pla)
    if (indicadorEix == 1){
        Q = vec2(vertexObj.yz);
        if (distance(Q, vec2(0.,0.)) < 0.2)
            fragColor = colorBlack;
        else
            fragColor = frontColor;
    }
    else if (indicadorEix == 2){
        Q = vec2(vertexObj.xz);
        if (distance(Q, vec2(-0.5,-0.5)) < 0.2 || distance(Q, vec2(0.5,0.5)) < 0.2)
            fragColor = colorBlack;
        else
            fragColor = frontColor;
    }
    else if (indicadorEix == 3){
        Q = vec2(vertexObj.xy);
        if (distance(Q, vec2(-0.5,-0.5)) < 0.2 || distance(Q, vec2(0.5,0.5)) < 0.2 || distance(Q, vec2(0.,0.)) < 0.2)
            fragColor = colorBlack;
        else
            fragColor = frontColor;
    }
}
