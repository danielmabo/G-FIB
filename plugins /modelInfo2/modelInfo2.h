#ifndef _ModelInfo2_H
#define _ModelInfo2_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class ModelInfo2 : public QObject, Plugin {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")
    Q_INTERFACES(Plugin)

    public:
        void onPluginLoad();
        void preFrame();
        void postFrame();

        void getModelInfo();
        void drawRect();

     private:
        GLuint textureID;
        QOpenGLShaderProgram* program;
        QOpenGLShader* vs;
        QOpenGLShader* fs;
        int nobj, npol, nvert;
        float ntriang;
        bool created = false;
};

#endif
