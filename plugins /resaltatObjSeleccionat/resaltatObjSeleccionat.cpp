#include "resaltatObjSeleccionat.h"

void ResaltatObjSeleccionat::onPluginLoad(){
    glwidget()->makeCurrent();
    // Carrega shader, compila i munta
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("drawBoundingBox.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("drawBoundingBox.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    createBox();
    createVAO();
}

void ResaltatObjSeleccionat::preFrame(){

}

void ResaltatObjSeleccionat::postFrame() {
    glwidget()->makeCurrent();
    GLWidget &g = *glwidget();

    int selectedObj = scene()->selectedObject();
    if (selectedObj != -1){
        Object obj = scene()->objects()[selectedObj];
        computeTranslateScale(&obj);
        program->bind();
        program->setUniformValue("mvp",
                               camera()->projectionMatrix() *
                               camera()->viewMatrix());
        program->setUniformValue("transl", transl);
        program->setUniformValue("scaleVal", scale);
        program->setUniformValue("vrp", bboxUnitCenter);

        // Dibuxa el VAO de la caixa englobat
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        g.glBindVertexArray(VAO);
        g.glDrawElements(GL_TRIANGLES, indices.size(),
                       GL_UNSIGNED_INT, (GLvoid*) 0);
        g.glBindVertexArray(0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void ResaltatObjSeleccionat::onObjectAdd()
{

}

bool ResaltatObjSeleccionat::drawScene()
{
	return false; // return true only if implemented
}

bool ResaltatObjSeleccionat::drawObject(int)
{
	return false; // return true only if implemented
}

bool ResaltatObjSeleccionat::paintGL()
{
	return false; // return true only if implemented
}

void ResaltatObjSeleccionat::keyPressEvent(QKeyEvent *)
{

}

void ResaltatObjSeleccionat::mouseMoveEvent(QMouseEvent *)
{

}

void ResaltatObjSeleccionat::computeTranslateScale(Object* object){
    Box objBbox = object->boundingBox();
    transl = objBbox.center();
    scale = objBbox.max() - objBbox.min();
}

void ResaltatObjSeleccionat::createVAO(){
    glwidget()->makeCurrent();
    GLWidget &g = *glwidget();
    // Crea VAO de la caixa englobant
    g.glGenVertexArrays(1, &VAO);
    g.glBindVertexArray(VAO);

    // Crea VBO de geometria
    GLuint coordBufferID;
    g.glGenBuffers(1, &coordBufferID);
    g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(),
                 &vertices[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);

    // Crea buffer d'IDs
    GLuint indexBufferID;
    g.glGenBuffers(1, &indexBufferID);
    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(),
                 &indices[0], GL_STATIC_DRAW);

    // El VAO ha estat definit
    g.glBindVertexArray(0);
}

void ResaltatObjSeleccionat::createBox(){
    vertices.clear();
    indices.clear();
    float xmin, xmax, ymin, ymax, zmin, zmax;
    xmin = 0.;
    xmax = 1.;
    ymin = 0.;
    ymax = 1.;
    zmin = 0.;
    zmax = 1.;

    bboxUnitCenter.setX((xmin+xmax)/2);
    bboxUnitCenter.setY((ymin+ymax)/2);
    bboxUnitCenter.setZ((zmin+zmax)/2);

    // v1
    vertices.push_back(xmin);
    vertices.push_back(ymin);
    vertices.push_back(zmin);
    // v2
    vertices.push_back(xmax);
    vertices.push_back(ymin);
    vertices.push_back(zmin);
    // v3
    vertices.push_back(xmax);
    vertices.push_back(ymax);
    vertices.push_back(zmin);
    // v4
    vertices.push_back(xmin);
    vertices.push_back(ymax);
    vertices.push_back(zmin);
    // v5
    vertices.push_back(xmin);
    vertices.push_back(ymin);
    vertices.push_back(zmax);
    // v6
    vertices.push_back(xmax);
    vertices.push_back(ymin);
    vertices.push_back(zmax);
    // v7
    vertices.push_back(xmax);
    vertices.push_back(ymax);
    vertices.push_back(zmax);
    // v8
    vertices.push_back(xmin);
    vertices.push_back(ymax);
    vertices.push_back(zmax);

    // t1
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    // t2
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);
    // t3
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(4);
    // t4
    indices.push_back(1);
    indices.push_back(4);
    indices.push_back(5);
    // t5
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(5);
    // t6
    indices.push_back(2);
    indices.push_back(5);
    indices.push_back(6);
    // t7
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(6);
    // t8
    indices.push_back(3);
    indices.push_back(6);
    indices.push_back(7);
    // t9
    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(7);
    // t10
    indices.push_back(0);
    indices.push_back(7);
    indices.push_back(4);
    // t11
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);
    // t12
    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(7);
}
