#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D MyTexture;
uniform float time;
uniform float speed = 0.1;

void main()
{
    //Afegim a les coordenades de la textura per a aquell pixel un increment
    //constant en eltemps en els 2 eixos de manera que sembla que "roti" es podria
    //afegir a una sola component o fer-ho sinusoidal
    //fragColor = frontColor * texture (MyTexture, vec2(speed * time + vtexCoord.s, speed * time + vtexCoord.t));
    fragColor = frontColor * texture (MyTexture, speed * time + vtexCoord);
}
