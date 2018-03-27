#ifndef QUAT_H
#define QUAT_H

#include "vec3.h"
#include "mat3.h"
#include "mat4.h"

/*==============================================================================
  CLASS Quat
  ==============================================================================*/
//! Quaternion class.

template<class T>
class Quat {
 public:
  Quat();
  Quat(T angle, T x, T y, T z);
  Quat(const Vec3<T> &axis, T angle);
  Quat(const Quat &q);
  Quat& operator = (const Quat &q);

  bool operator == (const Quat &q) const;
  bool operator != (const Quat &q) const;
  bool operator <  (const Quat &q) const;
  bool operator <= (const Quat &q) const;
  bool operator >  (const Quat &q) const;
  bool operator >= (const Quat &q) const;

  const T& operator [] (int index) const;
  operator T*();
  operator const T*() const;
  T* ptr();
  const T* ptr() const;

  Quat operator +   (const Quat &q) const;
  Quat operator -   (const Quat &q) const;
  Quat operator *   (const Quat &q) const;
  Quat operator *   (const T &q) const;
  Quat operator /   (const T &q) const;
  Quat& operator += (const Quat &q);
  Quat& operator -= (const Quat &q);
  Quat& operator *= (const T &q);
  Quat& operator /= (const T &q);
  Quat& operator - ();

  float length()    const;
  float sqrLength() const;
  Quat& scale(float newLength);
  Quat& normalize();

  Quat conjugate()   const;
  Quat unitInverse() const;
  Quat inverse()     const;

  Mat4<T> toMat4() const;
  Mat3<T> toMat3() const;
  Vec3<T> axis()   const;
  T angle()        const;

 private:
  T _e[4];
};

template<class T>
Quat<T>::Quat() {
  _e[0] = _e[1] = _e[2] = 0;
  _e[3] = 1;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::Quat(T angle, T x, T y, T z) {
  _e[0] = angle;
  _e[1] = x;
  _e[2] = y;
  _e[3] = z;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::Quat(const Vec3<T> &axis, T angle) {
  _e[0] = cos(angle/2);

  float tmp = sin(angle/2);
  _e[1] = axis[0]*tmp;
  _e[2] = axis[1]*tmp;
  _e[3] = axis[2]*tmp;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::Quat(const Quat<T> &q) {
  *this = q;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator = (const Quat<T> &q) {
  _e[0] = q._e[0];
  _e[1] = q._e[1];
  _e[2] = q._e[2];
  _e[3] = q._e[3];
  
  return *this;
}
  
//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator == (const Quat<T> &q) const {
  return (q._e[0] == _e[0]) && (q._e[1] == _e[1]) && (q._e[2] == _e[2]) && (q._e[3] == _e[3]);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator != (const Quat<T> &q) const {
  return (q._e[0] != _e[0]) || (q._e[1] != _e[1]) || (q._e[2] != _e[2]) || (q._e[3] != _e[3]);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator < (const Quat<T> &q) const {
  return (_e[0] < q._e[0]) || ((_e[0] == q._e[0]) && ((_e[1] < q._e[1]) || ((_e[1] == q._e[1]) && ((_e[2] < q._e[2]) || ((_e[2] == q._e[2]) && (_e[3] < q._e[3]))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator <= (const Quat<T> &q) const {
  return (_e[0] < q._e[0]) || ((_e[0] == q._e[0]) && ((_e[1] < q._e[1]) || ((_e[1] == q._e[1]) && ((_e[2] < q._e[2]) || ((_e[2] == q._e[2]) && (_e[3] <= q._e[3]))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator > (const Quat<T> &q) const {
  return (_e[0] > q._e[0]) || ((_e[0] == q._e[0]) && ((_e[1] > q._e[1]) || ((_e[1] == q._e[1]) && ((_e[2] > q._e[2]) || ((_e[2] == q._e[2]) && (_e[3] > q._e[3]))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator >= (const Quat<T> &q) const {
  return (_e[0] > q._e[0]) || ((_e[0] == q._e[0]) && ((_e[1] > q._e[1]) || ((_e[1] == q._e[1]) && ((_e[2] > q._e[2]) || ((_e[2] == q._e[2]) && (_e[3] >= q._e[3]))))));
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Quat<T>::operator [] (int index) const {
  return _e[index];
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::operator T*() {
  return _e;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::operator const T*() const {
  return _e;
}

//------------------------------------------------------------------------------
//
template< class T >
inline T* Quat<T>::ptr() {
  return _e;
}

//------------------------------------------------------------------------------
//
template< class T >
inline const T* Quat<T>::ptr() const {
  return _e;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator + (const Quat<T> &q) const {
  return Quat( _e[0]+q._e[0],_e[1]+q._e[1], _e[2]+q._e[2], _e[3]+q._e[3]);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator - (const Quat<T> &q) const {
  return Quat(_e[0]-q._e[0], _e[1]-q._e[1], _e[2]-q._e[2], _e[3]-q._e[3]);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator * (const Quat<T> &q) const {
  return Quat(
              _e[0]*q._e[0] - _e[1]*q._e[1] - _e[2]*q._e[2] - _e[3]*q._e[3],
              _e[0]*q._e[1] + _e[1]*q._e[0] + _e[2]*q._e[3] - _e[3]*q._e[2],
              _e[0]*q._e[2] + _e[2]*q._e[0] + _e[3]*q._e[1] - _e[1]*q._e[3],
              _e[0]*q._e[3] + _e[3]*q._e[0] + _e[1]*q._e[2] - _e[2]*q._e[1]
              );
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator * (const T &q) const {
  return Quat(_e[0]*q, _e[1]*q, _e[2]*q, _e[3]*q);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator / (const T &q) const {
  return Quat(_e[0]/q, _e[1]/q, _e[2]/q, _e[3]/q);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator += (const Quat<T> &q) {
  _e[0] += q._e[0]; 
  _e[1] += q._e[1]; 
  _e[2] += q._e[2]; 
  _e[3] += q._e[3];
  
  return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator -= (const Quat<T> &q) {
  _e[0] -= q._e[0]; 
  _e[1] -= q._e[1]; 
  _e[2] -= q._e[2]; 
  _e[3] -= q._e[3];
  
  return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator *= (const T &q) {
  *this = *this * q;

  return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator /= (const T &q) {
  _e[0] /= q; 
  _e[1] /= q; 
  _e[2] /= q; 
  _e[3] /= q;
  
  return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator - () {
  _e[0] = -_e[0];
  _e[1] = -_e[1]; 
  _e[2] = -_e[2]; 
  _e[3] = -_e[3]; 
  
  return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
float Quat<T>::length() const {
  return sqrt(sqrLength());
}

//------------------------------------------------------------------------------
//
template<class T>
float Quat<T>::sqrLength() const {
  return _e[0]*_e[0]+_e[1]*_e[1]+_e[2]*_e[2]+_e[3]*_e[3];
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::scale(float l) {
  float s = l/length();
  _e[0] *= s;	
  _e[1] *= s; 
  _e[2] *= s; 
  _e[3] *= s;
  return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::normalize() {
  return scale(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::conjugate() const {
  return Quat(_e[0], -_e[1], -_e[2], -_e[3]);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::unitInverse() const {
  return conjugate();
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::inverse() const {
  return conjugate()/sqrLength();
}

//------------------------------------------------------------------------------
//
template<class T>
Mat4<T> Quat<T>::toMat4() const {
  float xx = _e[1]*_e[1];
  float xy = _e[1]*_e[2];
  float xz = _e[1]*_e[3];
  float xw = _e[1]*_e[0];
  float yy = _e[2]*_e[2];
  float yz = _e[2]*_e[3];
  float yw = _e[2]*_e[0];
  float zz = _e[3]*_e[3];
  float zw = _e[3]*_e[0];


  return Mat4<T>(1-2*(yy+zz), 2*(xy+zw)  , 2*(xz-yw)  , 0,
                 2*(xy-zw)  , 1-2*(xx+zz), 2*(yz+xw)  , 0,
                 2*(xz+yw)  , 2*(yz-xw)  , 1-2*(xx+yy), 0,
                 0          , 0          , 0          , 1);
}

//------------------------------------------------------------------------------
//
template<class T>
Mat3<T> Quat<T>::toMat3() const {
  float xx = _e[1]*_e[1];
  float xy = _e[1]*_e[2];
  float xz = _e[1]*_e[3];
  float xw = _e[1]*_e[0];
  float yy = _e[2]*_e[2];
  float yz = _e[2]*_e[3];
  float yw = _e[2]*_e[0];
  float zz = _e[3]*_e[3];
  float zw = _e[3]*_e[0];

  return Mat3<T>(1-2*(yy+zz), 2*(xy+zw)  , 2*(xz-yw),
                 2*(xy-zw)  , 1-2*(xx+zz), 2*(yz+xw),
                 2*(xz+yw)  , 2*(yz-xw)  , 1-2*(xx+yy));
}

//------------------------------------------------------------------------------
//
template< class T >
inline Vec3<T> Quat<T>::axis() const {
  return Vec3<T>(_e[1],_e[2],_e[3]);
}

//------------------------------------------------------------------------------
//
template< class T >
inline T Quat<T>::angle() const {
  return _e[0];
}

typedef Quat< float >   Quatf;
typedef Quat< double >  Quatd;
typedef Quat< int >     Quati;

#endif // QUAT_H
