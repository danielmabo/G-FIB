// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
//
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "base.h"



float Base::crossModul(Vector v1, Vector v2){
    float vx =  v1.y() * v2.z() - v1.z() * v2.y();
    float vy =  v1.z() * v2.x() - v1.x() * v2.z();
    float vz =  v1.x() * v2.y() - v1.y() * v2.x();
    return sqrt(pow(vx,2) + pow(vy,2) + pow(vz,2));
}


float Base::getMinY(Face f){
    float minY = scene()->objects()[0].vertices()[f.vertexIndex(0)].coord().y();
    for (int i = 1; i < f.numVertices(); i++){
        float actY = scene()->objects()[0].vertices()[f.vertexIndex(i)].coord().y();
        if (actY < minY)
            minY = actY;
    }
    return minY;
}

float Base::getFaceArea(Face f){
    Point p1 = scene()->objects()[0].vertices()[f.vertexIndex(0)].coord();
    Point p2 = scene()->objects()[0].vertices()[f.vertexIndex(1)].coord();
    Point p3 = scene()->objects()[0].vertices()[f.vertexIndex(2)].coord();
    Vector v1 = p2-p1;
    Vector v2 = p3-p1;
    float area = crossModul(v1, v2)/2.;
    return area;
}

void Base::onPluginLoad(){
    Object obj = scene()->objects()[0];
    float thresholdY = obj.boundingBox().center().y();
    vector<Face> faces = obj.faces();
    float area = 0;
    for (int i = 0; i < faces.size(); i++){
        float minY = getMinY(faces[i]);
        if (minY < thresholdY)
            area += getFaceArea(faces[i]);
    }
    cout << "Area: " << area << endl;
}


