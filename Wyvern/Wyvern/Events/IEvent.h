#pragma once

#include <Wyvern/Managers/cEventManager.h>

#include <functional>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	template<class T>
	class iEvent
	{

	public:

		/// <summary>
		/// <para>Hook member function to an event</para>
		/// </summary>
		/// <typeparam name="C">Caller class type</typeparam>
		/// <param name="_func">The function</param>
		/// <param name="_obj">The owner of the member function (usually "this")</param>
		template<class C>
		static void hook( std::function<void( C*, T& )> _func, C* _obj );

		/// <summary>
		/// Hook static or global function to an event
		/// </summary>
		/// <param name="_func">The function</param>
		static void hook( std::function<void( T& )> _func );

///////////////////////////////////////////////////////////////////////////////////////

	protected:

		iEvent( void ) { }

	};

///////////////////////////////////////////////////////////////////////////////////////

	template<class T>
	template<class C>
	void iEvent<T>::hook( std::function<void( C*, T& )> _func, C* _obj )
	{

		auto& func = std::bind( _func, _obj, std::placeholders::_1 );
		cEventManager::hook<T>( func );

	}

///////////////////////////////////////////////////////////////////////////////////////

	template<class T>
	void iEvent<T>::hook( std::function<void( T& )> _func )
	{

		cEventManager::hook<T>( _func );

	}

///////////////////////////////////////////////////////////////////////////////////////

}
