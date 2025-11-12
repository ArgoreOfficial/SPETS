#pragma once

#include <string>

namespace Sprocket {

// intended for internal use
void pushError( const std::string& _error );
std::string popError();

}