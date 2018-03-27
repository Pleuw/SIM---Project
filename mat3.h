#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"
#include <math.h>

/*==============================================================================
  CLASS Mat3
  ==============================================================================*/

//! 3D Matrix class.
//!
//! The matrix is define in column major but the constructor
//! and the accessor use a row major definition.
//!
//! internal: ( 0 3 6 )  external: ( 0 1 2 )
//!           ( 1 4 7 )            ( 3 4 5 )
//!           ( 2 5 8 )            ( 6 7 8 )

template< class T >
class Mat3
{

 public:

  /*----- static methods -----*/

  static Mat3 identity();

  /*----- methods -----*/

  template< class S > Mat3( const Mat3<S>& m )
    {
      _e[0] = m._e[0];
      _e[1] = m._e[1];
      _e[2] = m._e[2];
      _e[3] = m._e[3];
      _e[4] = m._e[4];
      _e[5] = m._e[5];
      _e[6] = m._e[6];
      _e[7] = m._e[7];
      _e[8] = m._e[8];
    }

  Mat3(){}
  Mat3( const Mat3<T>& m );
  Mat3( const T& e00, const T& e01, const T& e02,
        const T& e10, const T& e11, const T& e12,
        const T& e20, const T& e21, const T& e22
        );
  ~Mat3(){}

  T* ptr();
  const T* ptr() const;

  Mat3  inverse() const;
  Mat3& inverseEq();
  Mat3  transpose() const;

  Mat3 operator+( const Mat3<T>& m ) const;
  Mat3 operator-( const Mat3<T>& m ) const;
  Mat3 operator*( const T& val ) const;
  Mat3 operator*( const Mat3<T>& m ) const;
  Mat3 operator/( const T& val ) const;

  Vec3<T> operator*( const Vec3<T>& vec ) const;

  Mat3& operator+=( const Mat3<T>& m );
  Mat3& operator-=( const Mat3<T>& m );
  Mat3& operator*=( const T& val );
  Mat3& operator*=( const Mat3<T>& m );
  Mat3& operator/=( const T& val );
  Mat3& operator=( const Mat3<T>& m );

  T& operator()( int line, int col );
  const T& operator()( int line, int col ) const;

 private:

  /*----- data members -----*/

  T _e[9];
};

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T> Mat3<T>::identity()
{
  return Mat3<T>(
                 1, 0, 0,
                 0, 1, 0,
                 0, 0, 1
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T>::Mat3( const Mat3<T>& m )
{
  *this = m;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T>::Mat3(
                     const T& e00, const T& e01, const T& e02,
                     const T& e10, const T& e11, const T& e12,
                     const T& e20, const T& e21, const T& e22
                     )
{
  _e[0] = e00;
  _e[1] = e10;
  _e[2] = e20;
  _e[3] = e01;
  _e[4] = e11;
  _e[5] = e21;
  _e[6] = e02;
  _e[7] = e12;
  _e[8] = e22;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline T* Mat3<T>::ptr()
{
  return _e;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline const T* Mat3<T>::ptr() const
{
  return _e;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T> Mat3<T>::inverse() const
{
  T det =
    _e[0] * ( _e[4] * _e[8] - _e[7] * _e[5] ) +
    _e[3] * ( _e[7] * _e[2] - _e[1] * _e[8] ) +
    _e[6] * ( _e[1] * _e[5] - _e[4] * _e[2] );

  if( fabs( det ) < 1e-12 ) return Mat3<T>();

  T idet = 1.0/det;

  return Mat3<T>(
                 idet*(  _e[4] * _e[8] - _e[7] * _e[5] ),
                 -idet*( _e[3] * _e[8] - _e[6] * _e[5] ),
                 idet*(  _e[3] * _e[7] - _e[6] * _e[4] ),

                 -idet*( _e[1] * _e[8] - _e[7] * _e[2] ),
                 idet*(  _e[0] * _e[8] - _e[6] * _e[2] ),
                 -idet*( _e[0] * _e[7] - _e[6] * _e[1] ),

                 idet*(  _e[1] * _e[5] - _e[4] * _e[2] ),
                 -idet*( _e[0] * _e[5] - _e[3] * _e[2] ),
                 idet*(  _e[0] * _e[4] - _e[3] * _e[1] )
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T>& Mat3<T>::inverseEq()
{
  T det =
    _e[0] * ( _e[4] * _e[8] - _e[7] * _e[5] ) +
    _e[3] * ( _e[7] * _e[2] - _e[1] * _e[8] ) +
    _e[6] * ( _e[1] * _e[5] - _e[4] * _e[2] );

  if( fabs( det ) < 1e-12 ) return *this;

  T idet = 1.0/det;

  T e0 = _e[0];
  T e1 = _e[1];
  T e2 = _e[2];
  T e3 = _e[3];
  T e4 = _e[4];
  T e5 = _e[5];
  T e6 = _e[6];

  _e[0] = idet*(  e4 * _e[8] - _e[7] * e5 );
  _e[1] = -idet*( e1 * _e[8] - _e[7] * e2 );
  _e[2] = idet*(  e1 * e5    - e4    * e2 );
  _e[3] = -idet*( e3 * _e[8] - e6    * e5 );
  _e[4] = idet*(  e0 * _e[8] - e6    * e2 );
  _e[5] = -idet*( e0 * e5    - e3    * e2 );
  _e[6] = idet*(  e3 * _e[7] - e6    * e4 );
  _e[7] = -idet*( e0 * _e[7] - e6    * e1 );
  _e[8] = idet*(  e0 * e4    - e3    * e1 );

  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T> Mat3<T>::transpose() const
{
  return Mat3<T>(_e[0],_e[1],_e[2],
                 _e[3],_e[4],_e[5],
                 _e[6],_e[7],_e[8]);
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T> Mat3<T>::operator+( const Mat3<T>& m ) const
{
  return Mat3<T>(
                 _e[0] + m._e[0],
                 _e[3] + m._e[3],
                 _e[6] + m._e[6],

                 _e[1] + m._e[1],
                 _e[4] + m._e[4],
                 _e[7] + m._e[7],

                 _e[2] + m._e[2],
                 _e[5] + m._e[5],
                 _e[8] + m._e[8]
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T> Mat3<T>::operator-( const Mat3<T>& m ) const
{
  return Mat3<T>(
                 _e[0] - m._e[0],
                 _e[3] - m._e[3],
                 _e[6] - m._e[6],

                 _e[1] - m._e[1],
                 _e[4] - m._e[4],
                 _e[7] - m._e[7],

                 _e[2] - m._e[2],
                 _e[5] - m._e[5],
                 _e[8] - m._e[8]
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T> Mat3<T>::operator*( const T& val ) const
{
  return Mat3<T>(
                 _e[0] * val,
                 _e[3] * val,
                 _e[6] * val,

                 _e[1] * val,
                 _e[4] * val,
                 _e[7] * val,

                 _e[2] * val,
                 _e[5] * val,
                 _e[8] * val
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T> Mat3<T>::operator*( const Mat3<T>& m ) const
{
  return Mat3<T>(
                 _e[0]*m._e[0] + _e[3]*m._e[1] + _e[6]*m._e[2],
                 _e[0]*m._e[3] + _e[3]*m._e[4] + _e[6]*m._e[5],
                 _e[0]*m._e[6] + _e[3]*m._e[7] + _e[6]*m._e[8],

                 _e[1]*m._e[0] + _e[4]*m._e[1] + _e[7]*m._e[2],
                 _e[1]*m._e[3] + _e[4]*m._e[4] + _e[7]*m._e[5],
                 _e[1]*m._e[6] + _e[4]*m._e[7] + _e[7]*m._e[8],

                 _e[2]*m._e[0] + _e[5]*m._e[1] + _e[8]*m._e[2],
                 _e[2]*m._e[3] + _e[5]*m._e[4] + _e[8]*m._e[5],
                 _e[2]*m._e[6] + _e[5]*m._e[7] + _e[8]*m._e[8]
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T> Mat3<T>::operator/( const T& val ) const
{
  T ival = (T)1 / val;
  return Mat3<T>(
                 _e[0] * ival,
                 _e[3] * ival,
                 _e[6] * ival,

                 _e[1] * ival,
                 _e[4] * ival,
                 _e[7] * ival,

                 _e[2] * ival,
                 _e[5] * ival,
                 _e[8] * ival
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Vec3<T> Mat3<T>::operator*( const Vec3<T>& vec ) const
{
  return Vec3<T>(
                 _e[0]*vec(0) + _e[3]*vec(1) + _e[6]*vec(2),
                 _e[1]*vec(0) + _e[4]*vec(1) + _e[7]*vec(2),
                 _e[2]*vec(0) + _e[5]*vec(1) + _e[8]*vec(2)
                 );
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T>& Mat3<T>::operator+=( const Mat3<T>& m )
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
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T>& Mat3<T>::operator-=( const Mat3<T>& m )
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
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T>& Mat3<T>::operator*=( const T& val )
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
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T>& Mat3<T>::operator*=( const Mat3<T>& m )
{
  T e0 = _e[0];
  T e1 = _e[1];
  T e2 = _e[2];
  T e3 = _e[3];
  T e4 = _e[4];
  T e5 = _e[5];

  _e[0] = e0*m._e[0] + e3*m._e[1] + _e[6]*m._e[2];
  _e[1] = e1*m._e[0] + e4*m._e[1] + _e[7]*m._e[2];
  _e[2] = e2*m._e[0] + e5*m._e[1] + _e[8]*m._e[2];

  _e[3] = e0*m._e[3] + e3*m._e[4] + _e[6]*m._e[5];
  _e[4] = e1*m._e[3] + e4*m._e[4] + _e[7]*m._e[5];
  _e[5] = e2*m._e[3] + e5*m._e[4] + _e[8]*m._e[5];

  _e[6] = e0*m._e[6] + e3*m._e[7] + _e[6]*m._e[8];
  _e[7] = e1*m._e[6] + e4*m._e[7] + _e[7]*m._e[8];
  _e[8] = e2*m._e[6] + e5*m._e[7] + _e[8]*m._e[8];
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T>& Mat3<T>::operator/=( const T& val )
{
  T ival = (T)1 / val;

  _e[0] *= ival;
  _e[1] *= ival;
  _e[2] *= ival;
  _e[3] *= ival;
  _e[4] *= ival;
  _e[5] *= ival;
  _e[6] *= ival;
  _e[7] *= ival;
  _e[8] *= ival;
  return *this;
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T>& Mat3<T>::operator=( const Mat3<T>& m )
{
  _e[0] = m._e[0];
  _e[1] = m._e[1];
  _e[2] = m._e[2];
  _e[3] = m._e[3];
  _e[4] = m._e[4];
  _e[5] = m._e[5];
  _e[6] = m._e[6];
  _e[7] = m._e[7];
  _e[8] = m._e[8];
  return *this;
}

//------------------------------------------------------------------------------
//!
  template< class T >
  inline T& Mat3<T>::operator()( int line, int col )
  {
    return _e[ line + (col*3) ];
  }

//------------------------------------------------------------------------------
//!
template< class T >
inline const T& Mat3<T>::operator()( int line, int col ) const
{
  return _e[ line + (col*3) ];
}

//------------------------------------------------------------------------------
//!
template< class T >
inline Mat3<T> operator*( const T& val, const Mat3<T>& m )
{
  return Mat3<T>(
                 m(0,0) * val,
                 m(0,1) * val,
                 m(0,2) * val,

                 m(1,0) * val,
                 m(1,1) * val,
                 m(1,2) * val,

                 m(2,0) * val,
                 m(2,1) * val,
                 m(2,2) * val
                 );
}

/*==============================================================================
  TYPEDEF
  ==============================================================================*/

typedef Mat3< int >    Mat3i;
typedef Mat3< float >  Mat3f;
typedef Mat3< double > Mat3d;


#endif
