#pragma once

#include <Wyvern/Core/defs.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

	namespace Math
	{

///////////////////////////////////////////////////////////////////////////////////////

		template < typename T > T clamp( const T& _value, const T& _min, const T& _max );
		template < typename T > T pow2 ( const T& _value );
		template < typename T > T pow3 ( const T& _value );
		template < typename T > T pow4 ( const T& _value );
		template < typename T > T pow5 ( const T& _value );
		template < typename T > T abs  ( const T& _value );
		template < typename T > T min  ( const T& _a, const T& _b );
		template < typename T > T max  ( const T& _a, const T& _b );

///////////////////////////////////////////////////////////////////////////////////////

		template < typename T > T clamp( const T& _value, const T& _min, const T& _max )
		{ 
			const T t = _value < _min ? _min : _value;
			return t > _max ? _max : t;
		}

		template< typename T > T pow2( const T& _value )
		{
			return _value * _value;
		}

		template< typename T > T pow3( const T& _value )
		{
			return _value * _value * _value;
		}

		template< typename T > T pow4( const T& _value )
		{
			return _value * _value * _value * _value;
		}

		template< typename T > T pow5( const T& _value )
		{
			return _value * _value * _value * _value * _value;
		}

		template< typename T > T abs( const T& _value )
		{
			return _value < T( 0 ) ? -_value : _value;
		}

		template< typename T > T min( const T& _a, const T& _b )
		{
			return _a < _b ? _a : _b;
		}

		template< typename T > T max( const T& _a, const T& _b )
		{
			return _a > _b ? _a : _b;
		}

///////////////////////////////////////////////////////////////////////////////////////

	}

}