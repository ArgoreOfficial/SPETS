#include "cApplication.h"

#include <format>



cApplication::cApplication()
{
#if defined DEBUG
	char type = 'd';
#elif defined RELEASE
	char type = 'p';
#elif defined FINAL
	char type = 'r';
#endif

	m_version = {
		.type     = type,
		.major    = 2,
		.minor    = 0,
		.year     = 24,
		.revision = 0,
	};

}

cApplication::~cApplication()
{

}

void cApplication::start()
{
	std::string title = std::format( "SPETS {}", getVersion() );
	m_window.create( 300, 300, title.c_str() );
	m_renderer.create( m_window );


}

void cApplication::run()
{
	while ( !m_window.shouldClose() )
	{
		m_window.beginFrame();
		m_renderer.beginFrame();

		m_renderer.clear( 0x00000000 );

		m_window.endFrame();
		m_renderer.endFrame();
	}
}

void cApplication::shutdown()
{
	m_renderer.destroy();

	m_window.destroy();
}

std::string cApplication::getVersion()
{
	return std::format( "{}{}.{}-{}.{}", m_version.type, m_version.major, m_version.minor, m_version.year, m_version.revision );
}
