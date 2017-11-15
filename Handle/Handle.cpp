#include "Handle.h"
#include "Common/Macros.h"

CHandleFactory* CHandleFactory::ms_pGlobalHandleFactory = nullptr;

CHandleFactory* CHandleFactory::GetGlobalHandleFactory()
{
	return ms_pGlobalHandleFactory;
}

void CHandleFactory::CreateGlobalHandleFactory()
{
	ms_pGlobalHandleFactory = new CHandleFactory();
}

void CHandleFactory::DestroyGlobalHandleFactory()
{
	assert( ms_pGlobalHandleFactory );
	delete ms_pGlobalHandleFactory;
	ms_pGlobalHandleFactory = nullptr;
}

CHandleFactory::~CHandleFactory()
{
	DEBUG_MESSAGE( "Destroy handle factory\n" );
	for( auto it( m_oHandleMap.begin() ); it != m_oHandleMap.end(); ++it )
	{
		delete it->second;
	}
	m_oHandleMap.clear();
}
