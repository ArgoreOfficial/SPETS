#pragma once

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	template< typename T >
	class cVector4
	{
	public:
		T x, y, z, w;

		cVector4( void ) : x( 0 ), y( 0 ), z( 0 ), w( 0 ){}
		cVector4( const T& _t ) : x( _t ), y( _t ), z( _t ), w( _t ){}
		cVector4( const T& _x, const T& _y, const T& _z, const T& _w ) : x( _x ), y( _y ), z( _z ), w( _w ){}

		cVector4< T >& operator = ( const cVector4< T >& _other );
		cVector4< T >& operator +=( const cVector4< T >& _other );
		cVector4< T >  operator + ( const cVector4< T >& _other );
		cVector4< T >  operator * ( const float& _scalar );
		cVector4< T >& operator *=( const float& _scalar );
		cVector4< T >  operator / ( const float& _scalar );
		cVector4< T >& operator /=( const float& _scalar );
	};

///////////////////////////////////////////////////////////////////////////////////////

	typedef cVector4< float > cVector4f;

///////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	inline cVector4< T >& cVector4<T>::operator=( const cVector4< T >& _other )
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		w = _other.w;
		return *this;
	}

	template< typename T >
	inline cVector4< T >& cVector4< T >::operator+=( const cVector4< T >& _other )
	{
		x += _other.x;
		y += _other.y;
		z += _other.z;
		w += _other.w;
		return *this;
	}

	template< typename T >
	inline cVector4< T > cVector4< T >::operator+( const cVector4< T >& _other )
	{
		return cVector2< T >( x + _other.x, y + _other.y, z + _other.z, w + _other.w );
	}

	template< typename T >
	inline cVector4< T > wv::cVector4< T >::operator*( const float & _scalar )
	{
		return cVector2< T >( x * _scalar, y * _scalar, z * _scalar, w * _scalar );
	}

	template< typename T >
	inline cVector4< T >& cVector4< T >::operator*=( const float & _scalar )
	{
		x *= _scalar;
		y *= _scalar;
		z *= _scalar;
		w *= _scalar;
		return *this;
	}

	template< typename T >
	inline cVector4< T > wv::cVector4< T >::operator/( const float & _scalar )
	{
		return cVector2< T >( x / _scalar, y / _scalar, z / _scalar, w / _scalar );
	}

	template< typename T >
	inline cVector4< T >& cVector4< T >::operator/=( const float & _scalar )
	{
		x /= _scalar;
		y /= _scalar;
		z /= _scalar;
		w /= _scalar;
		return *this;
	}

///////////////////////////////////////////////////////////////////////////////////////

}