#include <Sprocket/Error.h>
#include <deque>

static std::deque<std::string> g_errors;

void Sprocket::pushError( const std::string& _error )
{
	g_errors.push_back( _error );
}

bool Sprocket::hasError()
{
	return g_errors.size() > 0;
}

size_t Sprocket::getNumErrors()
{
	return g_errors.size();
}

std::string Sprocket::popError()
{
	if ( g_errors.size() == 0 )
		return "";

	std::string err = g_errors.front();
	g_errors.pop_front();
	return err;
}

size_t Sprocket::dumpErrors()
{
	size_t numErrors = Sprocket::getNumErrors();

	if ( Sprocket::hasError() )
	{
		printf( "Errors generated:\n" );
		while ( Sprocket::hasError() )
			printf( "    %s\n", Sprocket::popError().c_str() );
	}
	
    return numErrors;
}
