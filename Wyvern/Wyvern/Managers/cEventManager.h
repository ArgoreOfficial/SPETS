#pragma once

#include <Wyvern/Core/iSingleton.h>
#include <Wyvern/Events/cEvents.h>

#include <functional>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class cEventManager : public iSingleton<cEventManager>
	{

	public:

		template<class T>
		static void hook( std::function<void( T& )> _func )
		{

			auto& hookedEvents = getHookedEvents<T>();
			hookedEvents.push_back( _func );

		}

		template<class T>
		static void call( T& _event )
		{

			auto& hookedEvents = getHookedEvents<T>();
			for ( int i = 0; i < hookedEvents.size(); i++ )
			{
				hookedEvents[ i ]( _event );
			}

		}

///////////////////////////////////////////////////////////////////////////////////////

	private:

		template<class T>
		static std::vector<std::function<void( T& )>>& getHookedEvents()
		{

			static std::vector<std::function<void( T& )>> hookedEvents;
			return hookedEvents;

		}

	};

///////////////////////////////////////////////////////////////////////////////////////

}