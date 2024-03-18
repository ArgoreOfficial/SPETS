#pragma once

#define SPETS_INTERFACE( _class )                  \
	public:                                          \
		virtual ~_class( void ) = default;           \
	protected:                                       \
		_class() { }                                 \
		_class( const _class& )            = delete; \
		_class& operator=( const _class& ) = delete; \
		_class( _class && )                = delete; \
		_class& operator=( _class && )     = delete; \
	private:

