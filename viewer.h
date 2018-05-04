#ifndef VIEWER_H
#define VIEWER_H

// GLEW lib: needs to be included first!!
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>

// OpenGL Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QGLFormat>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <stack>

#include "camera.h"
#include "grid.h"
#include "shader.h"

class Viewer : public QGLWidget {
 public:
  Viewer(const QGLFormat &format=QGLFormat::defaultFormat());
  ~Viewer();

 protected :
  virtual void paintGL();
  virtual void initializeGL();
  virtual void resizeGL(int width,int height);
  virtual void keyPressEvent(QKeyEvent *ke);
  virtual void mousePressEvent(QMouseEvent *me);
  virtual void mouseMoveEvent(QMouseEvent *me);

 private:
  void createVAO();
  void deleteVAO();

  void createFBO();
  void deleteFBO();
  void initFBO();

  void createShaders();
  void deleteShaders();
  void disableShader();

  void drawQuad();
  void drawTerrain();
  void computeNoiseShader();
  void computeNormalShader();
  void computeRendering();

  void createTexture();
  void deleteTexture();

  // render texture ids
  GLuint _rendColorId;
  GLuint _rendNormalId;
  GLuint _rendDepthId;

  QTimer        *_timer;    // timer that controls the animation
  unsigned int   _currentstep; // current shader index

  Shader *_terrainShader;
  Shader *_noiseShader;
  Shader *_normalShader;

  Grid   *_grid;      // the grid
  Camera *_cam;    // the camera

  glm::vec3 _light; // light direction
  bool      _mode;  // camera motion or light motion
/*
  std::vector<std::string> _vertexFilenames;   // all vertex filenames
  std::vector<std::string> _fragmentFilenames; // all fragment filenames
  std::vector<Shader *>    _shaders;           // all the shaders
*/

  //vao
  GLuint _vaoTerrain;
  GLuint _terrain[2];
  GLuint _quad;
  GLuint _vaoQuad;

  //noise texture
  GLuint _noiseHeightId;
  GLuint _noiseNormalId;
  GLuint idShaderTerrain;
  //fbo
  GLuint _fbo_normal;
  GLuint _fbo_renderer;


  GLuint _textHerbe;
  GLuint _textFalaise;

};

#endif // VIEWER_H
