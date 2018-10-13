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

#include "glwidget.h"
#include "phongIlumFS.h"

void PhongIlumFS::onPluginLoad()
{
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("phongIlumFS.vert");
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("phongIlumFS.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

void PhongIlumFS::preFrame(){
    // bind shader and define uniforms
    program->bind();
    QMatrix4x4 MVP =  camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

    QMatrix3x3 normalMatrix =  camera()->viewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", normalMatrix);
    QMatrix4x4 MV = camera()->viewMatrix();
    program->setUniformValue("modelViewMatrix", MV);

    QVector4D lightAmbient = QVector4D(0.1, 0.1, 0.1, 1.0);
    QVector4D lightDiffuse = QVector4D(1.0 ,1.0 ,1.0, 1.0);
    QVector4D lightSpecular = QVector4D(1.0 ,1.0 ,1.0, 1.0);
    QVector4D lightPosition = QVector4D(0.0, 0.0, 0.0, 1.0);
    program->setUniformValue("lightAmbient", lightAmbient);
    program->setUniformValue("lightDiffuse", lightDiffuse);
    program->setUniformValue("lightSpecular", lightSpecular);
    program->setUniformValue("lightPosition", lightPosition);
    QVector4D matAmbient = QVector4D(1.0, 0.5, 0.3, 1.0);
    QVector4D matDiffuse = QVector4D(1.0, 0.5, 0.3, 1.0);
    QVector4D matSpecular = QVector4D(1.0, 1.0, 1.0, 1.0);
    float matShininess = 64.0f;
    program->setUniformValue("matAmbient", matAmbient);
    program->setUniformValue("matDiffuse", matDiffuse);
    program->setUniformValue("matSpecular", matSpecular);
    program->setUniformValue("matShininess", matShininess);
}

void PhongIlumFS::postFrame(){
    program->release();
}
