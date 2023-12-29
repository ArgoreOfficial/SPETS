#include "cCamera2D.h"

#include <Wyvern/cApplication.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

void cCamera2D::update()
{

	iCamera::update();

	auto& viewport = cApplication::getInstance().getViewport();
	
	float vw = viewport.getWidth();
	float vh = viewport.getHeight();
	glm_proj = glm::ortho( -vw, vw, -vh, vh, -100.0f, 100.0f );

}
