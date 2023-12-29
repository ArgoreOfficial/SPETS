#pragma once

#include <stdio.h>
// std studio -david 2023

///////////////////////////////////////////////////////////////////////////////////////

enum eLogLevel
{
	kFatal = 0,
	kError = 1,
	kWarning = 2,
	kInfo = 3,
	kDebug = 4,
	kTrace = 5
};

///////////////////////////////////////////////////////////////////////////////////////

void outputLog( eLogLevel _level, const char* message, ... );

///////////////////////////////////////////////////////////////////////////////////////

#define LOG_RED     printf( "\x1b[31m" )
#define LOG_GREEN   printf( "\x1b[32m" )
#define LOG_YELLOW  printf( "\x1b[33m" )
#define LOG_BLUE    printf( "\x1b[34m" )
#define LOG_MAGENTA printf( "\x1b[35m" )
#define LOG_CYAN    printf( "\x1b[36m" )
#define LOG_RESET   printf( "\x1b[0m"  )

#define WV_FATAL(   msg, ... ) LOG_RED;     outputLog( eLogLevel::kFatal,   msg, __VA_ARGS__ ); LOG_RESET;
#define WV_ERROR(   msg, ... ) LOG_RED;     outputLog( eLogLevel::kError,   msg, __VA_ARGS__ ); LOG_RESET;
#define WV_WARNING( msg, ... ) LOG_YELLOW;  outputLog( eLogLevel::kWarning, msg, __VA_ARGS__ ); LOG_RESET;
#define WV_INFO(    msg, ... ) LOG_RESET;   outputLog( eLogLevel::kInfo,    msg, __VA_ARGS__ ); LOG_RESET;
#define WV_DEBUG(   msg, ... ) LOG_RESET;   outputLog( eLogLevel::kDebug,   msg, __VA_ARGS__ ); LOG_RESET;
