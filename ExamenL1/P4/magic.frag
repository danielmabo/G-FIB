#version 330 core

in vec3 N;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D window; 
uniform sampler2D interior1; // observeu el digit 1 al final
uniform sampler2D exterior2; // observeu el digit 2 al final 
 


void main()
{
    //Apliquem raonament exercici amb el component alfa i accedint a cada textura en les coordenades indicades
    vec4 C = texture(window, vtexCoord);
    vec4 D;
    if (C.w == 1.){
        fragColor = C;
    }
    else{
        D = texture(interior1, vtexCoord + 0.5 * N.xy);
        if (D.w == 1.)
            fragColor = D;
        else
            fragColor = texture(exterior2, vtexCoord + 0.7 * N.xy); 
    }
        
}
