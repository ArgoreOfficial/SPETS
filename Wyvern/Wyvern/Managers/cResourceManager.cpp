#include "cResourceManager.h"

#include <thread>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

void cResourceManager::loadQueuedAssetThread( cResourceManager* _instance )
{

	cResourceManager& instance = *_instance;

	for ( size_t i = 0; i < instance.m_resourceQueue.size(); i++ )
	{

		cResourceHandle handle = instance.m_resourceQueue[ i ];
		unsigned int uuid = handle.getUUID();
		std::string path = handle.getPath();

		instance.m_resources[ uuid ]->load( path );

	}

	WV_DEBUG( "Loading complete. Killing thread..." );
	
	instance.m_assetManagerMutex.lock();
	
	instance.m_hasLoaded = true;
	instance.m_isLoading = false;
	
	instance.m_assetManagerMutex.unlock();

}

///////////////////////////////////////////////////////////////////////////////////////

void cResourceManager::pushResource( cResourceHandle& _handle, iResource* _resource )
{

	unsigned int uuid = _handle.getUUID();
	m_resources[ uuid ] = _resource;
	m_resourceQueue.push_back( _handle );

}

///////////////////////////////////////////////////////////////////////////////////////

void cResourceManager::unloadResource( cResourceHandle& _handle )
{

	unsigned int uuid = _handle.getUUID();

	if ( !m_resources.count( uuid ) )
		return;

	delete m_resources[ uuid ];
	m_resources.erase( uuid );

}

///////////////////////////////////////////////////////////////////////////////////////

std::thread* cResourceManager::loadResources()
{

	m_isLoading = true;

	WV_DEBUG( "Loading assets. Creating thread..." );

	m_assetLoadThread = new std::thread( cResourceManager::loadQueuedAssetThread, this );
	return m_assetLoadThread;

}

///////////////////////////////////////////////////////////////////////////////////////

void cResourceManager::createResources( void )
{

	for ( size_t i = 0; i < m_resourceQueue.size(); i++ )
	{

		cResourceHandle handle = m_resourceQueue[ i ];
		iResource* resource = m_resources[ handle.getUUID() ];

		if( resource )
			resource->create();
		
	}

	m_resourceQueue.clear();
}

///////////////////////////////////////////////////////////////////////////////////////

void cResourceManager::unloadAllResources()
{
	
	WV_DEBUG( "Unloaded assets" );

}

///////////////////////////////////////////////////////////////////////////////////////

tModelHandle cResourceManager::loadModel( std::string _path )
{

	tModelHandle handle{ _path };
	cModel* resource = new cModel();
	
	m_models[ handle.getUUID() ] = resource;
	pushResource( handle, resource );

	return handle;

}

///////////////////////////////////////////////////////////////////////////////////////

tTextureHandle cResourceManager::loadTexture( std::string _path )
{

	tTextureHandle handle{ _path };
	cTextureObject* resource = new cTextureObject();

	m_textures[ handle.getUUID() ] = resource;
	pushResource( handle, resource );

	return handle;

}

///////////////////////////////////////////////////////////////////////////////////////

void cResourceManager::unloadModel( tModelHandle _handle )
{

	unsigned int uuid = _handle.getUUID();

	if ( !m_models.count( uuid ) )
		return;

	m_models.erase( uuid );
	unloadResource( _handle );

}

///////////////////////////////////////////////////////////////////////////////////////

void cResourceManager::unloadTexture( tTextureHandle _handle )
{
	
	unsigned int uuid = _handle.getUUID();

	if ( !m_textures.count( uuid ) )
		return;

	m_textures.erase( uuid );
	unloadResource( _handle );

}

///////////////////////////////////////////////////////////////////////////////////////

bool cResourceManager::isLoading()
{

	m_assetManagerMutex.lock();
	const bool out = m_isLoading;
	m_assetManagerMutex.unlock();

	return out;

}

///////////////////////////////////////////////////////////////////////////////////////

unsigned int cResourceManager::getNewUUID( void )
{

	m_lastUUID++;
	return m_lastUUID;

}

///////////////////////////////////////////////////////////////////////////////////////

cModel* cResourceManager::getModel( tModelHandle _handle )
{

	unsigned long long uuid = _handle.getUUID();
	
	if ( m_models.count( uuid ) )
		return m_models[ uuid ];

	return nullptr;

}

///////////////////////////////////////////////////////////////////////////////////////

cTextureObject* cResourceManager::getTexture( tTextureHandle _handle )
{
	
	unsigned long long uuid = _handle.getUUID();
	
	if ( m_textures.count( uuid ) )
		return m_textures[ uuid ];

	return nullptr;

}
