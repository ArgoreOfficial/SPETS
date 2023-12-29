#pragma once

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class cIndexBuffer
	{

	public:

		 cIndexBuffer( void );
		~cIndexBuffer( void );

///////////////////////////////////////////////////////////////////////////////////////

		void create    ( void );
		void bind      ( void );
		void bufferData( unsigned int* _data, unsigned long long _size );

///////////////////////////////////////////////////////////////////////////////////////

	private:
	
		unsigned int m_handle = 0;
	
	};

///////////////////////////////////////////////////////////////////////////////////////

}