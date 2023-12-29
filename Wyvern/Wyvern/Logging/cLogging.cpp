#include "cLogging.h"

#include <stdio.h>
#include <string>
#include <stdarg.h>

///////////////////////////////////////////////////////////////////////////////////////

void outputLog( eLogLevel _level, const char* _message, ... )
{

	const char* prefixes[ 6 ] = { "[FATAL]: ", "[ERROR]: " , "[WARNING]: " , "[INFO]: " , "[DEBUG]: " , "[TRACE]: " };
	char out[ 32000 ];
	char formatted[ 32000 ];

	va_list args;
	va_start( args, _message );
	vsnprintf( formatted, sizeof( formatted ), _message, args );
	va_end( args );
	
	sprintf( out, "%s%s\n", prefixes[ _level ], formatted );
	printf( "%s", out);

}

///////////////////////////////////////////////////////////////////////////////////////
