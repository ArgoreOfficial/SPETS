#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <variant>

namespace SPETS {

enum ArgType
{
	ArgType_Int,
	ArgType_String,
	ArgType_Flag
};

class ArgInfo
{
public:
	ArgInfo() = default;

	typedef std::variant<int, std::string, bool> TypeVariant_t;

	ArgInfo& setDesc( const std::string& _description ) { m_description = _description; return *this; }
	ArgInfo& setType( ArgType _type ) {
		m_type = _type; 
		return *this; 
	}
	
	ArgInfo& setDefault( TypeVariant_t _value ) { 
		m_hasDefault = true;
		m_default = _value; 
		return *this; 
	}

	ArgInfo& setImplicit( bool _value ) { m_implicit = _value; return *this; }
	
	std::string   getDesc()     { return m_description; }
	ArgType       getType()     { return m_type; }
	bool          getImplicit() { return m_implicit; }

	template<typename Ty>
	Ty getValue() { 
		if ( isSet() )
			return std::get<Ty>( m_currentValue );
		else if ( m_hasDefault )
			return std::get<Ty>( m_default );
		else
			return Ty{};
	}

	void setValue( TypeVariant_t _value ) { 
		m_hasValue     = true;
		m_currentValue = _value; 
	}

	bool isSet() { return m_hasValue; }

	template<typename Ty>
	bool operator == ( const Ty& _other ) { return m_currentValue == _other; }

private:
	std::string m_description = "";
	ArgType m_type = ArgType_Int;

	bool m_hasDefault = false;
	bool m_hasValue   = false;

	std::variant<int, std::string, bool> m_default;
	std::variant<int, std::string, bool> m_currentValue;

	// only for flags
	bool m_implicit = false;
};

class ArgParser
{
public:
	 ArgParser() = default;
	~ArgParser() = default;

	ArgInfo& addArg( const std::string& _command ) {
		if ( m_args.contains( _command ) )
			throw std::runtime_error( "Command already exists" );

		m_args[ _command ] = ArgInfo();
		return m_args[ _command ];
	}

	bool parseArguments( int _argc, char* _argv[] );

	std::string getErrorMessage() const { return m_errorMessage; }

	ArgInfo& get( const std::string& _arg ) {
		if ( !m_args.contains( _arg ) )
			throw std::runtime_error( "No arg of such name." );

		return m_args[ _arg ];
	}

private:
	std::unordered_map<std::string, ArgInfo> m_args;
	std::string m_errorMessage = "";
};

}