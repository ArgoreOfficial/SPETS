#include "Wyvern/Renderer/Framework/cShaderProgram.h"

#include <Wyvern/Logging/cLogging.h>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

cShaderProgram::cShaderProgram( void )
{

}

///////////////////////////////////////////////////////////////////////////////////////

cShaderProgram::~cShaderProgram( void )
{
	glDeleteProgram( m_handle );
}

///////////////////////////////////////////////////////////////////////////////////////

void cShaderProgram::create( cShaderSource _vertexSource, cShaderSource _fragmentSource )
{

	m_handle = glCreateProgram();
	const char* vsource = _vertexSource.getSource();
	const char* fsource = _fragmentSource.getSource();

	unsigned int vertex, fragment;
	int success;
	char infoLog[ 512 ];

	// vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vsource, NULL );
	glCompileShader( vertexShader );

	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
	if ( !success )
	{

		glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
		WV_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED \n %s", infoLog);

	};

	// fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fsource, NULL );
	glCompileShader( fragmentShader );

	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
	if ( !success )
	{

		glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
		WV_ERROR( "ERROR::SHADER::VERTEX::COMPILATION_FAILED \n %s", infoLog );

	};

	glAttachShader( m_handle, vertexShader );
	glAttachShader( m_handle, fragmentShader );
	glLinkProgram( m_handle );

	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

}

///////////////////////////////////////////////////////////////////////////////////////

void cShaderProgram::use( void )
{
	glUseProgram( m_handle );
}

void wv::cShaderProgram::setUniform4f( std::string _name, glm::mat4x4 _matrix )
{
	glUniformMatrix4fv( getUniformLocation( _name ), 1, GL_FALSE, glm::value_ptr( _matrix ) );
}

unsigned int wv::cShaderProgram::getUniformLocation( std::string _name )
{
	/*
	if ( m_uniforms.count( _name ) )
		return m_uniforms[_name];
	*/

	unsigned int location = glGetUniformLocation( m_handle, _name.c_str() );
	// m_uniforms[ _name ] = location;
	return location;
}
