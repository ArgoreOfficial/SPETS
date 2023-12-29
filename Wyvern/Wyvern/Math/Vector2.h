#pragma once

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	template< typename T >
	class cVector2
	{
	public:
		T x, y;

		cVector2( void ) : x( 0 ), y( 0 ){}
		cVector2( const T& _t ) : x( _t ), y( _t ){}
		cVector2( const T& _x, const T& _y ) : x( _x ), y( _y ){}

		cVector2< T >& operator = ( const cVector2< T >& _other );
		cVector2< T >& operator +=( const cVector2< T >& _other );
		cVector2< T >  operator + ( const cVector2< T >& _other );
		cVector2< T >  operator * ( const float& _scalar );
		cVector2< T >& operator *=( const float& _scalar );
		cVector2< T >  operator / ( const float& _scalar );
		cVector2< T >& operator /=( const float& _scalar );
	};

///////////////////////////////////////////////////////////////////////////////////////

	typedef cVector2< float > cVector2f;

///////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	inline cVector2< T >& cVector2< T >::operator=( const cVector2< T >& _other )
	{
		x = _other.x;
		y = _other.y;
		return *this;
	}

	template< typename T >
	inline cVector2< T >& cVector2< T >::operator+=( const cVector2< T >& _other )
	{
		x += _other.x;
		y += _other.y;
		return *this;
	}

	template< typename T >
	inline cVector2< T > cVector2< T >::operator+( const cVector2< T >& _other )
	{
		return cVector2< T >( x + _other.x, y + _other.y );
	}

	template< typename T >
	inline cVector2< T > wv::cVector2< T >::operator*( const float & _scalar )
	{
		return cVector2< T >( x * _scalar, y * _scalar );
	}

	template< typename T >
	inline cVector2< T >& cVector2< T >::operator*=( const float & _scalar )
	{
		x *= _scalar;
		y *= _scalar;
		return *this;
	}
	
	template< typename T >
	inline cVector2< T > wv::cVector2< T >::operator/( const float & _scalar )
	{
		return cVector2< T >( x / _scalar, y / _scalar );
	}

	template< typename T >
	inline cVector2< T >& cVector2< T >::operator/=( const float & _scalar )
	{
		x /= _scalar;
		y /= _scalar;
		return *this;
	}

///////////////////////////////////////////////////////////////////////////////////////

}