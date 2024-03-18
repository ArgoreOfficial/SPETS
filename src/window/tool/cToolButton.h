#pragma once

#include <vector>
#include <string>

#include <math/cInterpolator.h>

class iToolWindow;

class cToolButton
{
public:

	 cToolButton( std::string _text, iToolWindow* _tool_window, std::vector<std::string> _allowed_extensions = {} );
	~cToolButton();

	void draw();

private:

	std::string m_text;
	std::string m_on_hover_text = "Load";
	std::vector<std::string> m_allowed_extensions;

	iToolWindow* m_tool_window;

	cInterpolator m_hover_interpolator;

	bool m_hovering = false;
	bool m_mouse_down_on = false;
	bool m_mouse_up_on = false;
};