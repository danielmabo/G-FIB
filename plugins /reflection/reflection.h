#ifndef _GLOWING_H
#define _GLOWING_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class Reflection : public QObject, public Plugin
{
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "Plugin")
     Q_INTERFACES(Plugin)

 public:
    void onPluginLoad();
    bool paintGL();
    void paintScene();

 private:
    QOpenGLShaderProgram* programRefl;
    QOpenGLShader* vsRefl;
    QOpenGLShader* fsRefl;
    QOpenGLShaderProgram* programMirror;
    QOpenGLShader* vsMirror;
    QOpenGLShader* fsMirror;
    GLuint textureId;
 };

 #endif
