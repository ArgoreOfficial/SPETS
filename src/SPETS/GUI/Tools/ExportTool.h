#pragma once

#include <SPETS/GUI/ITool.h>
#include <filesystem>
#include <vector>

namespace SPETS {

class ExportTool : public ITool
{
public:
	ExportTool() : ITool( "Export Blueprint", "Convert a .blueprint file into a 3D mesh" ) { }

	void onRunTool() override;

	void checkedExport( const std::filesystem::path& _path );
	
};

}