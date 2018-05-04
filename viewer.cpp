#include "viewer.h"

#include <math.h>
#include <iostream>
#include <QTime>

using namespace std;


Viewer::Viewer(const QGLFormat &format)
  : QGLWidget(format),
    _currentstep(2),
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
  deleteTexture();
}

// Create a Vertex Array Object
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

// Remove a Vertex Array Object
void Viewer::deleteVAO() {
  // delete your VAO here (function called in destructor)
  glDeleteBuffers(2,_terrain);
  glDeleteBuffers(1,&_quad);
  glDeleteVertexArrays(1,&_vaoTerrain);
  glDeleteVertexArrays(1,&_vaoQuad);

}

// Remote a Frame Buffer Object
void Viewer::deleteFBO() {
  // delete all FBO Ids
  glDeleteFramebuffers(1,&_fbo_normal);
  glDeleteTextures(1,&_noiseHeightId);
  glDeleteTextures(1,&_noiseNormalId);
  glDeleteFramebuffers(1,&_fbo_renderer);
  glDeleteTextures(1,&_rendColorId);
  glDeleteTextures(1,&_rendNormalId);
  glDeleteTextures(1,&_rendDepthId);
}

// Create a Frame Buffer Object
void Viewer::createFBO() {
    // Ids needed for the FBO and associated textures
    glGenFramebuffers(1,&_fbo_normal);
    glGenTextures(1,&_noiseHeightId);
    glGenTextures(1,&_noiseNormalId);
    glGenFramebuffers(1,&_fbo_renderer);
    glGenTextures(1,&_rendColorId);
    glGenTextures(1,&_rendNormalId);
    glGenTextures(1,&_rendDepthId);

  }

// Initialize a Frame Buffer Object
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

  //

  glBindTexture(GL_TEXTURE_2D,_rendColorId);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA32F,width(),height(),0,GL_RGBA,GL_FLOAT,NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_2D,_rendNormalId);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA32F,width(),height(),0,GL_RGBA,GL_FLOAT,NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_2D,_rendDepthId);
  glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,width(),height(),0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindFramebuffer(GL_FRAMEBUFFER,_fbo_renderer);
  glBindTexture(GL_TEXTURE_2D,_rendColorId);
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,_rendColorId,0);
  glBindTexture(GL_TEXTURE_2D,_rendNormalId);
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,_rendNormalId,0);
  glBindTexture(GL_TEXTURE_2D,_rendDepthId);
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,_rendDepthId,0);
  glBindFramebuffer(GL_FRAMEBUFFER,0);


  // test if everything is ok
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    cout << "Warning: FBO not complete!" << endl;

  // disable FBO
  glBindFramebuffer(GL_FRAMEBUFFER,0);

}

// Delete a texture
void Viewer::deleteTexture(){
  glDeleteTextures(1,&_textHerbe);
  glDeleteTextures(1,&_textFalaise);
}

// Create textures
void Viewer::createTexture(){
  glGenTextures(1,&_textFalaise);
  QImage img1 = QGLWidget::convertToGLFormat(QImage("textures/textFalaise.jpg"));
  glBindTexture(GL_TEXTURE_2D,_textFalaise);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img1.width(),img1.height(),0, GL_RGBA,GL_UNSIGNED_BYTE,(const GLvoid *)img1.bits());

  glGenTextures(2,&_textHerbe);
  QImage img2 = QGLWidget::convertToGLFormat(QImage("textures/textHerbe.jpg"));
  glBindTexture(GL_TEXTURE_2D,_textHerbe);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2.width(),img2.height(),0, GL_RGBA,GL_UNSIGNED_BYTE,(const GLvoid *)img2.bits());
}

// Create shaders
void Viewer::createShaders() {

  // create 3 shaders
  _terrainShader = new Shader();
  _normalShader = new Shader();
  _noiseShader = new Shader();

  _terrainShader->load("shaders/constant.vert","shaders/constant.frag");
  _normalShader->load("shaders/normal.vert","shaders/normal.frag");
  _noiseShader->load("shaders/noise.vert","shaders/noise.frag");
}

// Delete shaders
void Viewer::deleteShaders() {
  delete _terrainShader; _terrainShader = NULL;
  delete _normalShader; _normalShader = NULL;
  delete _noiseShader; _noiseShader = NULL;
}

// Draw 2 triangles insine a square
void Viewer::drawQuad() {

  // Draw the 2 triangles
  glBindVertexArray(_vaoQuad);
  glDrawArrays(GL_TRIANGLES,0,6);
  glBindVertexArray(0);
}

// Execute the noise shader
void Viewer::computeNoiseShader() {

  if(_currentstep > 0){
    // clear the color and depth buffers
    glViewport(0,0,_grid->width(),_grid->height());
    // activate the created framebuffer object
    glBindFramebuffer(GL_FRAMEBUFFER,_fbo_normal);
    // draw in _noiseHeightId
    GLenum buffer_height [] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1,buffer_height);
  } else {
    glViewport(0,0,width(),height());
  }
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

// Execute the normal shader
void Viewer::computeNormalShader() {
  if (_currentstep >= 1) {
    if (_currentstep != 1) {
      glViewport(0,0,_grid->width(),_grid->height());
      // activate the created framebuffer object
      glBindFramebuffer(GL_FRAMEBUFFER,_fbo_normal);
      // draw in _noiseNormalId
      GLenum buffer_normal [] = {GL_COLOR_ATTACHMENT1};
      glDrawBuffers(1,buffer_normal);
    } else {
      glViewport(0,0,width(),height());
    }
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

}

// Make the rendering
void Viewer::computeRendering() {
  if(_currentstep >= 2){

      if(_currentstep > 3){
          // activate the created framebuffer object
          glBindFramebuffer(GL_FRAMEBUFFER,_fbo_renderer);
          // draw in _rendColorId & _rendNormalId
          GLenum buffer_render [] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
          glDrawBuffers(2,buffer_render);
      }
      // activate the shader
      glUseProgram(_terrainShader->id());
      // clear buffers
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glUseProgram(_terrainShader->id());

      glUniformMatrix4fv(glGetUniformLocation(_terrainShader->id(),"projMat"),1,GL_FALSE,&(_cam->projMatrix()[0][0]));  // same for all matrix
      glUniformMatrix4fv(glGetUniformLocation(_terrainShader->id(),"mdvMat"),1,GL_FALSE,&(_cam->mdvMatrix()[0][0])); // same for all matrix
      glUniformMatrix3fv(glGetUniformLocation(_terrainShader->id(),"normalMat"),1,GL_FALSE,&(_cam->normalMatrix()[0][0]));
      //glUniform4fv(glGetUniformLocation(idterrainShader,"matrixModel"),1,GL_FALSE,modelMatrix); // same for all matrix

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D,_noiseHeightId);
      glUniform1i(glGetUniformLocation(_terrainShader->id(),"perlinTex"),0);

      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D,_noiseNormalId);
      glUniform1i(glGetUniformLocation(_terrainShader->id(),"normalTex"),1);


      glBindVertexArray(_vaoTerrain);
      glDrawElements(GL_TRIANGLES,3*_grid->nbFaces(),GL_UNSIGNED_INT,(void *)0);
      glBindVertexArray(0);

      // disable shader
      glUseProgram(0);
      // desactivate fbo
      glBindFramebuffer(GL_FRAMEBUFFER,0);
  }
}

void Viewer::disableShader() {
  // desactivate all shaders
  glUseProgram(0);
}

// Draw function
void Viewer::paintGL() {


  computeNoiseShader();

  computeNormalShader();

  computeRendering();



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
    _noiseShader->load("shaders/noise.vert","shaders/noise.frag");
    _normalShader->load("shaders/normal.vert","shaders/normal.frag");
    _terrainShader->load("shaders/constant.vert","constant.frag");
  }

  // space bar : switch to next step
  if(ke->key()==Qt::Key_Space) {
    _currentstep = (_currentstep+1)%3;
  }

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
  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glViewport(0,0,width(),height());

  // initialize camera
  _cam->initialize(width(),height(),true);

  // load shader files
  createShaders();
/*
  // init and load all shader files
  for(unsigned int i=0;i<_vertexFilenames.size();++i) {
    _shaders.push_back(new Shader());
    _shaders[i]->load(_vertexFilenames[i].c_str(),_fragmentFilenames[i].c_str());
  }
*/
  // VAO creation
  createVAO();

  // create/init FBO
  createFBO();
  initFBO();
createTexture();
  // starts the timer
  _timer->start();
}
