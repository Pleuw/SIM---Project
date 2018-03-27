#include "camera.h"

Camera::Camera(float radius,const glm::vec3 &center,int mode) 
  : _m(NONE),
    _w(0), 
    _h(0), 
    _p(0,0),
    _c(glmToVec3(center)),
    _r(radius),
    _t(),
    _f(45.0f),
    _d(mode),
    _up(0,0,0),
    _right(0,0,0),
    _view(0,0,0),
    _zmin(0),
    _zmax(0) {

}

void Camera::initialize(int w,int h,bool replace) {
  const float tmp1 = 100.0f;
  const float tmp2 = 3.0f;

  int wo2 = w/2;
  int ho2 = h/2;
  int rad = wo2<ho2 ? wo2 : ho2;
  
  // data initialization 
  _m = NONE;
  _w = w;
  _h = h;
  _t = TrackBall(rad*2,Vec2f(wo2,ho2));
  _f = 45.0f;
  
  // projection transformations  
  if(_d==PERSP) {
    _matp = glmToMat4(glm::perspective(_f,(float)_w/(float)_h,_r/tmp1,_r*tmp1));
  } else {
    _matp = glmToMat4(glm::ortho((float)(-_w),(float)_w,(float)(-_h),(float)_h,0.0f,_r*100.0f));
  }
  
  if(!replace)
    return;

  // camera transformations
  _matm = glmToMat4(glm::lookAt(glm::vec3(_c[0],_c[1],_c[2]-tmp2*_r),
				glm::vec3(_c[0],_c[1],_c[2]),
				glm::vec3(0.0,1.0,0.0)));

  // update params 
  updateCamVectors(_matm);
  updateCamDists(_matm);
}

void Camera::setFovy(float f) {
  _f = f;
  initialize(_w,_h,false);
}

void Camera::setMode(int m) {
  if(_d!=m) {
    _d = m;
    initialize(_w,_h,false);
  }
}
