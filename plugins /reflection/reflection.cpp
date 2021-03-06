#include "reflection.h"
#include <QCoreApplication>

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Reflection::onPluginLoad(){
    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link
    vsRefl = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsRefl->compileSourceFile(QCoreApplication::applicationDirPath() + "/../../plugins/reflection/reflectionScene.vert");

    fsRefl = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsRefl->compileSourceFile(QCoreApplication::applicationDirPath() + "/../../plugins/reflection/reflectionScene.frag");

    programRefl = new QOpenGLShaderProgram(this);
    programRefl->addShader(vs);
    programRefl->addShader(fs);
    programRefl->link();

    vsMirror = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsMirror->compileSourceFile(QCoreApplication::applicationDirPath() + "/../../plugins/reflection/mirrorFloor.vert");

    fsMirror = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsMirror->compileSourceFile(QCoreApplication::applicationDirPath() + "/../../plugins/reflection/mirrorFloor.frag");

    programMirror = new QOpenGLShaderProgram(this);
    programMirror->addShader(vs);
    programMirror->addShader(fs);
    programMirror->link();

    // Setup texture
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures( 1, &textureId);
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		      GL_LINEAR_MIPMAP_LINEAR );
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT,
		   0, GL_RGB, GL_FLOAT, NULL);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    // Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
}

void drawRect(GLWidget &g){
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;


        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, 0,
                            1, -1, 0,
                           -1,  1, 0,
                            1,  1, 0};

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}

void Reflection::paintReflection(){
    GLWidget & g = *glwidget();
    g.makeCurrent();
    g.glClearColor(1,1,1,1);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    programRefl->bind();
    programRefl->setUniformValue("modelViewMatrix", );
    programRefl->setUniformValue("modelViewMatrix", );
    programRefl->setUniformValue("modelViewMatrix", );
    programRefl->setUniformValue("modelViewMatrix", );
    uniform vec4 planeVec1;
    uniform vec4 planeVec2;
    uniform vec4 planePoint;
    uniform mat4 modelViewMatrix;
    uniform mat4 projectionMatrix;
    if (drawPlugin()) drawPlugin()->drawScene();
    programRefl->release();
}

void Reflection::paintScene(){
    GLWidget & g = *glwidget();
    g.makeCurrent();
    g.glClearColor(1,1,1,1);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    g.defaultProgram()->bind();
    if (drawPlugin()) drawPlugin()->drawScene();
    g.defaultProgram()->release();
}

void Reflection::copyWindowToTexture(){
    GLWidget & g = *glwidget();
    g.makeCurrent();
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,IMAGE_WIDTH, IMAGE_HEIGHT);
    g.glGenerateMipmap(GL_TEXTURE_2D);
}




bool Reflection::paintGL()
{
    GLWidget & g = *glwidget();

    // Pas 1: Dibuixar escena reflectida (al terra)
    paintReflection();


    // Pas 2: Guardar resultat en una textura

    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,IMAGE_WIDTH, IMAGE_HEIGHT);
    g.glGenerateMipmap(GL_TEXTURE_2D);


    // Pas 3: Dibuixar escena real
    paintScene();

    // Pas 4: Dibuixar mirall (el mirall sera el pla inferior de la capsa contenidora)

    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    program->bind();
    program->setUniformValue("colorMap", 0);
    program->setUniformValue("SIZE", float(IMAGE_WIDTH));
    program->setUniformValue("modelViewProjectionMatrix", QMatrix4x4() );
    drawRect(g);
    g.glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}
