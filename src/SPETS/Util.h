#pragma once

#include <filesystem>
#include <shlobj.h>

namespace SPETS {

std::filesystem::path getFolderPath( const KNOWNFOLDERID& _id );

}