#pragma once

#include <filesystem>
#include <shlobj.h>

namespace SPETS {

constexpr const char* VERSION_STR = "2.0";

std::filesystem::path getFolderPath( const KNOWNFOLDERID& _id );

}