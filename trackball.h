#ifndef TRACKBALL_H
#define TRACKBALL_H

#include "vec2.h"
#include "vec3.h"
#include "quat.h"

class TrackBall {
 public:
  TrackBall();
  TrackBall(float radius, const Vec2f &center);
  TrackBall(const TrackBall &t);
  
  inline TrackBall& operator = (const TrackBall &t);
  
  inline void beginTracking(const Vec2f &pt);
  inline Quatf track(const Vec2f &pt);
  inline void setCenter(const Vec2f &center);
  inline void setRadius(float radius);
    
 private:
  Vec2f _startPos;
  Vec3f _startSphPos;
  Vec2f _center;
  float _radius;
};

inline TrackBall& TrackBall::operator = (const TrackBall &t) {
  _startPos    = t._startPos;
  _startSphPos = t._startSphPos;
  _center      = t._center;
  _radius      = t._radius;
  
  return *this;
}

inline void TrackBall::beginTracking(const Vec2f &pt) {
  Vec2f p = pt - _center;
  _startPos = p;
  _startSphPos = Vec3f(p.x(), p.y(), _radius);
}

inline Quatf TrackBall::track(const Vec2f &pt) {
  Vec2f p = pt - _center;
  float angle = (p-_startPos).length()*4/_radius;
  Vec3f ptSph = Vec3f(p.x(),p.y(),_radius);
  Vec3f axis = (ptSph ^ _startSphPos).normal();
  
  if(axis.hasNan()  || axis.hasInf())
    return Quatf(1,0,0,0);
  
  return Quatf(axis,angle);
}

inline void TrackBall::setCenter(const Vec2f &center) {
  _center = center;
}

inline void TrackBall::setRadius(float radius) {
  _radius = radius;
}

#endif // TRACKBALL_H

