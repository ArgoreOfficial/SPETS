#include "ArgParser.h"

#include <algorithm>
#include <format>

bool isNumber( const std::string& _str )
{
	std::string::const_iterator it = _str.begin();
	while ( it != _str.end() && std::isdigit( *it ) ) ++it;
	return !_str.empty() && it == _str.end();
}

std::string lowercase( std::string _str )
{
	std::string copy = _str;
	std::transform( 
		copy.begin(),
		copy.end(),
		copy.begin(),
		[]( unsigned char c ) { return std::tolower( c ); } 
	);

	return copy;
}

bool SPETS::ArgParser::parseArguments( int _argc, char* _argv[] )
{
	int argCounter = 0;

	for ( size_t i = 1; i < _argc; i++ )
	{
		std::string arg = _argv[ i ];

		if ( m_args.contains( arg ) )
		{
			argCounter++;
			ArgInfo& info = m_args[ arg ];
			
			if ( i + 1 == _argc || m_args.contains( _argv[ i + 1 ] ) ) // too few arguments
			{
				if ( info.getType() == ArgType_Flag )
				{
					info.setValue( info.getImplicit() );
					continue;
				}
				else
				{
					m_errorMessage = std::format( "No value provided for argument {} \"{}\"", argCounter, arg );
					return false;
				}
			}

			std::string valStr = _argv[ i + 1 ];

			switch ( info.getType() )
			{
			case ArgType_Int:    
				if ( isNumber )
				{
					m_errorMessage = std::format( "Argument {} \"{}\" expected number", argCounter, arg );
					return false;
				}

				info.setValue( std::stoi( valStr ) ); 
				break;

			case ArgType_String: 
				info.setValue( valStr ); 
				break;

			case ArgType_Flag: 
				if ( lowercase( valStr ) == "true" ) 
					info.setValue( true );
				else if ( lowercase( valStr ) == "false" ) 
					info.setValue( false );
				else
				{
					m_errorMessage = std::format( "Argument {} \"{}\" expected bool, got \"{}\"", argCounter, arg, valStr );
					return false;
				}

				break;
			}

			i++;
		}
		else
		{
			m_errorMessage = std::format( "Unknown argument {} \"{}\"", argCounter, arg );
			return false;
		}
	}

    return true;
}

void SPETS::ArgParser::printHelp()
{
	printf( "Usage: SPETS [options]\n" );
	printf( "Options:\n" );

	for ( auto& info : m_args )
	{
		std::string inputName = info.second.getInputName();
		if( inputName == "" )
			printf( "  %-22s%s\n", info.first.c_str(), info.second.getDesc().c_str() );
		else
		{
			std::string argname = info.first + " <" + inputName + ">";
			printf( "  %-22s%s\n", argname.c_str(), info.second.getDesc().c_str() );
		}
	}
}
