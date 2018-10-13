#version 330 core

in vec3 gNormal;
in vec4 gPos;
out vec4 fragColor;

uniform mat3 normalMatrix;

uniform sampler2D grass_top0, grass_side1;
uniform float d = 0.1;
void main()
{
    //VERTICAL
    if (gNormal.z == 0){
        vec2 texCoord = vec2(4 * (gPos.x - gPos.y), 1.0 - gPos.z/d);
        vec4 texColor = texture(grass_top0, texCoord);
        if (texColor.a < 0.1){
            discard;
        }
        else {
            fragColor = texColor;
        }
    }
    else {
        vec2 texCoord = vec2(4 * gPos.xy);
        fragColor = texture(grass_side1, texCoord);
    }


}
