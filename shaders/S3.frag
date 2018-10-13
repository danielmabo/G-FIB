#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;

out vec4 fragColor;

uniform sampler2D MyTexture;

void main()
{
  fragColor = frontColor * texture(MyTexture, vtexCoord); //Acceder a componentes textura (vtexCoord.s,vtexCoord.t)
}
