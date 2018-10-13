#version 330 core

in vec3 vertexWorld;
out vec4 fragColor;

uniform vec3 origin = vec3(0., 0., 0.);
uniform vec3 axis = vec3(0., 0., 1.);
uniform float slice = 0.05;

void main(){
    vec4 colorBlue = vec4(0., 0., 1., 1.);
    vec4 colorCian = vec4(0., 1., 1., 1.);

    //Idea: El vertex en worldSpace pot ser un vector de l'origen al punt
    //Per tant podem calcular la projeccio del punt en la recta (axis)
    //Tenint en compte que el porducte escalar (dot) entre 2 vectors dona el
    //cosinus de l'angle i un vector pel cosinus es projecta en la recta del pla (trigonometria).
    //A la vegada aquest no deixara de ser un punt i podem calcular la distancia
    //entre aquest punt i el vertexWorld.
    //Sempre s'ha de normalitzar el eix (vertex)
    vec3 axisN = normalize(axis);
    vec3 linePoint = origin + axisN * dot(vertexWorld, axis);
    float d = distance(vertexWorld, linePoint);

    if (mod(d, 2 * slice) < slice){
        fragColor = colorCian;
    }
    else
        fragColor = colorBlue;
}
