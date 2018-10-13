#include "mouseObjSelection.h"

void MouseObjSelection::onPluginLoad(){
    glwidget()->makeCurrent();
    // BoundingBox: Carrega shader, compila i munta
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("drawBoundingBox.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("drawBoundingBox.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    // colorShader: Carrega shader, compila i munta
    vsColor = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsColor->compileSourceFile("colorShader.vert");

    fsColor = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsColor->compileSourceFile("colorShader.frag");

    programColor = new QOpenGLShaderProgram(this);
    programColor->addShader(vsColor);
    programColor->addShader(fsColor);
    programColor->link();

    createBox();
    createVAO();
    scene()->setSelectedObject(-1);
}

void MouseObjSelection::preFrame(){

}

void MouseObjSelection::postFrame() {
    glwidget()->makeCurrent();
    GLWidget &g = *glwidget();

    int selectedObj = scene()->selectedObject();
    if (selectedObj != -1){
        Object obj = scene()->objects()[selectedObj];
        computeTranslateScale(&obj);
        program->bind();
        program->setUniformValue("mvp", camera()->projectionMatrix() * camera()->viewMatrix());
        program->setUniformValue("transl", transl);
        program->setUniformValue("scaleVal", scale);
        program->setUniformValue("vrp", bboxUnitCenter);

        // Dibuxa el VAO de la caixa englobat
        //Guardem tipus de poligion inicial (GL_LINE, GL_FILL, GL_POINTS)
        GLint polygonMode;
        g.glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

        // Posem tipus linea per pintar la caixa englobant
        g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        g.glBindVertexArray(VAO);
        g.glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid*) 0);
        g.glBindVertexArray(0);

        //Reestablim poligon mode inicial
        g.glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
        program->release();
    }
}

void MouseObjSelection::onObjectAdd()
{

}

bool MouseObjSelection::drawScene()
{
	return false; // return true only if implemented
}

bool MouseObjSelection::drawObject(int)
{
	return false; // return true only if implemented
}

bool MouseObjSelection::paintGL()
{
	return false; // return true only if implemented
}

void MouseObjSelection::keyPressEvent(QKeyEvent* e){

}

void encodeID(int i, GLubyte* color) {
    color[0] = i;
    color[1] = i;
    color[2] = i;
}

int decodeID(GLubyte *color) {
  if (color[0] == 255) return -1;
  return color[0];
}

void MouseObjSelection::mouseReleaseEvent(QMouseEvent *e){
    glwidget()->makeCurrent();
    GLWidget &g = *glwidget();
    if (!(e->button()&Qt::LeftButton)) return;          // Comprovem Que sigui Left_Buttom
    if (e->modifiers()&(Qt::ShiftModifier) || e->modifiers()&(Qt::AltModifier)) return;     // No altres modificadors pulsats
    if (!(e->modifiers()&Qt::ControlModifier)) return;  // Tecla Control pulsada

    // Clear Window
    g.glClearColor(1, 1, 1, 1);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Draw color scene
    programColor->bind();
    programColor->setUniformValue("mvp", camera()->projectionMatrix() * camera()->viewMatrix());
    for (unsigned int i = 0; i < scene()->objects().size(); i++){
        GLubyte color[4];
        encodeID(i, color);
        programColor->setUniformValue("colorFrag", QVector4D(color[0]/255.0, color[1]/255., color[2]/255., 1.0));
        drawPlugin()->drawObject(i);
    }

    programColor->release();

    // Detect selected color, and set selected object
    int x = e->x();
    int y = glwidget()->height()-e->y();
    GLubyte read[4];
    g.glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);
    int mouseValue = decodeID(&read[0]);
    if (mouseValue != -1 && mouseValue < scene()->objects().size()){
        scene()->setSelectedObject(mouseValue);
    }
    else {
        scene()->setSelectedObject(-1);
    }

    // Paint again original scene
    drawPlugin()->drawScene();
}

void MouseObjSelection::computeTranslateScale(Object* object){
    Box objBbox = object->boundingBox();
    transl = objBbox.center();
    scale = objBbox.max() - objBbox.min();
}

void MouseObjSelection::createVAO(){
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

void MouseObjSelection::createBox(){
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
