#pragma once

#include <Wyvern/Math/Vector3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class iCamera
	{
	
	public:
	
		 iCamera();
		~iCamera();

///////////////////////////////////////////////////////////////////////////////////////

		virtual void update();

///////////////////////////////////////////////////////////////////////////////////////

		void setPosition( cVector3f _position ) { m_position = _position; }
		void setRotation( cVector3f _euler ) { m_rotation = _euler; };
		void setFOV( float _fov ) { m_fov = _fov; }
		void setAspect( float _aspect ) { m_aspect = _aspect; }

///////////////////////////////////////////////////////////////////////////////////////

		void move( cVector3f _move ) { m_position += _move; }
		void rotate( cVector3f _euler ) { m_rotation += _euler; }

///////////////////////////////////////////////////////////////////////////////////////

		glm::mat4 getViewMatrix( void ) { return glm_view; }
		glm::mat4 getProjMatrix( void ) { return glm_proj; }
		cVector3f getRotation  ( void ) { return m_rotation; }
		cVector3f getPosition  ( void ) { return m_position; }

///////////////////////////////////////////////////////////////////////////////////////

	protected:

		float m_view[ 16 ];
		float m_proj[ 16 ];

		glm::mat4 glm_view{ 1.0f }; // change to use wv::Math
		glm::mat4 glm_proj{ 1.0f };

		cVector3f m_position = { 0.0f, 0.0f, 0.0f };
		cVector3f m_rotation = { 0.0f, 0.0f, 0.0f};

		float m_aspect = 1.0f;
		float m_fov = 45.0f;

	};

///////////////////////////////////////////////////////////////////////////////////////

}