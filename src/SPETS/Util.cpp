#include "Util.h"

#ifdef _WIN32
    #include <Windows.h>
    #include <shlobj.h>
    #pragma comment(lib, "shell32.lib")
    #pragma comment(lib, "Ole32.lib")
#else
    #include <cstdlib>
    #include <pwd.h>
    #include <unistd.h>
#endif

#ifdef _WIN32
std::filesystem::path SPETS::getFolderPath(const KNOWNFOLDERID& _id)
{
    wchar_t* wpath = nullptr;
    if (SHGetKnownFolderPath(_id, 0, NULL, &wpath) != S_OK)
    {
        if (wpath) CoTaskMemFree(static_cast<void*>(wpath));
        return "";
    }

    std::filesystem::path path = wpath;
    CoTaskMemFree(static_cast<void*>(wpath));
    return path;
}
#else
std::filesystem::path SPETS::getFolderPath(const std::string& _id) {
    const char* home_env = std::getenv("HOME");
    std::filesystem::path home = home_env ? home_env : getpwuid(getuid())->pw_dir;

    // 1. Find the Steam Root
    std::filesystem::path steamRoot = home / ".steam" / "debian-installation";
    if (!std::filesystem::exists(steamRoot)) {
        steamRoot = home / ".local" / "share" / "Steam";
    }

    // 2. Point to the Sprocket Proton Prefix (AppID 1674170)
    std::filesystem::path pfxRoot = steamRoot / "steamapps" / "compatdata" / "1674170" / "pfx" / "drive_c" / "users" / "steamuser";

    // 3. Handle the specific redirections
    if (_id == "DOCUMENTS") {
        return pfxRoot / "Documents"; 
    }
    
    if (_id == "APPDATA_LOW") {
        return pfxRoot / "AppData" / "LocalLow";
    }

    if (_id == "PROGRAM_FILES") {
        return steamRoot; 
    }

    return home;
}
#endif


