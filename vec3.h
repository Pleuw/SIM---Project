#ifndef VEC3_H
#define VEC3_H


#include <math.h>

        
  /*==============================================================================
    CLASS Vec3
    ==============================================================================*/

  //! 3D vector class.

  template< class T >
    class Vec3
    {

    public: 

   
      /*----- static methods -----*/

      inline static Vec3 zero();
      inline static Vec3 xaxis();
      inline static Vec3 yaxis();
      inline static Vec3 zaxis();

      inline static Vec3 gravity();

      /*----- methods -----*/

      template< class S > Vec3( const Vec3<S>& vec )
        {
          _e[0] = (T)vec(0);
          _e[1] = (T)vec(1);
          _e[2] = (T)vec(2);
        }

      Vec3(){ _e[0]=_e[1]=_e[2]=(T)0; }
      Vec3( const Vec3<T>& vec );
      Vec3( const Vec3<T>& _v1, const Vec3<T>& _v2 );
      Vec3( const T e0, const T e1, const T e2 );
      Vec3( const T vec[] ); 

      ~Vec3(){}

      bool hasNan() const;
      bool hasInf() const;

      T* ptr();
      const T* ptr() const;

      T* getArray();
      const T* getArray() const;

      void setValues(const T _v1, const T _v2, const T _v3);
      void set( const T _v1, const T _v2, const T _v3);

      T length() const;
      T sqrLength() const;
      T norm() const; //an alias for length
           
      T dot( const Vec3<T>& vec ) const;

      Vec3  cross( const Vec3<T>& vec ) const;
      Vec3  normal() const;
      Vec3& normalEq();
      Vec3& normalEq( const T length );
      Vec3& negateEq();
      Vec3& clampToMaxEq( const T& max );
      Vec3  generateOrthogonal() const;

      Vec3 operator^( const Vec3<T>& _v ) const;
   
      Vec3 operator+( const Vec3<T>& rhs ) const;
      Vec3 operator+( const T& _v ) const;
      Vec3 operator-( const Vec3<T>& rhs ) const;
      Vec3 operator-( const T& _v ) const;
      Vec3 operator-() const;
      Vec3 operator*( const T& rhs ) const;
      Vec3 operator*( const Vec3<T>& rhs ) const;
      Vec3 operator/( const T& rhs ) const;
      Vec3 operator/( const Vec3<T>& rhs ) const;

      Vec3& operator+=( const Vec3<T>& rhs );
      Vec3& operator+=( const T& _v );
      Vec3& operator-=( const Vec3<T>& rhs );
      Vec3& operator-=( const T& _v );
      Vec3& operator*=( const T& rhs );
      Vec3& operator*=( const Vec3<T>& rhs );
      Vec3& operator/=( const T& rhs );
      Vec3& operator/=( const Vec3<T>& rhs );
      Vec3& operator=( const Vec3<T>& rsh );

      bool operator==( const Vec3<T>& rhs ) const;
      bool operator!=( const Vec3<T>& rhs ) const;

      bool operator> ( const Vec3<T>& _v ) const;
      bool operator>= ( const Vec3<T>& _v ) const;
      bool operator< ( const Vec3<T>& _v ) const;
      bool operator<= ( const Vec3<T>& _v ) const;
   
      T& operator()( int idx );
      const T& operator()( int idx ) const;

      T& operator[]( int idx );
      const T& operator[]( int idx ) const;

      void setX(const T&);
      void setY(const T&);
      void setZ(const T&);
   
      T x();
      T y();
      T z();
 
      const T& x() const;
      const T& y() const;
      const T& z() const;

    private: 

      /*----- data members -----*/

      T _e[3];
    };

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::zero() 
    {
      return Vec3( 0, 0, 0 );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::xaxis() 
    {
      return Vec3( 1, 0, 0 );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::yaxis() 
    {
      return Vec3( 0, 1, 0 );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::zaxis() 
    {
      return Vec3( 0, 0, 1 );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::gravity() 
    {
      return Vec3( 0, 0, -9.8 );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>::Vec3( const Vec3<T>& vec )
    {
      _e[0] = vec._e[0];
      _e[1] = vec._e[1];
      _e[2] = vec._e[2];
    }
 
  //------------------------------------------------------------------------------
  //!
  template< class T >
  inline bool Vec3<T>::hasNan() const  
  {
    return (isnan(_e[0]) || isnan(_e[1]) || isnan(_e[2]));
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
  inline bool Vec3<T>::hasInf() const 
  {
    return (isinf(_e[0]) || isinf(_e[1]) || isinf(_e[2]));
  }


  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>::Vec3( const Vec3<T>& _v1, const Vec3<T>& _v2 ) {
    _e[0] = _v2._e[0] - _v1._e[0];
    _e[1] = _v2._e[1] - _v1._e[1];
    _e[2] = _v2._e[2] - _v1._e[2];
  }


  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>::Vec3( const T e0, const T e1, const T e2 )
    {
      _e[0] = e0;
      _e[1] = e1;
      _e[2] = e2;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>::Vec3(
                         const T vec[]
                         )
    {
      memcpy( _e, vec, 3 * sizeof(T) ); 
    }



  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T* Vec3<T>::ptr()
    {
      return _e;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T* Vec3<T>::ptr() const
    {
      return _e;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T* Vec3<T>::getArray()
    {
      return _e;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T* Vec3<T>::getArray() const
    {
      return _e;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline void Vec3<T>::setValues(const T _v1, const T _v2, const T _v3) {
    _e[0] = _v1; _e[1] = _v2; _e[2] = _v3;
  }

  template< class T >
    inline void Vec3<T>::set( const T _v1, const T _v2, const T _v3)
    {
      setValues( _v1, _v2, _v3);
    }
       
       
  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T Vec3<T>::length() const
    {
      return (T)sqrt( _e[0]*_e[0] + _e[1]*_e[1] + _e[2]*_e[2] );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T Vec3<T>::sqrLength() const
    {
      return _e[0]*_e[0] + _e[1]*_e[1] + _e[2]*_e[2];
    }

  template< class T >
    inline T
    Vec3<T>::norm() const
    {
      return length();
    }
       

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T Vec3<T>::dot
    ( const Vec3<T>& vec ) const
    {
      return _e[0]*vec._e[0] + _e[1]*vec._e[1] + _e[2]*vec._e[2];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::cross( const Vec3<T>& vec ) const
    {
      return Vec3<T>(
                     _e[1]*vec._e[2] - _e[2]*vec._e[1],
                     _e[2]*vec._e[0] - _e[0]*vec._e[2],
                     _e[0]*vec._e[1] - _e[1]*vec._e[0]
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::normal() const
    {
      const T tmp = (T)1 / length();
      return Vec3<T>( _e[0] * tmp, _e[1] * tmp, _e[2] * tmp );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::normalEq() 
    {
      const T tmp = (T)1 / this->length();
      _e[0] *= tmp;
      _e[1] *= tmp;
      _e[2] *= tmp;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::normalEq( const T length ) 
    {
      const T tmp = length / this->length();
      _e[0] *= tmp;
      _e[1] *= tmp;
      _e[2] *= tmp;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::negateEq()
    {
      _e[0] = -_e[0];
      _e[1] = -_e[1];
      _e[2] = -_e[2];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::clampToMaxEq( const T& max )
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
      return *this;
    }

  template< class T >
    inline Vec3<T>  Vec3<T>::generateOrthogonal() const
    {
      T const ax = fabs(_e[0]);
      T const ay = fabs(_e[1]);
      T const az = fabs(_e[2]);
      if ( (ax < ay) && (ax < az) )
        {
          return Vec3<T>(T(0),_e[2],-_e[1]);
        }
      else if (ay < az)
        {
          return Vec3<T>(_e[2],T(0),-_e[0]);
        }
      else
        {
          return Vec3<T>(-_e[1],_e[0],T(0));
        }

    }


  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator^( const Vec3<T>& _v ) const {
    return this->cross(_v);
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator+( const Vec3<T>& rhs ) const
    {
      return Vec3<T>(
                     _e[0] + rhs._e[0],
                     _e[1] + rhs._e[1],
                     _e[2] + rhs._e[2]
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator+( const T& _v ) const
    {
      return Vec3<T>(
                     _e[0] + _v,
                     _e[1] + _v,
                     _e[2] + _v
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator-( const Vec3<T>& rhs ) const
    {
      return Vec3<T>(
                     _e[0] - rhs._e[0],
                     _e[1] - rhs._e[1],
                     _e[2] - rhs._e[2]
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator-( const T& _v ) const
    {
      return Vec3<T>(
                     _e[0] - _v,
                     _e[1] - _v,
                     _e[2] - _v
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator-() const
    {
      return Vec3<T>( -_e[0], -_e[1], -_e[2] );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator*( const T& rhs ) const
    {
      return Vec3<T>( _e[0] * rhs, _e[1] * rhs, _e[2] * rhs );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator*( const Vec3<T>& rhs ) const
    {
      return Vec3<T>(
                     _e[0] * rhs._e[0],
                     _e[1] * rhs._e[1],
                     _e[2] * rhs._e[2]
                     );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator/( const T& rhs ) const
    {
      return Vec3<T>( _e[0] / rhs, _e[1] / rhs, _e[2] / rhs );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> Vec3<T>::operator/( const Vec3<T>& rhs ) const
    {
      return Vec3<T>( _e[0] / rhs._e[0], _e[1] / rhs._e[1], _e[2] / rhs._e[2] );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>&Vec3<T>::operator+=( const Vec3<T>& rhs )
    {
      _e[0] += rhs._e[0];
      _e[1] += rhs._e[1];
      _e[2] += rhs._e[2];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>&Vec3<T>::operator+=( const T& _v )
    {
      _e[0] += _v;
      _e[1] += _v;
      _e[2] += _v;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::operator-=( const Vec3<T>& rhs )
    {
      _e[0] -= rhs._e[0];
      _e[1] -= rhs._e[1];
      _e[2] -= rhs._e[2];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::operator-=( const T& _v )
    {
      _e[0] -= _v;
      _e[1] -= _v;
      _e[2] -= _v;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::operator*=( const T& rhs )
    {
      _e[0] *= rhs;
      _e[1] *= rhs;
      _e[2] *= rhs;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::operator*=( const Vec3<T>& rhs )
    {
      _e[0] *= rhs._e[0];
      _e[1] *= rhs._e[1];
      _e[2] *= rhs._e[2];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::operator/=( const T& rhs )
    {
      _e[0] /= rhs;
      _e[1] /= rhs;
      _e[2] /= rhs;
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::operator/=( const Vec3<T>& rhs )
    {
      _e[0] /= rhs._e[0];
      _e[1] /= rhs._e[1];
      _e[2] /= rhs._e[2];
      return *this;
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T>& Vec3<T>::operator=( const Vec3<T>& rhs )
    {
      _e[0] = rhs._e[0];
      _e[1] = rhs._e[1];
      _e[2] = rhs._e[2];
      return *this;
    }


  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline bool Vec3<T>::operator==( const Vec3<T>& rhs ) const
    {
      return
        _e[0] == rhs._e[0] &&
        _e[1] == rhs._e[1] &&
        _e[2] == rhs._e[2];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline bool Vec3<T>::operator!=( const Vec3<T>& rhs ) const
    {
      return
        _e[0] != rhs._e[0] ||
        _e[1] != rhs._e[1] ||
        _e[2] != rhs._e[2];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline bool Vec3<T>::operator>( const Vec3<T>& _v ) const {
    return
      _e[0] > _v._e[0] && 
      _e[1] > _v._e[1] &&
      _e[2] > _v._e[2];
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline bool Vec3<T>::operator>=( const Vec3<T>& _v ) const {
    return
      _e[0] >= _v._e[0] && 
      _e[1] >= _v._e[1] &&
      _e[2] >= _v._e[2];
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline bool Vec3<T>::operator<( const Vec3<T>& _v ) const {
    return
      _e[0] < _v._e[0] && 
      _e[1] < _v._e[1] &&
      _e[2] < _v._e[2];
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline bool Vec3<T>::operator<=( const Vec3<T>& _v ) const {
    return
      _e[0] <= _v._e[0] && 
      _e[1] <= _v._e[1] &&
      _e[2] <= _v._e[2];
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T& Vec3<T>::operator()( int idx )
    {
      return _e[idx];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T& Vec3<T>::operator()( int idx ) const
    {
      return _e[idx];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T & Vec3<T>::operator[]( int idx )
    {
      return _e[idx];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T& Vec3<T>::operator[]( int idx ) const
    {
      return _e[idx];
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline Vec3<T> operator*( const T& val, const Vec3<T>& vec )
    {
      return Vec3<T>( vec(0) * val, vec(1) * val, vec(2) * val );
    }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline void Vec3<T>::setX(const T& _v) {
    _e[0] = _v;
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline void Vec3<T>::setY(const T& _v) {
    _e[1] = _v;
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline void Vec3<T>::setZ(const T& _v) {
    _e[2] = _v;
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T Vec3<T>::x() {
    return _e[0];
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T Vec3<T>::y() {
    return _e[1];
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline T Vec3<T>::z() {
    return _e[2];
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T& Vec3<T>::x() const {
    return _e[0];
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T& Vec3<T>::y() const {
    return _e[1];
  }

  //------------------------------------------------------------------------------
  //!
  template< class T >
    inline const T& Vec3<T>::z() const {
    return _e[2];
  }

  /*==============================================================================
    TYPEDEF
    ==============================================================================*/

  typedef Vec3< int >    Vec3i;
  typedef Vec3< float >  Vec3f;
  typedef Vec3< double > Vec3d;

  
#endif
