#include "cColor.h"

#include <Wyvern/Math/Math.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

cColor::cColor( byte _r, byte _g, byte _b, byte _a ) :
	r( _r ), 
	g( _g ), 
	b( _b ), 
	a( _a )
{

}

///////////////////////////////////////////////////////////////////////////////////////

wv::cColor::cColor( wv::cVector3<byte> _rgb, byte _a ) :
	r( _rgb.x ), 
	g( _rgb.y ), 
	b( _rgb.z ), 
	a( _a )
{
}

///////////////////////////////////////////////////////////////////////////////////////

wv::cColor::cColor( wv::cVector4<byte> _rgba ) :
	r( _rgba.x ), 
	g( _rgba.y ), 
	b( _rgba.z ), 
	a( _rgba.w )
{
}

///////////////////////////////////////////////////////////////////////////////////////

wv::cColor::cColor( wv::cVector3<float> _rgb, float _a ) :
	r( ( byte )( wv::Math::clamp( _rgb.x, 0.0f, 1.0f ) * 255.0f ) ), 
	g( ( byte )( wv::Math::clamp( _rgb.y, 0.0f, 1.0f ) * 255.0f ) ), 
	b( ( byte )( wv::Math::clamp( _rgb.z, 0.0f, 1.0f ) * 255.0f ) ), 
	a( ( byte )( wv::Math::clamp( _a, 0.0f, 1.0f ) * 255.0f ) )
{
}

///////////////////////////////////////////////////////////////////////////////////////

wv::cColor::cColor( wv::cVector4<float> _rgba ) :
	r( ( byte )( wv::Math::clamp( _rgba.x, 0.0f, 1.0f ) * 255.0f ) ), 
	g( ( byte )( wv::Math::clamp( _rgba.y, 0.0f, 1.0f ) * 255.0f ) ), 
	b( ( byte )( wv::Math::clamp( _rgba.z, 0.0f, 1.0f ) * 255.0f ) ), 
	a( ( byte )( wv::Math::clamp( _rgba.w, 0.0f, 1.0f ) * 255.0f ) )
{
}

///////////////////////////////////////////////////////////////////////////////////////

cColor::cColor( float _r, float _g, float _b, float _a ) :
	r( ( byte )( wv::Math::clamp( _r, 0.0f, 1.0f ) * 255.0f ) ),
	g( ( byte )( wv::Math::clamp( _g, 0.0f, 1.0f ) * 255.0f ) ),
	b( ( byte )( wv::Math::clamp( _b, 0.0f, 1.0f ) * 255.0f ) ),
	a( ( byte )( wv::Math::clamp( _a, 0.0f, 1.0f ) * 255.0f ) )
{

}

///////////////////////////////////////////////////////////////////////////////////////

cColor::cColor( dword _rgba ):
	r( ( _rgba >> 24 ) & 0xFF ),
	g( ( _rgba >> 16 ) & 0xFF ),
	b( ( _rgba >> 8  ) & 0xFF ),
	a( _rgba & 0xFF )
{
	
}

///////////////////////////////////////////////////////////////////////////////////////

bool wv::cColor::operator==( cColor& _other )
{
	return r == _other.r && g == _other.g && b == _other.b && a == _other.a;
}

///////////////////////////////////////////////////////////////////////////////////////

byte& wv::cColor::operator[]( const size_t& _index )
{
	switch( _index )
	{
		case 0:  return r;
		case 1:  return g;
		case 2:  return b;
		case 3:  return a;
		default: return r;
	}
}
