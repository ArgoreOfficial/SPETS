#pragma once

#include <SPETS/GUI/ITool.h>
#include <filesystem>
#include <vector>

namespace SPETS {

class ImportTool : public ITool
{
public:
	ImportTool() : ITool( "Import Mesh", "Basic mesh importing." ) { }

	void onRunTool() override;
	
	void checkedImport( const std::filesystem::path& _path, const std::string& _faction );
	void quickImportFiles( const std::vector<std::string>& _files );
};

}