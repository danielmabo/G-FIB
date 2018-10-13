#ifndef _MULTITEX_H
#define _MULTITEX_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class TextureSplatting : public QObject, public Plugin
 {
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "Plugin")
#endif
     Q_INTERFACES(Plugin)

 public:
    void onPluginLoad();
    void preFrame();
    void postFrame();

 private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;
    GLuint textureId0, textureId1, textureId2;
 };

 #endif
