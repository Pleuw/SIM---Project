#include "viewer.h"

#include <math.h>
#include <iostream>
#include <QTime>

using namespace std;


Viewer::Viewer(const QGLFormat &format)
  : QGLWidget(format),
    _timer(new QTimer(this)),
    _light(glm::vec3(0,0,1)),
    _mode(false) {

  setlocale(LC_ALL,"C");
  _grid = new Grid();
  _cam = new Camera(sqrt(2),glm::vec3(0,0,0));

  _timer->setInterval(10);
  connect(_timer,SIGNAL(timeout()),this,SLOT(updateGL()));
}

Viewer::~Viewer() {
  delete _timer;
  delete _grid;
  delete _cam;


  deleteShaders();
  deleteVAO();
  deleteFBO();
}

void Viewer::createVAO() {

  //Vertexs for create the quad
  const GLfloat quadData[] = {-1.0f,-1.0f,0.0f, 1.0f,-1.0f,0.0f, -1.0f,1.0f,0.0f, -1.0f,1.0f,0.0f, 1.0f,-1.0f,0.0f, 1.0f,1.0f,0.0f };

  // create some buffers inside the GPU memory
  glGenBuffers(2,_terrain);
  glGenBuffers(1,&_quad);
  glGenVertexArrays(1,&_vaoTerrain);
  glGenVertexArrays(1,&_vaoQuad);


  // create the VBO associated with the grid (the terrain)  glBindVertexArray(_vaoTerrain);
  glBindBuffer(GL_ARRAY_BUFFER,_terrain[0]); // vertices
  glBufferData(GL_ARRAY_BUFFER,_grid->nbVertices()*3*sizeof(float),_grid->vertices(),GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_terrain[1]); // indices
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,_grid->nbFaces()*3*sizeof(int),_grid->faces(),GL_STATIC_DRAW);

  // create the VBO associated with the screen quad
  glBindVertexArray(_vaoQuad);
  glBindBuffer(GL_ARRAY_BUFFER,_quad); // vertices
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadData),quadData,GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
  glEnableVertexAttribArray(0);
}

void Viewer::deleteVAO() {
  // delete your VAO here (function called in destructor)
  glDeleteBuffers(2,_terrain);
  glDeleteBuffers(1,&_quad);
  glDeleteVertexArrays(1,&_vaoTerrain);
  glDeleteVertexArrays(1,&_vaoQuad);

}

void Viewer::deleteFBO() {
  // delete all FBO Ids
  glDeleteFramebuffers(1,&_fbo_normal);
  glDeleteTextures(1,&_noiseHeightId);
  glDeleteTextures(1,&_noiseNormalId);
}

void Viewer::createFBO() {
    // Ids needed for the FBO and associated textures
    glGenFramebuffers(1,&_fbo_normal);
    glGenTextures(1,&_noiseHeightId);
    glGenTextures(1,&_noiseNormalId);


  }

void Viewer::initFBO() {

  glBindTexture(GL_TEXTURE_2D,_noiseHeightId);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA32F,_grid->width(),_grid->height(),0,GL_RGBA,GL_FLOAT,NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_2D,_noiseNormalId);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA32F,_grid->width(),_grid->height(),0,GL_RGBA,GL_FLOAT,NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindFramebuffer(GL_FRAMEBUFFER,_fbo_normal);
  glBindTexture(GL_TEXTURE_2D,_noiseHeightId);
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,_noiseHeightId,0);
  glBindTexture(GL_TEXTURE_2D,_noiseNormalId);
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,_noiseNormalId,0);
  glBindFramebuffer(GL_FRAMEBUFFER,0);

  // test if everything is ok
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    cout << "Warning: FBO not complete!" << endl;

  // disable FBO
  glBindFramebuffer(GL_FRAMEBUFFER,0);

}


void Viewer::createShaders() {

  // create 3 shaders
  _basicShader = new Shader();
  _normalShader = new Shader();
  _noiseShader = new Shader();

  _basicShader->load("shaders/constant.vert","shaders/constant.frag");
  _normalShader->load("shaders/normal.vert","shaders/normal.frag");
  _noiseShader->load("shaders/noise.vert","shaders/noise.frag");
}


void Viewer::deleteShaders() {
  delete _basicShader; _basicShader = NULL;
  delete _normalShader; _normalShader = NULL;
  delete _noiseShader; _noiseShader = NULL;
}

void Viewer::drawQuad() {

  // Draw the 2 triangles
  glBindVertexArray(_vaoQuad);
  glDrawArrays(GL_TRIANGLES,0,6);
  glBindVertexArray(0);
}

void Viewer::computeNoiseShader() {

  // clear the color and depth buffers
  glViewport(0,0,_grid->width(),_grid->height());
  // activate the created framebuffer object
  glBindFramebuffer(GL_FRAMEBUFFER,_fbo_normal);
  // draw in _noiseHeightId
  GLenum buffer_height [] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1,buffer_height);
  // activate the shader
  glUseProgram(_noiseShader->id());
  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawQuad();

  // disable shader
  glUseProgram(0);
  // desactivate fbo
  glBindFramebuffer(GL_FRAMEBUFFER,0);


}

void Viewer::computeNormalShader() {
  glViewport(0,0,_grid->width(),_grid->height());
  // activate the created framebuffer object
  glBindFramebuffer(GL_FRAMEBUFFER,_fbo_normal);
  // draw in _noiseNormalId
  GLenum buffer_normal [] = {GL_COLOR_ATTACHMENT1};
  glDrawBuffers(1,buffer_normal);
  // activate the shader
  glUseProgram(_normalShader->id());
  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // send the noise to shader
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,_noiseHeightId);
  glUniform1i(glGetUniformLocation(_normalShader->id(),"heightmap"),0);
  // draw base quad

  drawQuad();


  // disable shader
  glUseProgram(0);
  // desactivate fbo
  glBindFramebuffer(GL_FRAMEBUFFER,0);

}


void Viewer::disableShader() {
  // desactivate all shaders
  glUseProgram(0);
}

void Viewer::paintGL() {


  computeNoiseShader();

  computeNormalShader();


  // tell the GPU to stop using this shader 
  disableShader();
}

void Viewer::resizeGL(int width,int height) {
  _cam->initialize(width,height,false);
  glViewport(0,0,width,height);
  updateGL();
}

void Viewer::mousePressEvent(QMouseEvent *me) {
  const glm::vec2 p((float)me->x(),(float)(height()-me->y()));

  if(me->button()==Qt::LeftButton) {
    _cam->initRotation(p);
    _mode = false;
  } else if(me->button()==Qt::MidButton) {
    _cam->initMoveZ(p);
    _mode = false;
  } else if(me->button()==Qt::RightButton) {
    _light[0] = (p[0]-(float)(width()/2))/((float)(width()/2));
    _light[1] = (p[1]-(float)(height()/2))/((float)(height()/2));
    _light[2] = 1.0f-std::max(fabs(_light[0]),fabs(_light[1]));
    _light = glm::normalize(_light);
    _mode = true;
  } 

  updateGL();
}

void Viewer::mouseMoveEvent(QMouseEvent *me) {
  const glm::vec2 p((float)me->x(),(float)(height()-me->y()));
 
  if(_mode) {
    // light mode
    _light[0] = (p[0]-(float)(width()/2))/((float)(width()/2));
    _light[1] = (p[1]-(float)(height()/2))/((float)(height()/2));
    _light[2] = 1.0f-std::max(fabs(_light[0]),fabs(_light[1]));
    _light = glm::normalize(_light);
    _mode = true;
  } else {
    // camera mode
    _cam->move(p);
  }

  updateGL();
}

void Viewer::keyPressEvent(QKeyEvent *ke) {
  
  // key a: play/stop animation
  if(ke->key()==Qt::Key_A) {
    if(_timer->isActive()) 
      _timer->stop();
    else 
      _timer->start();
  }

  // key i: init camera
  if(ke->key()==Qt::Key_I) {
    _cam->initialize(width(),height(),true);
  }
  
  // key f: compute FPS
  if(ke->key()==Qt::Key_F) {
    int elapsed;
    QTime timer;
    timer.start();
    unsigned int nb = 500;
    for(unsigned int i=0;i<nb;++i) {
      paintGL();
    }
    elapsed = timer.elapsed();
    double t = (double)nb/((double)elapsed);
    cout << "FPS : " << t*1000.0 << endl;
  }

  // key r: reload shaders 
  if(ke->key()==Qt::Key_R) {
    for(unsigned int i=0;i<_vertexFilenames.size();++i) {
      _shaders[i]->reload(_vertexFilenames[i].c_str(),_fragmentFilenames[i].c_str());
    }
  }

//  // space: next shader
//  if(ke->key()==Qt::Key_Space) {
//    _currentshader = (_currentshader+1)%_shaders.size();
//  }

  updateGL();
}

void Viewer::initializeGL() {
  // make this window the current one
  makeCurrent();

  // init and chack glew
  glewExperimental = GL_TRUE;

  if(glewInit()!=GLEW_OK) {
    cerr << "Warning: glewInit failed!" << endl;
  }


  // init OpenGL settings
  glClearColor(0.0,1.0,0.0,1.0);
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glViewport(0,0,width(),height());

  // initialize camera
  _cam->initialize(width(),height(),true);

  // load shader files
  createShaders();

  // init and load all shader files
  for(unsigned int i=0;i<_vertexFilenames.size();++i) {
    _shaders.push_back(new Shader());
    _shaders[i]->load(_vertexFilenames[i].c_str(),_fragmentFilenames[i].c_str());
  }

  // VAO creation 
  createVAO();

  // starts the timer 
  _timer->start();
}

