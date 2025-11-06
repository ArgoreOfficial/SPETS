#pragma once

#include <filesystem>
#include <shlobj.h>

namespace SPETS {

constexpr const char* VERSION_STR = "p2.0-25.1";

std::filesystem::path getFolderPath( const KNOWNFOLDERID& _id );

}