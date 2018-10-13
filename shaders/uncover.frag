#version 330 core

in vec3 vertexNorm;
out vec4 fragColor;
uniform float time;

void main()
{
    vec4 colorBlue = vec4(0., 0., 1., 1.);
    float timeMax = 2.;

    //Canviem de coordenades nomralitzades [-1..1] -> [0..1]
    float coordVal = (vertexNorm.x + 1)/2;

    if (coordVal > time/timeMax)
        discard;
    else
        fragColor = colorBlue;
}
