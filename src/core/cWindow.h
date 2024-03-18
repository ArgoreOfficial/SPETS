#pragma once

#include "Engine.h"

class cWindow
{
public:
	 cWindow();
	~cWindow();

	int create( unsigned int _width, unsigned int _height, const char* _title );
	void destroy();

	void beginFrame( void );
	void endFrame  ( void );

	bool shouldClose( void ) const { return glfwWindowShouldClose( m_window_object ); }
	void close() { glfwSetWindowShouldClose( m_window_object, true ); }

	GLFWwindow* const getWindowObject( void ) { return m_window_object; }
	HWND        const getWin32Handle ( void ) { return glfwGetWin32Window( m_window_object ); }
	unsigned int getWidth ( void ) const { return m_width; }
	unsigned int getHeight( void ) const { return m_height; }

	void setSize( int _width, int _height );

private:

	GLFWwindow* m_window_object = nullptr;
	unsigned int m_width = 0;
	unsigned int m_height = 0;

};
