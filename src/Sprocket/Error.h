#pragma once

#include <string>
#include <format>

namespace Sprocket {

// intended for internal use
void pushError( const std::string& _error );


bool hasError();
size_t getNumErrors();
std::string popError();

// returns number of errors dumped
size_t dumpErrors();

}

// Corrected for cross-platform (GCC and MSVC)
#define SPROCKET_PUSH_ERROR( ... ) \
    Sprocket::pushError( std::format( "{} ({}) : {}", __FUNCTION__, __LINE__, std::format( __VA_ARGS__ ) ) )

