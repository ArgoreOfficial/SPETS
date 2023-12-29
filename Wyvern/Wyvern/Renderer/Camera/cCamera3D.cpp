#include "cCamera3D.h"

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

void cCamera3D::update()
{

	iCamera::update();

	glm_proj = glm::perspective( glm::radians( m_fov ), m_aspect, 0.1f, 100.0f );

}
