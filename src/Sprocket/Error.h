#pragma once

#include <string>
#include <format>

namespace Sprocket {

// intended for internal use
void pushError( const std::string& _error );


bool hasError();
size_t getNumErrors();
std::string popError();

}

#define SPROCKET_PUSH_ERROR( ... ) Sprocket::pushError( std::format( __FUNCTION__ "({}) : {}", __LINE__, std::format( __VA_ARGS__ ) ) )