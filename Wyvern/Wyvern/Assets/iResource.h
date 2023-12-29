#pragma once

#include <string>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class iResource
	{

///////////////////////////////////////////////////////////////////////////////////////

	public:

		iResource( void ) { }
		~iResource( void ) { }

///////////////////////////////////////////////////////////////////////////////////////

		bool isReady( void ) { return m_ready; }

///////////////////////////////////////////////////////////////////////////////////////

		virtual void load( std::string _path ) { }
		virtual void create( void ) { }

///////////////////////////////////////////////////////////////////////////////////////

	protected:

		bool m_ready = false;

	};

}