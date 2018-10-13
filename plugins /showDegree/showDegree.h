#ifndef _ShowDegree_H
#define _ShowDegree_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class ShowDegree : public QObject, Plugin {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")
    Q_INTERFACES(Plugin)

    public:
        void onPluginLoad();
        void preFrame();
        void postFrame();

        void getObjectDegree();
        void drawRect();

     private:
        GLuint textureID;
        QOpenGLShaderProgram* program;
        QOpenGLShader* vs;
        QOpenGLShader* fs;
        float vertDegree;
        bool created = false;
};

#endif
