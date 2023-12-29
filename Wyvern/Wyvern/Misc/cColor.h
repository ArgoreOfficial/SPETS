#pragma once

#include <Wyvern/Core/defs.h>
#include <Wyvern/Math/Vector3.h>
#include <Wyvern/Math/Vector4.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class cColor
	{

	public:

		cColor( byte  _r, byte  _g, byte  _b, byte  _a = 255  );
		cColor( wv::cVector3< byte > _rgb,    byte  _a = 255  );
		cColor( wv::cVector4< byte > _rgba );
		cColor( wv::cVector3< float > _rgb,    float _a = 1.0f  );
		cColor( wv::cVector4< float > _rgba );
		cColor( float _r, float _g, float _b, float _a = 1.0f );

		cColor( dword _rgba );

///////////////////////////////////////////////////////////////////////////////////////

		byte r = 0x00;
		byte g = 0x00;
		byte b = 0x00;
		byte a = 0xFF;

		bool operator == ( cColor& _other );
		byte& operator[]( const size_t& _index );

	};

///////////////////////////////////////////////////////////////////////////////////////

	namespace Color
	{
		const cColor White      ( 0xFFFFFFFF );
		const cColor Gray       ( 0x0F0F0FFF );
		const cColor Black      ( 0x000000FF );
		const cColor Red        ( 0xFF0000FF );
		const cColor Yellow     ( 0xFFFF00FF );
		const cColor Turquoise  ( 0x30D5C8FF );
		const cColor Cyan       ( 0x00FFFFFF );
		const cColor Blue       ( 0x00FF00FF );
		const cColor Magenta    ( 0xFF00FFFF );
		const cColor PacificBlue( 0x039BCFFF );
		const cColor Green      ( 0x0000FFFF );
	}

///////////////////////////////////////////////////////////////////////////////////////

}