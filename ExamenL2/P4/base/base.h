#ifndef _Base_H
#define _Base_H

#include "plugin.h"
#include "glwidget.h"
#include <iostream>
#include <cmath>

class Base : public QObject, public Plugin
 {
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "Plugin")
     Q_INTERFACES(Plugin)

 public:
    void onPluginLoad();

    float crossModul(Vector v1, Vector v2);
    float getMinY(Face f);
    float getFaceArea(Face f);

 private:

 };

 #endif
