#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 projectionMatrix;
uniform float disp = 0.05;

void main( void ){
    vec4 colorWhite = vec4(1.,1.,1.,1.);

    vec4 v1 =  gl_in[0].gl_Position;
    vec4 v2 =  gl_in[1].gl_Position;
    vec4 v3 =  gl_in[2].gl_Position;
    vec4 c1 = vfrontColor[0];
    vec4 c2 = vfrontColor[1];
    vec4 c3 = vfrontColor[2];
    vec4 c4 = colorWhite;

    vec4 bariCentTriang = (v1 + v2 + v3)/3.;
    vec4 normEye = vec4(normalize(cross((v2 - v1).xyz, (v3 - v1).xyz)), 0.);
    vec4 v4 = bariCentTriang + disp * normEye;


    vec3 normalEye;

    normalEye = normalize(cross((v2-v1).xyz, (v4-v1).xyz));
	gfrontColor = c1 * normalEye.z;
	gl_Position = projectionMatrix * v1;
	EmitVertex();
    gfrontColor = c2 * normalEye.z;
    gl_Position = projectionMatrix * v2;
    EmitVertex();
    gfrontColor = c4 * normalEye.z;
    gl_Position = projectionMatrix * v4;
    EmitVertex();
    EndPrimitive();

    normalEye = normalize(cross((v1-v3).xyz, (v4-v3).xyz));
    gfrontColor = c1 * normalEye.z;
    gl_Position = projectionMatrix * v1;
    EmitVertex();
    gfrontColor = c3 * normalEye.z;
    gl_Position = projectionMatrix * v3;
    EmitVertex();
    gfrontColor = c4 * normalEye.z;
    gl_Position = projectionMatrix * v4;
    EmitVertex();
    EndPrimitive();

    normalEye = normalize(cross((v3-v2).xyz, (v4-v2).xyz));
    gfrontColor = c2 * normalEye.z;
    gl_Position = projectionMatrix * v2;
    EmitVertex();
    gfrontColor = c3 * normalEye.z;
    gl_Position = projectionMatrix * v3;
    EmitVertex();
    gfrontColor = c4 * normalEye.z;
    gl_Position = projectionMatrix * v4;
    EmitVertex();
    EndPrimitive();

}
