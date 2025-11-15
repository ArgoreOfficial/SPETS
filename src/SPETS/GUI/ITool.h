#pragma once

#include <string>

namespace SPETS {

class ITool
{
public:
	ITool( const std::string& _label, const std::string& _description = "" ) :
		m_label{ _label },
		m_description{ _description }
	{

	}

	virtual void onRunTool() = 0;

	std::string getLabel() const { return m_label; }
	std::string getDescription() const { return m_description; }

private:
	std::string m_label;
	std::string m_description;
};

}