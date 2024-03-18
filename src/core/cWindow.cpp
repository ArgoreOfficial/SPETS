#include "cWindow.h"

#include <stdio.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

void processInput( GLFWwindow* window )
{
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
		glfwSetWindowShouldClose( window, true );
}


cWindow::cWindow()
{

}

cWindow::~cWindow()
{

}

int cWindow::create( unsigned int _width, unsigned int _height, const char* _title )
{

	if ( !glfwInit() )
	{
		fprintf( stderr, "Failed to init GLFW\n" );
		return 1;
	}

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE );
	glfwWindowHint( GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE );

	glfwWindowHint( GLFW_DECORATED, GLFW_FALSE );
#ifndef DEBUG
#endif
	printf( "GLFW version: %s\n", glfwGetVersionString() );

	m_window_object = glfwCreateWindow( _width, _height, _title, NULL, NULL );
	if ( !m_window_object )
	{
		fprintf( stderr, "Failed to create GLFW window\n" );
		return 1;
	}
	glfwMakeContextCurrent( m_window_object );

	m_width = _width;
	m_height = _height;

	glfwSwapInterval( 1 ); /* enable vsync so it doesn't eat 100% of the gpu */

}

void cWindow::destroy()
{
	glfwTerminate();
}

void cWindow::beginFrame( void )
{
	processInput( m_window_object );

}

void cWindow::endFrame( void )
{
	glfwSwapBuffers( m_window_object );
	glfwPollEvents();
}

void cWindow::setPosition( int _x, int _y )
{
	glfwSetWindowPos( m_window_object, _x, _y );
}

void cWindow::setSize( int _width, int _height )
{
	glfwSetWindowSize( m_window_object, _width, _height );
}
