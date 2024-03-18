#pragma once

#include <vector>
#include <string>

#include <math/cInterpolator.h>

class iToolWindow;

class cToolButton
{
public:

	 cToolButton( std::string _text, iToolWindow* _tool_window, std::vector<std::string> _allowed_extensions = {} );
	~cToolButton( void );

	void draw( void );

private:
	
	float updateHoveringT( bool _hovering );
	void  checkClick     ( bool _hovering );
	void  checkDragDrop  ( bool _hovering );
	
	void drawButton( std::string _text, int _width, int _height, float _padding, float _t, bool _enabled = true );

	std::string openFileDialog( void );

	std::string m_text;
	std::string m_on_hover_text      = "Load";
	std::string m_on_drag_hover_text = "Drop";
	std::vector<std::string> m_allowed_extensions;

	iToolWindow* m_tool_window;

	cInterpolator m_hover_interpolator;

	float m_hover_effect_t;

	bool m_hovering      = false;
	bool m_mouse_down_on = false;
	bool m_mouse_up_on   = false;
};