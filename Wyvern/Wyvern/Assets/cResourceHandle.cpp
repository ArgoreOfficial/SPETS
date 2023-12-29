#include "cResourceHandle.h"

#include <Wyvern/Managers/cResourceManager.h>

using namespace wv;

///////////////////////////////////////////////////////////////////////////////////////

unsigned int cResourceHandle::getUUID( void )
{
	
	if ( m_uuid == 0 )
		m_uuid = cResourceManager::getInstance().getNewUUID();

	return m_uuid;

}
