#pragma once

#include "Wyvern/Core/iSceneObject.h"

#include <vector>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class cSceneGraph
	{

	public:

		 cSceneGraph( void ) { }
		~cSceneGraph( void ) { }

///////////////////////////////////////////////////////////////////////////////////////

		void add( iSceneObject* _object );

///////////////////////////////////////////////////////////////////////////////////////

		void update( double _deltaTime );
		void draw3D( void );
		void draw2D( void );
		void drawUI( void );

///////////////////////////////////////////////////////////////////////////////////////

	private:

		unsigned int m_internalIDCount = 1;

		std::vector<iSceneObject*> m_objects = {};

	};

///////////////////////////////////////////////////////////////////////////////////////

}