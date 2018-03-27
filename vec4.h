#ifndef VEC4_H
#define VEC4_H

#include <math.h>

        
  /*==============================================================================
    CLASS Vec4
    ==============================================================================*/

  //! 4D vector class.

  template< class T >
    class Vec4
    {

    public:
   
      /*----- methods -----*/

      inline static Vec4 zero();

      /*----- methods -----*/

      template< class S > Vec4( const Vec4<S>& vec )
        {
          _e[0] = (T)vec(0);
          _e[1] = (T)vec(1);
          _e[2] = (T)vec(2);
          _e[3] = (T)vec(3);
        }

      Vec4() { _e[0]=_e[1]=_e[2]=_e[3]=0; }
      Vec4( const Vec4<T>& vec );
      Vec4( const T& e0, const T& e1, const T& e2, const T& e3 );
      Vec4( const T vec[] );

      ~Vec4() {}

      T* ptr();
      const T* ptr() const;

      void set( const T _v1, const T _v2, const T _v3, const T _v4);

            
      T length() const;
      T sqrLength() const;
      T dot( const Vec4<T>& vec ) const;

      Vec4  cross( const Vec4<T>& vec ) const;
      Vec4  normal() const;
      Vec4& normalEq();
      Vec4& normalEq( const T length );
      Vec4& negateEq();
      Vec4& clampToMaxEq( const T& max );
   
      Vec4 operator+( const Vec4<T>& rhs ) const;
      Vec4 operator-( const Vec4<T>& rhs ) const;
      Vec4 operator-() const;
      Vec4 operator*( const T& rhs ) const;
      Vec4 operator*( const Vec4<T>& rhs ) const;
      Vec4 operator/( const T& rhs ) const;
      Vec4 operator/( const Vec4<T>& rhs ) const;

      Vec4& operator+=( const Vec4<T>& rhs );
      Vec4& operator-=( const Vec4<T>& rhs );
      Vec4& operator*=( const T& rhs );
      Vec4& operator*=( const Vec4<T>& rhs );
      Vec4& operator/=( const T& rhs );
      Vec4& operator/=( const Vec4<T>& rhs );
      Vec4& operator=( const Vec4<T>& rsh );

      bool operator==( const Vec4<T>& rhs ) const;
      bool operator!=( const Vec4<T>& rhs ) const;

      T& operator()( int idx );
      const T& operator()( int idx ) const;

      T& operator[]( int idx );
      const T& operator[]( int idx ) const;

    private:

      /*----- data members -----*/

      T _e[4];
    };

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::zero() 
    {
      return Vec4( 0, 0, 0, 0 );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>::Vec4( const Vec4<T>& vec )
    {
      _e[0] = vec._e[0];
      _e[1] = vec._e[1];
      _e[2] = vec._e[2];
      _e[3] = vec._e[3];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>::Vec4(
                         const T& e0,
                         const T& e1,
                         const T& e2,
                         const T& e3
                         )
    {
      _e[0] = e0;
      _e[1] = e1;
      _e[2] = e2;
      _e[3] = e3;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>::Vec4(
                         const T vec[]
                         )
    {
      memcpy( _e, vec, 4 * sizeof(T) ); 
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T* Vec4<T>::ptr()
    {
      return _e;
    }

  //------------------------------------------------------------------------------
  //!        
  template< class T >
    inline void
    Vec4<T>::set( const T _v1, const T _v2, const T _v3, const T _v4)
    {
      _e[0] = _v1;
      _e[1] = _v2;
      _e[2] = _v3;
      _e[3] = _v4;
    }
        

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T* Vec4<T>::ptr() const
    {
      return _e;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T Vec4<T>::length() const
    {
      return (T)sqrt(
                     _e[0]*_e[0] +
                     _e[1]*_e[1] +
                     _e[2]*_e[2] +
                     _e[3]*_e[3]
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T Vec4<T>::sqrLength() const
    {
      return _e[0]*_e[0] + _e[1]*_e[1] + _e[2]*_e[2] + _e[3]*_e[3];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T Vec4<T>::dot( const Vec4<T>& vec ) const
    {
      return _e[0]*vec._e[0] + _e[1]*vec._e[1] + _e[2]*vec._e[2] + _e[3]*vec._e[3];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::cross( const Vec4<T>& vec ) const
    {
      return Vec4<T>(
                     _e[1]*vec._e[2] - _e[2]*vec._e[1],
                     _e[2]*vec._e[0] - _e[0]*vec._e[2],
                     _e[0]*vec._e[1] - _e[1]*vec._e[0],
                     0
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::normal() const
    {
      T tmp = (T)1 / length();
      return Vec4<T>(
                     _e[0] * tmp,
                     _e[1] * tmp,
                     _e[2] * tmp,
                     _e[3] * tmp
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::normalEq() 
    {
      T tmp = (T)1 / length();
      _e[0] *= tmp;
      _e[1] *= tmp;
      _e[2] *= tmp;
      _e[3] *= tmp;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::normalEq( const T length ) 
    {
      T tmp = length / length();
      _e[0] *= tmp;
      _e[1] *= tmp;
      _e[2] *= tmp;
      _e[3] *= tmp;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::negateEq()
    {
      _e[0] = -_e[0];
      _e[1] = -_e[1];
      _e[2] = -_e[2];
      _e[3] = -_e[3];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::clampToMaxEq( const T& max )
    {
      if( _e[0] > max )
        {
          _e[0] = max;
        }
      if( _e[1] > max )
        {
          _e[1] = max;
        }
      if( _e[2] > max )
        {
          _e[2] = max;
        }
      if( _e[3] > max )
        {
          _e[3] = max;
        }
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::operator+( const Vec4<T>& rhs ) const
    {
      return Vec4<T>(
                     _e[0] + rhs._e[0],
                     _e[1] + rhs._e[1],
                     _e[2] + rhs._e[2],
                     _e[3] + rhs._e[3]
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::operator-( const Vec4<T>& rhs ) const
    {
      return Vec4<T>(
                     _e[0] - rhs._e[0],
                     _e[1] - rhs._e[1],
                     _e[2] - rhs._e[2],
                     _e[3] - rhs._e[3]
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::operator-() const
    {
      return Vec4<T>( -_e[0], -_e[1], -_e[2], -_e[3] );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::operator*( const T& rhs ) const
    {
      return Vec4<T>(
                     _e[0] * rhs,
                     _e[1] * rhs,
                     _e[2] * rhs,
                     _e[3] * rhs
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::operator* ( const Vec4<T>& rhs ) const
    {
      return Vec4<T>(
                     _e[0] * rhs._e[0],
                     _e[1] * rhs._e[1],
                     _e[2] * rhs._e[2],
                     _e[3] * rhs._e[3]
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::operator/( const T& rhs ) const
    {
      return Vec4<T>(
                     _e[0] / rhs,
                     _e[1] / rhs,
                     _e[2] / rhs,
                     _e[3] / rhs
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T> Vec4<T>::operator/( const Vec4<T>& rhs ) const
    {
      return Vec4<T>(
                     _e[0] / rhs._e[0],
                     _e[1] / rhs._e[1],
                     _e[2] / rhs._e[2],
                     _e[3] / rhs._e[3]
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::operator+=( const Vec4<T>& rhs )
    {
      _e[0] += rhs._e[0];
      _e[1] += rhs._e[1];
      _e[2] += rhs._e[2];
      _e[3] += rhs._e[3];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::operator-=( const Vec4<T>& rhs )
    {
      _e[0] -= rhs._e[0];
      _e[1] -= rhs._e[1];
      _e[2] -= rhs._e[2];
      _e[3] -= rhs._e[3];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::operator*=( const T& rhs )
    {
      _e[0] *= rhs;
      _e[1] *= rhs;
      _e[2] *= rhs;
      _e[3] *= rhs;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::operator*=( const Vec4<T>& rhs )
    {
      _e[0] *= rhs._e[0];
      _e[1] *= rhs._e[1];
      _e[2] *= rhs._e[2];
      _e[3] *= rhs._e[3];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::operator/=( const T& rhs )
    {
      _e[0] /= rhs;
      _e[1] /= rhs;
      _e[2] /= rhs;
      _e[3] /= rhs;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::operator/=( const Vec4<T>& rhs )
    {
      _e[0] /= rhs._e[0];
      _e[1] /= rhs._e[1];
      _e[2] /= rhs._e[2];
      _e[3] /= rhs._e[3];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec4<T>& Vec4<T>::operator=( const Vec4<T>& rhs )
    {
      _e[0] = rhs._e[0];
      _e[1] = rhs._e[1];
      _e[2] = rhs._e[2];
      _e[3] = rhs._e[3];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline bool Vec4<T>::operator==( const Vec4<T>& rhs ) const
    {
      return
        _e[0] == rhs._e[0] &&
        _e[1] == rhs._e[1] &&
        _e[2] == rhs._e[2] &&
        _e[3] == rhs._e[3];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline bool Vec4<T>::operator!=( const Vec4<T>& rhs ) const
    {
      return
        _e[0] != rhs._e[0] ||
        _e[1] != rhs._e[1] ||
        _e[2] != rhs._e[2] ||
        _e[3] != rhs._e[3];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T& Vec4<T>::operator()( int idx )
    {
      return _e[idx];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T& Vec4<T>::operator()( int idx ) const
    {
      return _e[idx];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T& Vec4<T>::operator[]( int idx )
    {
      return _e[idx];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T& Vec4<T>::operator[]( int idx ) const
    {
      return _e[idx];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T > inline Vec4<T>
    operator*
    ( const T& val, const Vec4<T>& vec )
    {
      return Vec4<T>(
                     vec(0) * val,
                     vec(1) * val,
                     vec(2) * val,
                     vec(3) * val
                     );
    }

  /*==============================================================================
    TYPEDEF
    ==============================================================================*/

  typedef Vec4< int >    Vec4i;
  typedef Vec4< float >  Vec4f;
  typedef Vec4< double > Vec4d;
        

  
              
#endif
