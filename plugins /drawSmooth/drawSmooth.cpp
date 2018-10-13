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

#include "drawSmooth.h"

DrawSmooth::~DrawSmooth() {
    cleanUp();
}

void DrawSmooth::onSceneClear()
{
    cleanUp();
}

void DrawSmooth::cleanUp(){
    GLWidget &g = *glwidget();
    g.makeCurrent();
    //Borrem totes les regions de memoria dels VBO i VAO
    //(per cada vector diem que volem borrar n VBO i passem la direccio de memeoria de l'inici del vector)
    g.glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
    g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
    g.glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
    g.glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);
    g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);

    //Netegem les variables on emmagatzemavem aquests valors
    coordBuffers.clear();
    normalBuffers.clear();
    stBuffers.clear();
    colorBuffers.clear();
    VAOs.clear();
    numVertices.clear();
}


bool DrawSmooth::drawObject(int i){
    GLWidget &g = *glwidget();
    g.makeCurrent();
    if (0 <= i && i < VAOs.size()){
        g.glBindVertexArray(VAOs[i]);
        g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[i]);
        g.glDrawElements(GL_TRIANGLES, numVertices[i], GL_UNSIGNED_INT, (GLvoid*) 0);
        g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        g.glBindVertexArray(0);
        return true;
    }
    else {
      return false;
    }
}

bool DrawSmooth::drawScene()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    for(unsigned int i = 0; i < VAOs.size(); i++) // for each buffer (that is, for each object)
    {
        g.glBindVertexArray(VAOs[i]);
        g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[i]);
        g.glDrawElements(GL_TRIANGLES, numVertices[i], GL_UNSIGNED_INT, (GLvoid*) 0);
        g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
    g.glBindVertexArray(0);
    return true;
}

void DrawSmooth::onPluginLoad(){
    cleanUp();
    for(unsigned int i=0; i<scene()->objects().size(); i++)
        addVBO(i);
}

void DrawSmooth::onObjectAdd(){
    addVBO(scene()->objects().size() - 1);
}

void DrawSmooth::addVBO(unsigned int currentObject){
    const Object& obj = scene()->objects()[currentObject];
    unsigned int numvertices = obj.vertices().size(); //En aquest cas V = V' per tant no tripliquem el numero de elements totals
    vector<float> vertices; // (x,y,z)    Final size: 3*number of vertexs
    vector<float> normals;  // (nx,ny,nz) Final size: 3*number of triangles
    vector<float> colors;   // (r, g, b)  Final size: 3*number of triangles
    vector<float> texCoords;// (s, t)     Final size: 3*number of triangles
    vector<int> vertexOrder;

    vector<Vector> vecNormal(numvertices, Vector(0,0,0));
    vector<int> vecAppearCount(numvertices, 0);
    vector<Face> faces = obj.faces();

    for (int i = 0; i < faces.size(); i++){
        //faces[i].computeNormal();
        Vector N = faces[i].normal();
        for (int j = 0; j < faces[i].numVertices(); j++){
            int vertIndex = faces[i].vertexIndex(j);
            vecNormal[vertIndex] += N;
            vecAppearCount[vertIndex]++;
        }
    }

    vector<Vertex> vertexs = obj.vertices();
    vector<std::pair<float, float> > coordST = obj.vertTexCoords();
    for (int i = 0; i < vertexs.size(); i++){
        Point P = vertexs[i].coord();
        vertices.push_back(P.x());
        vertices.push_back(P.y());
        vertices.push_back(P.z());

        Vector N = vecNormal[i] / vecAppearCount[i];
        normals.push_back(N.x());
        normals.push_back(N.y());
        normals.push_back(N.z());

        colors.push_back(fabs(N.x()));
        colors.push_back(fabs(N.y()));
        colors.push_back(fabs(N.z()));

        texCoords.push_back(coordST[i].first);
        texCoords.push_back(coordST[i].second);
    }

    for (int i = 0; i < faces.size(); i++) {
      Face face = faces[i];
      for (int j = 0; j < face.numVertices(); j++)
        vertexOrder.push_back(face.vertexIndex(j));
    }

    // Step 2: Create VAO and empty buffers (coords, normals, ...)
    GLWidget& g = *glwidget();

    //Generem el VAO de l'objecte
    GLuint VAO;
    g.glGenVertexArrays(1, &VAO);
    //Guardem la direccio de memoria del VAO per a l'objecte
    VAOs.push_back(VAO);

    // Activem el VAO
    g.glBindVertexArray(VAO);
    // Generem els diversos VBO per a aquell objecte i emmagatzemem la seva direccio de memoria tmb

    // VBO Vertexs
    GLuint coordBufferID;
    g.glGenBuffers(1, &coordBufferID);
    coordBuffers.push_back(coordBufferID);

    // VBO Normals
    GLuint normalBufferID;
    g.glGenBuffers(1, &normalBufferID);
    normalBuffers.push_back(normalBufferID);

    // VBO Coordenades textura ST
    GLuint stBufferID;
    g.glGenBuffers(1, &stBufferID);
    stBuffers.push_back(stBufferID);

    // VBO Colors
    GLuint colorBufferID;
    g.glGenBuffers(1, &colorBufferID);
    colorBuffers.push_back(colorBufferID);

    // VBO Indexos
    GLuint indexBufferID;
    g.glGenBuffers(1, &indexBufferID);
    indexBuffers.push_back(indexBufferID);

    //Guardem tambe el numero de vertexs (es a dri el numero de elements que shan de pintar)
    numVertices.push_back(3 * obj.faces().size());



    // Step 3: Define VBO data (coords, normals, colors, textureST, )
    g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW); //Passem el nombre d'elements i la direccio de inici
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Els posem com a layout per al VS i FS: layout (location = 0) in vec3 vertex;
    g.glEnableVertexAttribArray(0); //Els activem!

    g.glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(1);

    g.glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(2);

    g.glBindBuffer(GL_ARRAY_BUFFER, stBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(3);

    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[currentObject]);
    g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*vertexOrder.size(), &vertexOrder[0], GL_STATIC_DRAW);

    //Descativem VBO i VAO
    g.glBindBuffer(GL_ARRAY_BUFFER,0);
    g.glBindVertexArray(0);
}
