#version 330 core

in vec4 gfrontColor;
in float topFace;
in vec3 gNormal;
in vec2 gtexCoord;
out vec4 fragColor;

uniform sampler2D sampler0;

const vec4 colorR = vec4(1.,0.,0.,1.);
const vec4 colorG = vec4(0.,1.,0.,1.);
const vec4 colorB = vec4(0.,0.,1.,1.);
const vec4 colorC = vec4(0.,1.,1.,1.);
const vec4 colorY = vec4(1.,1.,0.,1.);

vec4 colorDistEucl() {
    float distR = distance(gfrontColor, colorR);
    float distG = distance(gfrontColor, colorG);
    float distB = distance(gfrontColor, colorB);
    float distC = distance(gfrontColor, colorC);
    float distY = distance(gfrontColor, colorY);
    float distMin = min(distR, min(distG, min(distB, min(distC, distY))));
    if (distMin == distR)
        return colorR;
    else if (distMin == distG)
        return colorG;
    else if (distMin == distB)
        return colorB;
    else if (distMin == distC)
        return colorC;
    return colorY;
}

void main() {
  fragColor = colorDistEucl() ;//* normalize(gNormal).z;
  if (topFace == 1.)
    fragColor = fragColor * texture(sampler0, gtexCoord);

}
