#ifndef MAT4_H
#define MAT4_H

#include "mat3.h"
#include "vec4.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/*==============================================================================
  CLASS Mat4
  ==============================================================================*/

//! 4D Matrix class.
//!
//!  The matrix is define in column major but the constructor
//!  and the accessor use a row major definition.
//!
//!   internal: ( 0 4  8 12 )  external: (  0  1  2  3 )
//!             ( 1 5  9 13 )            (  4  5  6  7 )
//!             ( 2 6 10 14 )            (  8  9 10 11 )
//!             ( 3 7 11 15 )            ( 12 13 14 15 )
//!

template< class T >
class Mat4
{

 public:

  /*----- static methods -----*/

  static Mat4 identity();
  static Mat4 rotationX( const T& angle ); // pitch
  static Mat4 rotationY( const T& angle ); // heading
  static Mat4 rotationZ( const T& angle ); // roll
  static Mat4 rotationX( const T& cos, const T& sin );
  static Mat4 rotationY( const T& cos, const T& sin );
  static Mat4 rotationZ( const T& cos, const T& sin );
  static Mat4 shearY( const T& tanyx, const T& tanyz );
  static Mat4 scale( T const & sx, T const & sy , T const & sz );

  /*----- methods -----*/

  template< class S > Mat4( const Mat4<S>& m )
    {
      _e[0]  = m(0);
      _e[1]  = m(1);
      _e[2]  = m(2);
      _e[3]  = m(3);
      _e[4]  = m(4);
      _e[5]  = m(5);
      _e[6]  = m(6);
      _e[7]  = m(7);
      _e[8]  = m(8);
      _e[9]  = m(9);
      _e[10] = m(10);
      _e[11] = m(11);
      _e[12] = m(12);
      _e[13] = m(13);
      _e[14] = m(14);
      _e[15] = m(15);
    }

  Mat4(){
    memset( _e, 0, 16 * sizeof(T) );
  }
  Mat4( const Mat4<T>& m );
  Mat4( const T& e00, const T& e01, const T& e02, const T& e03,
        const T& e10, const T& e11, const T& e12, const T& e13,
        const T& e20, const T& e21, const T& e22, const T& e23,
        const T& e30, const T& e31, const T& e32, const T& e33
        );
  Mat4( const Mat3<T>& m );
  Mat4( const T& m );
  ~Mat4(){}

  T* ptr();
  const T* ptr() const;

  Mat4  inverse() const;
  Mat4& inverseEq();
  Mat4& translateEq( const Vec3<T>& vec );
  Mat4& translateBeforeEq( const Vec3<T>& vec );
  Mat4  transpose() const;

  Mat4 operator+( const Mat4<T>& m ) const;
  Mat4 operator-( const Mat4<T>& m ) const;
  Mat4 operator*( const T& val ) const;
  Mat4 operator*( const Mat4<T>& m ) const;
  Mat4 operator/( const T& val ) const;

  Vec4<T> operator*( const Vec4<T>& vec ) const;
  Vec3<T> operator*( const Vec3<T>& vec ) const;
  Vec3<T> operator^( const Vec3<T>& vec ) const;
  Vec3<T> operator|( const Vec3<T>& vec ) const;

  Mat4& operator+=( const Mat4<T>& m );
  Mat4& operator-=( const Mat4<T>& m );
  Mat4& operator*=( const T& val );
  Mat4& operator*=( const Mat4<T>& m );
  Mat4& operator/=( const T& val );
  Mat4& operator=( const Mat4<T>& m );

  T& operator[]( int pos );
  const T& operator[]( int pos ) const;

  T& operator()( int pos );
  const T& operator()( int pos ) const;
  T& operator()( int line, int col );
  const T& operator()( int line, int col ) const;

 private:

  /*----- data members -----*/

  T _e[16];
};

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::identity()
{
  return Mat4<T>(
                 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::rotationX( const T& angle )
{
  return rotationX( cos( angle ), sin( angle ) );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::rotationY( const T& angle )
{
  return rotationY( cos( angle ), sin( angle ) );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::rotationZ( const T& angle )
{
  return rotationZ( cos( angle ), sin( angle ) );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::rotationX( const T& cos, const T& sin )
{
  return Mat4<T>(
                 1,   0,    0, 0,
                 0, cos, -sin, 0,
                 0, sin,  cos, 0,
                 0,   0,    0, 1
                 );
}


//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::rotationY( const T& cos, const T& sin )
{
  return Mat4<T>(
                 cos, 0, sin, 0,
                 0, 1,   0, 0,
                 -sin, 0, cos, 0,
                 0, 0,   0, 1
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::rotationZ( const T& cos, const T& sin )
{
  return Mat4<T>(
                 cos, -sin, 0, 0,
                 sin,  cos, 0, 0,
                 0,    0, 1, 0,
                 0,    0, 0, 1
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::shearY( const T& tanyx, const T& tanyz )
{
  return Mat4<T>(
                 1,  0,     0, 0,
                 tanyx,  1, tanyz, 0,
                 0,  0,     1, 0,
                 0,  0,     0, 1
                 );
}

template< class T >
inline Mat4<T> Mat4<T>::scale( T const & sx, T const & sy , T const & sz )
{
  return Mat4<T>(
                 sx,  0, 0, 0,
                 0,  sy, 0, 0,
                 0,  0, sz, 0,
                 0,  0, 0, 1
                 );

}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>::Mat4( const Mat4<T>& m )
{
  *this = m;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>::Mat4(
                     const T& e00, const T& e01, const T& e02, const T& e03,
                     const T& e10, const T& e11, const T& e12, const T& e13,
                     const T& e20, const T& e21, const T& e22, const T& e23,
                     const T& e30, const T& e31, const T& e32, const T& e33
                     )
{
  _e[0] = e00;
  _e[1] = e10;
  _e[2] = e20;
  _e[3] = e30;

  _e[4] = e01;
  _e[5] = e11;
  _e[6] = e21;
  _e[7] = e31;

  _e[8] = e02;
  _e[9] = e12;
  _e[10]= e22;
  _e[11]= e32;

  _e[12]= e03;
  _e[13]= e13;
  _e[14]= e23;
  _e[15]= e33;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>::Mat4( const Mat3<T>& m )
{
  _e[0]  = m(0,0);
  _e[1]  = m(1,0);
  _e[2]  = m(2,0);
  _e[3]  = 0;

  _e[4]  = m(0,1);
  _e[5]  = m(1,1);
  _e[6]  = m(2,1);
  _e[7]  = 0;

  _e[8]  = m(0,2);
  _e[9]  = m(1,2);
  _e[10] = m(2,2);
  _e[11] = 0;

  _e[12] = 0;
  _e[13] = 0;
  _e[14] = 0;
  _e[15] = 1;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>::Mat4( const T& m )
{
  memcpy( _e, m, 16 * sizeof(T) );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline T* Mat4<T>::ptr()
{
  return _e;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline const T* Mat4<T>::ptr() const
{
  return _e;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::inverse() const
{
  // Cramer's rule.
  Mat4<T> m;

  T t0  = _e[10]*_e[15] - _e[11]*_e[14];
  T t1  = _e[9]*_e[15]  - _e[11]*_e[13];
  T t2  = _e[9]*_e[14]  - _e[10]*_e[13];
  T t3  = _e[8]*_e[15]  - _e[11]*_e[12];
  T t4  = _e[8]*_e[14]  - _e[10]*_e[12];
  T t5  = _e[8]*_e[13]  - _e[9]*_e[12];
  T t6  = _e[2]*_e[7]   - _e[3]*_e[6];
  T t7  = _e[1]*_e[7]   - _e[3]*_e[5];
  T t8  = _e[1]*_e[6]   - _e[2]*_e[5];
  T t9  = _e[0]*_e[7]   - _e[3]*_e[4];
  T t10 = _e[0]*_e[6]   - _e[2]*_e[4];
  T t11 = _e[0]*_e[5]   - _e[1]*_e[4];

  T det = t0*t11 - t1*t10 + t2*t9 + t3*t8 - t4*t7 + t5*t6;

  if( fabs( det ) < 1e-12 ) return Mat4<T>();

  T idet = 1.0/det;

  m._e[0]  =  _e[5]*t0  - _e[6]*t1   + _e[7]*t2;
  m._e[4]  = -_e[4]*t0  + _e[6]*t3   - _e[7]*t4;
  m._e[8]  =  _e[4]*t1  - _e[5]*t3   + _e[7]*t5;
  m._e[12] = -_e[4]*t2  + _e[5]*t4   - _e[6]*t5;

  m._e[1]  = -_e[1]*t0  + _e[2]*t1   - _e[3]*t2;
  m._e[5]  =  _e[0]*t0  - _e[2]*t3   + _e[3]*t4;
  m._e[9]  = -_e[0]*t1  + _e[1]*t3   - _e[3]*t5;
  m._e[13] =  _e[0]*t2  - _e[1]*t4   + _e[2]*t5;

  m._e[2]  =  _e[13]*t6 - _e[14]*t7  + _e[15]*t8;
  m._e[6]  = -_e[12]*t6 + _e[14]*t9  - _e[15]*t10;
  m._e[10] =  _e[12]*t7 - _e[13]*t9  + _e[15]*t11;
  m._e[14] = -_e[12]*t8 + _e[13]*t10 - _e[14]*t11;

  m._e[3]  = -_e[9]*t6  + _e[10]*t7  - _e[11]*t8;
  m._e[7]  =  _e[8]*t6  - _e[10]*t9  + _e[11]*t10;
  m._e[11] = -_e[8]*t7  + _e[9]*t9   - _e[11]*t11;
  m._e[15] =  _e[8]*t8  - _e[9]*t10  + _e[10]*t11;

  for ( int i = 0; i < 16; ++i )
    {
      m._e[i] *= idet;
    }

  return m;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>& Mat4<T>::inverseEq()
{
  // Cramer's rule.
  T t0  = _e[10]*_e[15] - _e[11]*_e[14];
  T t1  = _e[9]*_e[15]  - _e[11]*_e[13];
  T t2  = _e[9]*_e[14]  - _e[10]*_e[13];
  T t3  = _e[8]*_e[15]  - _e[11]*_e[12];
  T t4  = _e[8]*_e[14]  - _e[10]*_e[12];
  T t5  = _e[8]*_e[13]  - _e[9]*_e[12];
  T t6  = _e[2]*_e[7]   - _e[3]*_e[6];
  T t7  = _e[1]*_e[7]   - _e[3]*_e[5];
  T t8  = _e[1]*_e[6]   - _e[2]*_e[5];
  T t9  = _e[0]*_e[7]   - _e[3]*_e[4];
  T t10 = _e[0]*_e[6]   - _e[2]*_e[4];
  T t11 = _e[0]*_e[5]   - _e[1]*_e[4];

  T det = t0*t11 - t1*t10 + t2*t9 + t3*t8 - t4*t7 + t5*t6;

  if( fabs( det ) < 1e-12 ) return *this;

  T idet = 1.0/det;

  T e0 = _e[0];
  T e8 = _e[8];
  T e9 = _e[9];
  T e10 = _e[10];
  T e12 = _e[12];
  T e13 = _e[13];

  _e[0]  =  _e[5]*t0  - _e[6]*t1   + _e[7]*t2;
  _e[8]  =  _e[4]*t1  - _e[5]*t3   + _e[7]*t5;
  _e[12] = -_e[4]*t2  + _e[5]*t4   - _e[6]*t5;
  _e[4]  = -_e[4]*t0  + _e[6]*t3   - _e[7]*t4;

  _e[5]  =  e0*t0     - _e[2]*t3   + _e[3]*t4;
  _e[9]  = -e0*t1     + _e[1]*t3   - _e[3]*t5;
  _e[13] =  e0*t2     - _e[1]*t4   + _e[2]*t5;
  _e[1]  = -_e[1]*t0  + _e[2]*t1   - _e[3]*t2;

  _e[2]  =  e13*t6    - _e[14]*t7  + _e[15]*t8;
  _e[6]  = -e12*t6    + _e[14]*t9  - _e[15]*t10;
  _e[10] =  e12*t7    - e13*t9     + _e[15]*t11;
  _e[14] = -e12*t8    + e13*t10    - _e[14]*t11;

  _e[3]  = -e9*t6     + e10*t7     - _e[11]*t8;
  _e[7]  =  e8*t6     - e10*t9     + _e[11]*t10;
  _e[11] = -e8*t7     + e9*t9      - _e[11]*t11;
  _e[15] =  e8*t8     - e9*t10     + e10*t11;

  for ( int i = 0; i < 16; ++i )
    {
      _e[i] *= idet;
    }

  return *this;
}

//------------------------------------------------------------------------------
//! Apply  (T) * (this)
//! This operation suppose that the last row of the matrix
//! is ( 0 0 0 1 )
template< class T >
inline Mat4<T>& Mat4<T>::translateEq( const Vec3<T>& vec )
{
  _e[12] += vec(0);
  _e[13] += vec(1);
  _e[14] += vec(2);
  return *this;
}


//------------------------------------------------------------------------------
//! Apply (this) * T
//! This operation suppose that the last row of the matrix
//! is ( 0 0 0 1 )
template< class T >
inline Mat4<T>& Mat4<T>::translateBeforeEq( const Vec3<T>& vec )
{
  _e[12] += _e[0] * vec(0) + _e[4] * vec(1) + _e[8]  * vec(2);
  _e[13] += _e[1] * vec(0) + _e[5] * vec(1) + _e[9]  * vec(2);
  _e[14] += _e[2] * vec(0) + _e[6] * vec(1) + _e[10] * vec(2);
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::transpose() const
{
  return Mat4<T>(
                 _e[0],  _e[1],  _e[2],  _e[3],
                 _e[4],  _e[5],  _e[6],  _e[7],
                 _e[8],  _e[9],  _e[10], _e[11],
                 _e[12], _e[13], _e[14], _e[15]
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::operator+( const Mat4<T>& m ) const
{
  return Mat4<T>(
                 _e[0]  + m._e[0],
                 _e[4]  + m._e[4],
                 _e[8]  + m._e[8],
                 _e[12] + m._e[12],

                 _e[1]  + m._e[1],
                 _e[5]  + m._e[5],
                 _e[9]  + m._e[9],
                 _e[13] + m._e[13],

                 _e[2]  + m._e[2],
                 _e[6]  + m._e[6],
                 _e[10] + m._e[10],
                 _e[14] + m._e[14],

                 _e[3]  + m._e[3],
                 _e[7]  + m._e[7],
                 _e[11] + m._e[11],
                 _e[15] + m._e[15]
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::operator-( const Mat4<T>& m ) const
{
  return Mat4<T>(
                 _e[0]  - m._e[0],
                 _e[4]  - m._e[4],
                 _e[8]  - m._e[8],
                 _e[12] - m._e[12],

                 _e[1]  - m._e[1],
                 _e[5]  - m._e[5],
                 _e[9]  - m._e[9],
                 _e[13] - m._e[13],

                 _e[2]  - m._e[2],
                 _e[6]  - m._e[6],
                 _e[10] - m._e[10],
                 _e[14] - m._e[14],

                 _e[3]  - m._e[3],
                 _e[7]  - m._e[7],
                 _e[11] - m._e[11],
                 _e[15] - m._e[15]
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::operator*( const T& val ) const
{
  return Mat4<T>(
                 _e[0]  * val,
                 _e[4]  * val,
                 _e[8]  * val,
                 _e[12] * val,

                 _e[1]  * val,
                 _e[5]  * val,
                 _e[9]  * val,
                 _e[13] * val,

                 _e[2]  * val,
                 _e[6]  * val,
                 _e[10] * val,
                 _e[14] * val,

                 _e[3]  * val,
                 _e[7]  * val,
                 _e[11] * val,
                 _e[15] * val
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::operator*( const Mat4<T>& m ) const
{
  return Mat4<T>(
                 _e[0]*m._e[0] + _e[4]*m._e[1] + _e[8]*m._e[2]  + _e[12]*m._e[3],
                 _e[0]*m._e[4] + _e[4]*m._e[5] + _e[8]*m._e[6]  + _e[12]*m._e[7],
                 _e[0]*m._e[8] + _e[4]*m._e[9] + _e[8]*m._e[10] + _e[12]*m._e[11],
                 _e[0]*m._e[12]+ _e[4]*m._e[13]+ _e[8]*m._e[14] + _e[12]*m._e[15],

                 _e[1]*m._e[0] + _e[5]*m._e[1] + _e[9]*m._e[2]  + _e[13]*m._e[3],
                 _e[1]*m._e[4] + _e[5]*m._e[5] + _e[9]*m._e[6]  + _e[13]*m._e[7],
                 _e[1]*m._e[8] + _e[5]*m._e[9] + _e[9]*m._e[10] + _e[13]*m._e[11],
                 _e[1]*m._e[12]+ _e[5]*m._e[13]+ _e[9]*m._e[14] + _e[13]*m._e[15],

                 _e[2]*m._e[0] + _e[6]*m._e[1] + _e[10]*m._e[2] + _e[14]*m._e[3],
                 _e[2]*m._e[4] + _e[6]*m._e[5] + _e[10]*m._e[6] + _e[14]*m._e[7],
                 _e[2]*m._e[8] + _e[6]*m._e[9] + _e[10]*m._e[10]+ _e[14]*m._e[11],
                 _e[2]*m._e[12]+ _e[6]*m._e[13]+ _e[10]*m._e[14]+ _e[14]*m._e[15],

                 _e[3]*m._e[0] + _e[7]*m._e[1] + _e[11]*m._e[2] + _e[15]*m._e[3],
                 _e[3]*m._e[4] + _e[7]*m._e[5] + _e[11]*m._e[6] + _e[15]*m._e[7],
                 _e[3]*m._e[8] + _e[7]*m._e[9] + _e[11]*m._e[10]+ _e[15]*m._e[11],
                 _e[3]*m._e[12]+ _e[7]*m._e[13]+ _e[11]*m._e[14]+ _e[15]*m._e[15]
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> Mat4<T>::operator/( const T& val ) const
{
  T ival = (T)1 / val;
  return Mat4<T>(
                 _e[0]  * ival,
                 _e[4]  * ival,
                 _e[8]  * ival,
                 _e[12] * ival,

                 _e[1]  * ival,
                 _e[5]  * ival,
                 _e[9]  * ival,
                 _e[13] * ival,

                 _e[2]  * ival,
                 _e[6]  * ival,
                 _e[10] * ival,
                 _e[14] * ival,

                 _e[3]  * ival,
                 _e[7]  * ival,
                 _e[11] * ival,
                 _e[15] * ival
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Vec4<T> Mat4<T>::operator*( const Vec4<T>& vec ) const
{
  return Vec4<T>(
                 _e[0]*vec(0) + _e[4]*vec(1) + _e[8]*vec(2) + _e[12]*vec(3),
                 _e[1]*vec(0) + _e[5]*vec(1) + _e[9]*vec(2) + _e[13]*vec(3),
                 _e[2]*vec(0) + _e[6]*vec(1) + _e[10]*vec(2)+ _e[14]*vec(3),
                 _e[3]*vec(0) + _e[7]*vec(1) + _e[11]*vec(2)+ _e[15]*vec(3)
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Vec3<T> Mat4<T>::operator*( const Vec3<T>& vec ) const
{
  return Vec3<T>(
                 _e[0]*vec(0) + _e[4]*vec(1) + _e[8]*vec(2) + _e[12],
                 _e[1]*vec(0) + _e[5]*vec(1) + _e[9]*vec(2) + _e[13],
                 _e[2]*vec(0) + _e[6]*vec(1) + _e[10]*vec(2)+ _e[14]
                 );
}


//------------------------------------------------------------------------------
//!
template< class T >
inline Vec3<T> Mat4<T>::operator^( const Vec3<T>& vec ) const
{
  return Vec3<T>(
                 _e[0]*vec(0) + _e[4]*vec(1) + _e[8]*vec(2),
                 _e[1]*vec(0) + _e[5]*vec(1) + _e[9]*vec(2),
                 _e[2]*vec(0) + _e[6]*vec(1) + _e[10]*vec(2)
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Vec3<T> Mat4<T>::operator|( const Vec3<T>& vec ) const
{
  float div = (T)(1) /
    ( _e[3]*vec(0) + _e[7]*vec(1) + _e[11]*vec(2)+ _e[15] );

  return Vec3<T>(
                 div * ( _e[0]*vec(0) + _e[4]*vec(1) + _e[8]*vec(2) + _e[12] ),
                 div * ( _e[1]*vec(0) + _e[5]*vec(1) + _e[9]*vec(2) + _e[13] ),
                 div * ( _e[2]*vec(0) + _e[6]*vec(1) + _e[10]*vec(2)+ _e[14] )
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>& Mat4<T>::operator+=( const Mat4<T>& m )
{
  _e[0] += m._e[0];
  _e[1] += m._e[1];
  _e[2] += m._e[2];
  _e[3] += m._e[3];

  _e[4] += m._e[4];
  _e[5] += m._e[5];
  _e[6] += m._e[6];
  _e[7] += m._e[7];

  _e[8] += m._e[8];
  _e[9] += m._e[9];
  _e[10]+= m._e[10];
  _e[11]+= m._e[11];

  _e[12]+= m._e[12];
  _e[13]+= m._e[13];
  _e[14]+= m._e[14];
  _e[15]+= m._e[15];
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>& Mat4<T>::operator-=( const Mat4<T>& m )
{
  _e[0] -= m._e[0];
  _e[1] -= m._e[1];
  _e[2] -= m._e[2];
  _e[3] -= m._e[3];

  _e[4] -= m._e[4];
  _e[5] -= m._e[5];
  _e[6] -= m._e[6];
  _e[7] -= m._e[7];

  _e[8] -= m._e[8];
  _e[9] -= m._e[9];
  _e[10]-= m._e[10];
  _e[11]-= m._e[11];

  _e[12]-= m._e[12];
  _e[13]-= m._e[13];
  _e[14]-= m._e[14];
  _e[15]-= m._e[15];
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>& Mat4<T>::operator*=( const T& val )
{
  _e[0] *= val;
  _e[1] *= val;
  _e[2] *= val;
  _e[3] *= val;

  _e[4] *= val;
  _e[5] *= val;
  _e[6] *= val;
  _e[7] *= val;

  _e[8] *= val;
  _e[9] *= val;
  _e[10]*= val;
  _e[11]*= val;

  _e[12]*= val;
  _e[13]*= val;
  _e[14]*= val;
  _e[15]*= val;
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>& Mat4<T>::operator*=( const Mat4<T>& m )
{
  T e0  = _e[0];
  T e1  = _e[1];
  T e2  = _e[2];
  T e3  = _e[3];
  T e4  = _e[4];
  T e5  = _e[5];
  T e6  = _e[6];
  T e7  = _e[7];
  T e8  = _e[8];
  T e9  = _e[9];
  T e10 = _e[10];
  T e11 = _e[11];

  _e[0] = e0*m._e[0] + e4*m._e[1] + e8*m._e[2]  + _e[12]*m._e[3];
  _e[1] = e1*m._e[0] + e5*m._e[1] + e9*m._e[2]  + _e[13]*m._e[3];
  _e[2] = e2*m._e[0] + e6*m._e[1] + e10*m._e[2] + _e[14]*m._e[3];
  _e[3] = e3*m._e[0] + e7*m._e[1] + e11*m._e[2] + _e[15]*m._e[3];

  _e[4] = e0*m._e[4] + e4*m._e[5] + e8*m._e[6]  + _e[12]*m._e[7];
  _e[5] = e1*m._e[4] + e5*m._e[5] + e9*m._e[6]  + _e[13]*m._e[7];
  _e[6] = e2*m._e[4] + e6*m._e[5] + e10*m._e[6] + _e[14]*m._e[7];
  _e[7] = e3*m._e[4] + e7*m._e[5] + e11*m._e[6] + _e[15]*m._e[7];

  _e[8] = e0*m._e[8] + e4*m._e[9] + e8*m._e[10] + _e[12]*m._e[11];
  _e[9] = e1*m._e[8] + e5*m._e[9] + e9*m._e[10] + _e[13]*m._e[11];
  _e[10]= e2*m._e[8] + e6*m._e[9] + e10*m._e[10]+ _e[14]*m._e[11];
  _e[11]= e3*m._e[8] + e7*m._e[9] + e11*m._e[10]+ _e[15]*m._e[11];

  _e[12]= e0*m._e[12]+ e4*m._e[13]+ e8*m._e[14] + _e[12]*m._e[15];
  _e[13]= e1*m._e[12]+ e5*m._e[13]+ e9*m._e[14] + _e[13]*m._e[15];
  _e[14]= e2*m._e[12]+ e6*m._e[13]+ e10*m._e[14]+ _e[14]*m._e[15];
  _e[15]= e3*m._e[12]+ e7*m._e[13]+ e11*m._e[14]+ _e[15]*m._e[15];

  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>& Mat4<T>::operator/=( const T& val )
{
  T ival = (T)1 / val;
  _e[0]  *= ival;
  _e[1]  *= ival;
  _e[2]  *= ival;
  _e[3]  *= ival;

  _e[4]  *= ival;
  _e[5]  *= ival;
  _e[6]  *= ival;
  _e[7]  *= ival;

  _e[8]  *= ival;
  _e[9]  *= ival;
  _e[10] *= ival;
  _e[11] *= ival;

  _e[12] *= ival;
  _e[13] *= ival;
  _e[14] *= ival;
  _e[15] *= ival;
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T>& Mat4<T>::operator=( const Mat4<T>& m )
{
  _e[0]  = m._e[0];
  _e[1]  = m._e[1];
  _e[2]  = m._e[2];
  _e[3]  = m._e[3];

  _e[4]  = m._e[4];
  _e[5]  = m._e[5];
  _e[6]  = m._e[6];
  _e[7]  = m._e[7];

  _e[8]  = m._e[8];
  _e[9]  = m._e[9];
  _e[10] = m._e[10];
  _e[11] = m._e[11];

  _e[12] = m._e[12];
  _e[13] = m._e[13];
  _e[14] = m._e[14];
  _e[15] = m._e[15];
  return *this;
}

//------------------------------------------------------------------------------
//!
  template< class T >
  inline T& Mat4<T>::operator[]( int pos )
  {
    return _e[pos];
  }

//------------------------------------------------------------------------------
//!
template< class T >
inline const T& Mat4<T>::operator[]( int pos ) const
{
  return _e[pos];
}

//------------------------------------------------------------------------------
//!
template< class T >
inline T& Mat4<T>::operator()( int pos )
{
  return _e[pos];
}

//------------------------------------------------------------------------------
//!
template< class T >
inline const T& Mat4<T>::operator()( int pos ) const
{
  return _e[pos];
}



//------------------------------------------------------------------------------
//!
template< class T >
inline T& Mat4<T>::operator()( int line, int col )
{
  return _e[ line + (col<<2) ];
}

//------------------------------------------------------------------------------
//!
template< class T >
inline const T& Mat4<T>::operator()( int line, int col ) const
{
  return _e[ line + (col<<2) ];
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat4<T> operator*( const T& val, const Mat4<T>& m )
{
  return Mat4<T>(
                 m(0,0) * val,
                 m(0,1) * val,
                 m(0,2) * val,
                 m(0,3) * val,

                 m(1,0) * val,
                 m(1,1) * val,
                 m(1,2) * val,
                 m(1,3) * val,

                 m(2,0) * val,
                 m(2,1) * val,
                 m(2,2) * val,
                 m(2,3) * val,

                 m(3,0) * val,
                 m(3,1) * val,
                 m(3,2) * val,
                 m(3,3) * val
                 );
}

/*==============================================================================
  TYPEDEF
  ==============================================================================*/

typedef Mat4< int >    Mat4i;
typedef Mat4< float >  Mat4f;
typedef Mat4< double > Mat4d;

       

#endif
