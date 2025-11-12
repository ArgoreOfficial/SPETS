#include <Sprocket/Error.h>
#include <deque>

static std::deque<std::string> g_errors;

void Sprocket::pushError( const std::string& _error )
{
	g_errors.push_back( _error );
}

std::string Sprocket::popError()
{
	if ( g_errors.size() == 0 )
		return "";

	std::string err = g_errors.front();
	g_errors.pop_front();
	return err;
}
