#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 normalObj[];
out vec3 gNormal;

uniform mat4 modelViewProjectionMatrix;
uniform float d = 2;

void main( void ){
    vec3 meanNorm = normalize((normalObj[0] + normalObj[1] + normalObj[2])/3.);
    vec4 v1 = gl_in[0].gl_Position;
    vec4 v2 = gl_in[1].gl_Position;
    vec4 v3 = gl_in[2].gl_Position;
    vec4 v4 = v1 + vec4(meanNorm * d, 0.);
    vec4 v5 = v2 + vec4(meanNorm * d, 0.);
    vec4 v6 = v3 + vec4(meanNorm * d, 0.);
    //Pintem cares prisma
    //TOP
    gNormal = meanNorm;
    gl_Position = modelViewProjectionMatrix * v4;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v5;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v6;
    EmitVertex();
    EndPrimitive();

    //BOTTOM
    gNormal = - meanNorm;
    gl_Position = modelViewProjectionMatrix * v1;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v2;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v3;
    EmitVertex();
    EndPrimitive();

    //BACK
    gNormal = cross((v3-v2).xyz, meanNorm);
    gl_Position = modelViewProjectionMatrix * v2;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v3;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v5;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v6;
    EmitVertex();
    EndPrimitive();

    //LEFT
    gNormal = cross((v1-v3).xyz, meanNorm);
    gl_Position = modelViewProjectionMatrix * v1;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v3;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v4;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v6;
    EmitVertex();
    EndPrimitive();

    //RIGHT
    gNormal = cross((v2-v1).xyz, meanNorm);
    gl_Position = modelViewProjectionMatrix * v1;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v2;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v4;
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * v5;
    EmitVertex();
    EndPrimitive();


}
