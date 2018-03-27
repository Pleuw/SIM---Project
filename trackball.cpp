#include "trackball.h" 

TrackBall::TrackBall()
: _startPos(),
  _startSphPos(),
  _center(Vec2f(0, 0)),
  _radius(1) {
}

TrackBall::TrackBall(float radius, const Vec2f &center)
: _startPos(),
  _startSphPos(),
  _center(center),
  _radius(radius) {
  
}

TrackBall::TrackBall(const TrackBall &t)
: _startPos(t._startPos),
  _startSphPos(t._startSphPos),
  _center(t._center),
  _radius(t._radius) {

}
