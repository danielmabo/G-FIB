#ifndef _DRAWSMOOTH_H
#define _DRAWSMOOTH_H

#include "plugin.h"
#include "glwidget.h"
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

class DrawSmooth : public QObject, public Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin")
  Q_INTERFACES(Plugin)

 public:
  ~DrawSmooth();
  void cleanUp();

  void onSceneClear();
  void onPluginLoad();
  void onObjectAdd();
  bool drawScene();
  bool drawObject(int i);

 private:
  void addVBO(unsigned int currentObject);

  // Guarem el identificados d'un VAO amb tots els seus VBO per a cadaa objecte, per aixo tenim vectors
  // de identicficadors ja que per a cada objecte the un identificador de cada guardat.
  vector<GLuint> VAOs;          // ID of VAOs
  vector<GLuint> coordBuffers;  // ID of vertex coordinates buffer
  vector<GLuint> normalBuffers; // ID of normal components buffer
  vector<GLuint> stBuffers;     // ID of (s,t) buffer
  vector<GLuint> colorBuffers;  // ID of color buffer
  vector<GLuint> indexBuffers;  // ID of index buffer
  vector<int> numVertices;
};

#endif
