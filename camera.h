#ifndef CAMERA_H
#define CAMERA_H

#include "trackball.h"
#include "quat.h"
#include "vec2.h"
#include "vec3.h"
#include "mat4.h"

// OpenGL Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

class Camera {
 public:
  enum {NONE, ROTATE, MOVEXY, MOVEZ};
  static const int PERSP=0;
  static const int ORTHO=1;

  Camera(float radius=1,const glm::vec3 &center=glm::vec3(0,0,0),int mode=PERSP);
  
  void initialize(int w,int h,bool replace=true);
  void setFovy(float f);
  void setMode(int m);

  inline void initRotation(const glm::vec2 &p);
  inline void initMoveXY(const glm::vec2 &p);
  inline void initMoveZ(const glm::vec2 &p);
  inline void move(const glm::vec2 &p);
  
  inline int w() const { return _w; } // width
  inline int h() const { return _h; } // height

  inline const glm::vec3 up()    const { return vec3ToGlm(_view);  } // up vector
  inline const glm::vec3 right() const { return vec3ToGlm(_right); } // right vector
  inline const glm::vec3 view()  const { return vec3ToGlm(_up);    } // view vector

  inline float zmin()  const { return _zmin;  } // min distance to object
  inline float zmax()  const { return _zmax;  } // max distance to object
  inline float fovy()  const { return _f;     } // aspect ratio

  inline const glm::vec2 pt() const { return vec2ToGlm(_p); } // current clicked point

  // access 
  inline glm::mat4 projMatrix() const {return mat4ToGlm(_matp);}
  inline glm::mat4 mdvMatrix () const {return mat4ToGlm(_matm);}
  inline glm::mat3 normalMatrix () const {return glm::mat3(glm::inverseTranspose(mdvMatrix()));}

 protected:
  inline void rotate(const Vec2f &p);
  inline void moveXY(const Vec2f &p);
  inline void moveZ(const Vec2f &p);

 private:
  inline void updateCamVectors(const Mat4f &m);
  inline void updateCamDists(const Mat4f &m);

  // TMP functions, until all Vec2/Vec3/Mat4 are replaced by glm
  inline glm::vec2 vec2ToGlm(const Vec2f &v) const;
  inline glm::vec3 vec3ToGlm(const Vec3f &v) const;
  inline glm::vec4 vec4ToGlm(const Vec4f &v) const;
  inline glm::mat4 mat4ToGlm(const Mat4f &m) const;
  inline Vec2f glmToVec2(const glm::vec2 &v) const;
  inline Vec3f glmToVec3(const glm::vec3 &v) const;
  inline Vec4f glmToVec4(const glm::vec4 &v) const;
  inline Mat4f glmToMat4(const glm::mat4 &m) const;

  int       _m; // moving mode 
  int       _w; // width
  int       _h; // height 
  Vec2f     _p; // departure point when moving 
  Vec3f     _c; // center 
  float     _r; // radius
  TrackBall _t; // trackball
  float     _f; // fovy
  Vec4i     _v; // viewport
  int       _d; // mode (persp or ortho)

  Vec3f     _up;
  Vec3f     _right;
  Vec3f     _view;
  float     _zmin;
  float     _zmax;
  Mat4f     _matm;
  Mat4f     _matp;
};

inline glm::vec2 Camera::vec2ToGlm(const Vec2f &v) const {
  return glm::vec2(v.x(),v.y());
}

inline glm::vec3 Camera::vec3ToGlm(const Vec3f &v) const {
  return glm::vec3(v.x(),v.y(),v.z());
}

inline glm::vec4 Camera::vec4ToGlm(const Vec4f &v) const {
  return glm::vec4(v[0],v[1],v[2],v[3]);
}

inline glm::mat4 Camera::mat4ToGlm(const Mat4f &m) const {
  return glm::make_mat4(m.ptr());
}

inline Vec2f Camera::glmToVec2(const glm::vec2 &v) const {
  return Vec2f(v[0],v[1]);
}

inline Vec3f Camera::glmToVec3(const glm::vec3 &v) const {
  return Vec3f(v[0],v[1],v[2]);
}

inline Vec4f Camera::glmToVec4(const glm::vec4 &v) const {
  return Vec4f(v[0],v[1],v[2],v[3]);
}

inline Mat4f Camera::glmToMat4(const glm::mat4 &m) const {
  return Mat4f(m[0][0],m[1][0],m[2][0],m[3][0],
	       m[0][1],m[1][1],m[2][1],m[3][1],
	       m[0][2],m[1][2],m[2][2],m[3][2],
	       m[0][3],m[1][3],m[2][3],m[3][3]);
}

inline void Camera::initRotation(const glm::vec2 &p) {
  _m = ROTATE;
  _p = glmToVec2(p);
  _t.beginTracking(_p);
}

inline void Camera::initMoveXY(const glm::vec2 &p) {
  _m = MOVEXY;
  _p = glmToVec2(p);
}

inline void Camera::initMoveZ(const glm::vec2 &p) {
  _m = MOVEZ;
  _p = glmToVec2(p);
}

inline void Camera::move(const glm::vec2 &p) {
  switch(_m) {
  case ROTATE: rotate(glmToVec2(p)); break;
  case MOVEXY: moveXY(glmToVec2(p)); break;
  case MOVEZ:  moveZ(glmToVec2(p));  break;
  default: break;
  }
}

inline void Camera::rotate(const Vec2f &p) {
  Mat4f mo = _matm;
  
  // compute rotation matrix 
  const Vec3f tr = Vec3f(mo[12],mo[13],mo[14]);
  const Mat4f t1 = Mat4f::identity().translateEq(-tr);
  const Mat4f t2 = Mat4f::identity().translateEq(tr);
  const Mat4f mr = _t.track(p).toMat4(); 
  
  _matm = t2*mr*t1*mo;

  // update params
  _p = p;
  _t.beginTracking(_p);
  updateCamVectors(_matm);
  updateCamDists(_matm);
}

inline void Camera::moveXY(const Vec2f &p) {
  const float s = _r/300.0;

  // compute translation matrix 
  _matm = _matm.translateEq(Vec3f((p[0]-_p[0])*s,(p[1]-_p[1])*s,0.0f));

  // update params 
  _p = p;
  updateCamDists(_matm);
}

inline void Camera::moveZ(const Vec2f &p) {
  const float s = _r/100.0;

  // compute translation matrix 
  _matm = _matm.translateEq(Vec3f(0.0f,0.0f,(_p[1]-p[1])*s));

  // update params 
  _p = p;
  updateCamDists(_matm);
}

inline void Camera::updateCamVectors(const Mat4f &m) {
  _up    = Vec3f(m[0],m[4],m[8 ]);
  _right = Vec3f(m[1],m[5],m[9 ]);
  _view  = Vec3f(m[2],m[6],m[10]);
}

inline void Camera::updateCamDists(const Mat4f &m) {
  const float fact = 1.0f;
  const float eps = 0.0f;
  const Vec4d ca  = m*Vec4d(_c[0],_c[1],_c[2],1.0);
  const float d = (Vec3f(ca[0],ca[1],ca[2])).length();
  
  _zmin = d-fact*_r;
  _zmin = _zmin<=eps ? eps : _zmin;
  _zmax = _zmin + fact*_r;
}

#endif // CAMERA_H
