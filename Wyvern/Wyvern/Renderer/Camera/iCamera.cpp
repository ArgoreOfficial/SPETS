#include "iCamera.h"

#include <Wyvern/cApplication.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

iCamera::iCamera()
{

	m_aspect = cApplication::getInstance().getViewport().getAspect();

}

///////////////////////////////////////////////////////////////////////////////////////

wv::iCamera::~iCamera()
{

}

///////////////////////////////////////////////////////////////////////////////////////

void wv::iCamera::update()
{

	auto& viewport = cApplication::getInstance().getViewport();
	m_aspect = viewport.getAspect();

	glm::vec3 pos{ m_position.x, m_position.y, m_position.z };

	glm::mat4 view = glm::mat4( 1.0f );
	
	glm::vec3 direction;
	float yaw = glm::radians(m_rotation.y);
	float pitch = glm::radians(m_rotation.x);

	direction.x = sin( yaw );
	direction.y = -( sin( pitch ) * cos( yaw ) );
	direction.z = -( cos( pitch ) * cos( yaw ) );

	glm::vec3 cameraPos = glm::vec3( m_position.x, m_position.y, m_position.z );
	glm::vec3 cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f );
	view = glm::lookAt( cameraPos, cameraPos + direction, cameraUp );

	glm_view = view;

}
