#version 330 core

in vec4 frontColor;
out vec4 fragColor;

void main()
{
    fragColor = frontColor;
    //Per defecte el fragDepth el tracta el z-buffer pero podem forçar que prengui
    //un altre valor en el FragmentShader
    gl_FragDepth = 1. - gl_FragCoord.z;
}
