#pragma once

#include "iWindow.h"

class cHubWindow : public iWindow
{
public:

	 cHubWindow( void );
	~cHubWindow( void );

protected:

	virtual void drawWindow() override;

};