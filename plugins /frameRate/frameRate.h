#ifndef _FrameRate_H
#define _FrameRate_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer>
#include <QPainter>
#include <QTimer>
#include <QElapsedTimer>

class FrameRate : public QObject, Plugin {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")
    Q_INTERFACES(Plugin)

    public:
        void onPluginLoad();
        void preFrame();
        void postFrame();
        void drawRect();

    public slots:
        void getFrameRate();

     private:
        GLuint textureID;
        QOpenGLShaderProgram* program;
        QOpenGLShader* vs;
        QOpenGLShader* fs;

        QTimer *timer;
        //QElapsedTimer timer;
        bool created = false;
        float frameRate = 0.;
        int nframes = 0;
};

#endif
