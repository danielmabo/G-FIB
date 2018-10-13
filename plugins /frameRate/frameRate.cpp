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

#include "frameRate.h"
#include "glwidget.h"



void FrameRate::onPluginLoad()
{
  glwidget()->makeCurrent();
    // Carregar shader, compile & link
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("show.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("show.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getFrameRate()));
    timer->start(1000);

    //timer.start();
}

void FrameRate::drawRect()
{
    glwidget()->makeCurrent();
    GLWidget &g = *glwidget();
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        float z = -0.99999;
        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, z,
                            1, -1, z,
                           -1,  1, z,
                            1,  1, z};
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

void FrameRate::getFrameRate(){
    //frameRate = 1000./ timer.restart();
    frameRate = float(nframes); 
    nframes = 0;
}

void FrameRate::preFrame(){

}

void FrameRate::postFrame()
{
    glwidget()->makeCurrent();
    GLWidget &g = *glwidget();
    nframes++;
    const int SIZE = 1024;
    // 1. Create image with text
    QImage image(SIZE,SIZE,QImage::Format_RGB32);
    image.fill(Qt::white);
    QPainter painter;
    painter.begin(&image);
    QFont font;
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen(QColor(50,50,50));
    int x = 15;
    int y = 50;
    string s1;
    s1 = "FPS: " + to_string(frameRate);
    painter.drawText(x, y, QString::fromStdString(s1));
    painter.end();

    // 2. Create texture
    const int textureUnit = 5;
    g.glActiveTexture(GL_TEXTURE0+textureUnit);
    QImage im0 = image.mirrored(false, true).convertToFormat(QImage::Format_RGBA8888, Qt::ColorOnly);
    //PRINT IMAGE
    /*if (!created){
        im0.save( QString::fromStdString("/Users/danielmartinezbordes/imatge.png"), 0, -1 );
        created = true;
    }*/
	g.glGenTextures( 1, &textureID);
	g.glBindTexture(GL_TEXTURE_2D, textureID);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glGenerateMipmap(GL_TEXTURE_2D);
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );


    // Pass 2. Draw quad using texture
    program->bind();
    program->setUniformValue("colorMap", textureUnit);
    program->setUniformValue("WIDTH", float(glwidget()->width()));
    program->setUniformValue("HEIGHT", float(glwidget()->height()));

    // quad covering viewport
    drawRect();
    program->release();
    g.glBindTexture(GL_TEXTURE_2D, 0);

    g.glDeleteTextures(1, &textureID);
}
