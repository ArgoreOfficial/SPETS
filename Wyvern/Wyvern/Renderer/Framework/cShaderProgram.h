#pragma once

#include <Wyvern/Assets/cShaderSource.h>

#include <glm/gtc/matrix_transform.hpp>

#include <map>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class cShaderProgram
	{

	public:

		 cShaderProgram( void );
		~cShaderProgram( void );

///////////////////////////////////////////////////////////////////////////////////////

		void create( cShaderSource _vertexSource, cShaderSource _fragmentSource );
		void use   ( void );
		void setUniform4f( std::string _name, glm::mat4x4 _matrix );

///////////////////////////////////////////////////////////////////////////////////////

	private:
		
		unsigned int getUniformLocation( std::string _name );

		unsigned int m_handle;
		// std::map<std::string, unsigned int> m_uniforms;

	};

///////////////////////////////////////////////////////////////////////////////////////

}