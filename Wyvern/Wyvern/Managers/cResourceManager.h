#pragma once

#include <Wyvern/Assets/iResource.h>
#include <Wyvern/Assets/cResourceHandle.h>

#include <Wyvern/Assets/cModel.h>
#include <Wyvern/Core/iSingleton.h>
#include <Wyvern/Renderer/Framework/cTextureObject.h>

#include <Wyvern/Logging/cLogging.h>
#include <Wyvern/Filesystem/cFilesystem.h>

#include <vector>
#include <unordered_map>
#include <mutex>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	class cResourceManager : public iSingleton<cResourceManager>
	{
	
	public:

		std::thread* loadResources     ( void );
		void         createResources   ( void );
		void         unloadAllResources( void );

///////////////////////////////////////////////////////////////////////////////////////

		tModelHandle   loadModel  ( std::string _path );
		tTextureHandle loadTexture( std::string _path );

///////////////////////////////////////////////////////////////////////////////////////

		void unloadModel  ( tModelHandle _handle );
		void unloadTexture( tTextureHandle _handle );

///////////////////////////////////////////////////////////////////////////////////////

		bool isLoading( void );

		unsigned int getNewUUID( void );

		cModel*          getModel  ( tModelHandle _handle );
		cTextureObject*  getTexture( tTextureHandle _handle );

///////////////////////////////////////////////////////////////////////////////////////

	private:

		static void loadQueuedAssetThread( cResourceManager* _instance );


///////////////////////////////////////////////////////////////////////////////////////
		
		void pushResource( cResourceHandle& _handle, iResource* _resource );
		void unloadResource( cResourceHandle& _handle );

		template<class kT, class T>
		void clearMap( std::map<kT, T> _map );

///////////////////////////////////////////////////////////////////////////////////////

		std::vector<cResourceHandle> m_resourceQueue;

		std::unordered_map<unsigned int, iResource*> m_resources;
		std::unordered_map<unsigned int, cModel*> m_models;
		std::unordered_map<unsigned int, cTextureObject*> m_textures;
		
///////////////////////////////////////////////////////////////////////////////////////
		
		bool m_isLoading = false;
		bool m_hasLoaded = false;
		std::mutex m_assetManagerMutex;
		std::thread* m_assetLoadThread = nullptr;
		unsigned int m_lastUUID = 0;
	};

///////////////////////////////////////////////////////////////////////////////////////

	template<class kT, class T>
	void cResourceManager::clearMap( std::map<kT, T> _map )
	{

		for ( std::map<kT, T>::iterator itr = _map.begin(); itr != _map.end(); itr++ )
		{
			delete itr->second;
		}
		_map.clear();

	}

///////////////////////////////////////////////////////////////////////////////////////

}
