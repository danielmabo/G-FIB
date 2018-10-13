#version 330 core

in vec4 frontColor;
out vec4 fragColor;

float computeLambda(){
    const float SIZE = 512.0; //Texturas 512x512
    vec2 uv = SIZE * gl_TexCoord[0].st;
    float rho = max(length(dFdx(uv)), length(dFdy(uv)));
    return log(rho) / log(2.0);
}

void main()
{
    float lambda = clamp(computeLambda(), 0, 8);
    int r = int(mod(lambda, 5.0));
    vec3 col;
    if (r == 0)     col = vec3(1., 0., 0.);
    else if(r == 1) col = vec3(1., 1., 0.);
    else if(r == 2) col = vec3(0., 1., 0.);
    else if(r == 3) col = vec3(0., 1., 1.);
    else if(r == 4) col = vec3(0., 0., 1.);
    fragColor = mix(vec4(col, 1.), texture2D(s, gl_TexCoord[0].st), 0.5);
}
