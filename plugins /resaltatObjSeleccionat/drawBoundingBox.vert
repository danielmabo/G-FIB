#version 330 core

in vec3 vertex;

uniform mat4 mvp;
uniform vec3 transl;
uniform vec3 scaleVal;
uniform vec3 vrp;

mat4 translate(vec3 t){
    return mat4 (vec4(1.,0.,0.,0.),
                 vec4(0.,1.,0.,0.),
                 vec4(0.,0.,1.,0.),
                 vec4(t, 1.));
}

mat4 scale(vec3 s){
    return mat4 (vec4(s.x,0.,0.,0.),
                 vec4(0.,s.y,0.,0.),
                 vec4(0.,0.,s.z,0.),
                 vec4(0.,0.,0.,1.));
}

void main(){
  gl_Position = mvp * translate(transl) * scale(scaleVal) * translate(-vrp) * vec4(vertex, 1.0);
}
