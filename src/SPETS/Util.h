#pragma once
#include <filesystem>
#include <string>

#ifdef _WIN32
    #include <shlobj.h>
#else
    // Define dummy types so the Linux compiler doesn't crash on Windows GUID names
    typedef std::string KNOWNFOLDERID;
    #define FOLDERID_ProgramFilesX86 "PROGRAM_FILES"
    #define FOLDERID_Documents "DOCUMENTS"
    #define FOLDERID_LocalAppDataLow "APPDATA_LOW"
#endif

namespace SPETS {
    inline const std::string VERSION_STR = "1.0.0";

    //New Helper
    inline std::filesystem::path getExecutableDir() {
#ifdef _WIN32
        wchar_t path[MAX_PATH];
        GetModuleFileNameW(NULL, path, MAX_PATH);
        return std::filesystem::path(path).parent_path();
#else
        // On Linux, this points to where the 'SPETS' binary actually lives
        return std::filesystem::read_symlink("/proc/self/exe").parent_path();
#endif
    }

    std::filesystem::path getFolderPath(const KNOWNFOLDERID& _id);
}

