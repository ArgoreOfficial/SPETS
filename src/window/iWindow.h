#pragma once

#include <defines.h>

class iWindow
{
	DECLARE_INTERFACE( iWindow )

public:

	void draw()
	{
		if ( m_state )
			drawWindow();
	}

	void setState( bool _state ) { m_state = _state; };
	bool getState( void )        { return m_state; };

protected:

	virtual void drawWindow() = 0;

	bool m_state = true;

};
