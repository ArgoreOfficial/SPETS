#pragma once

// On Windows/MSVC, this handles the auto-linking magic
#ifdef _WIN32
    #include <msvc/wx/setup.h>
#endif

// This is the standard way to get wxWidgets definitions portably
#include <wx/defs.h> 
#include <wx/wx.h>

