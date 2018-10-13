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

#include "animateVerticesPlugin.h"

void AnimateVerticesPlugin::onPluginLoad()
{
    QOpenGLShader shader(QOpenGLShader::Vertex);


    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("animate-vertices-1.vert");
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("animate-vertices-1.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    t.start();
}

void AnimateVerticesPlugin::preFrame(){
    // bind shader and define uniforms
    program->bind();
    //program->setUniformValue("time", 6);
    program->setUniformValue("Pi", 3.1415f);
    program->setUniformValue("freq", 2.5f);
    program->setUniformValue("amplitude", 0.1f);
    program->setUniformValue("time", t.elapsed()/1000.f);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    QMatrix3x3 normalMatrix =  camera()->viewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", normalMatrix);
}

void AnimateVerticesPlugin::postFrame(){
    program->release();
}
