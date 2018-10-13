#version 330 core

in vec4 frontColor;
out vec4 fragColor;

void main()
{
    //En aquest cas el FS nomes assigna el color
    fragColor = frontColor;
}
