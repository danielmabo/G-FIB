#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int n;

void main()
{

    fragColor = frontColor;
    //La funcio mod es continua amb periode n (es a dir pex mod(1.5, 3) = 1.5 )
    //per tant que fos == 0 era imposible pq ens torna el centre del fragment 0.5 , 1.5 ...
    //if (mod(gl_FragCoord.y, n) >= 1)
    if (mod(gl_FragCoord.y, n) != 0.5)
        discard;
}
