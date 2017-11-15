#include "Listener.h"
#include "Common/Macros.h"
#include "Handle/Handle.h"

CListener::~CListener()
{
	DEBUG_MESSAGE( "Listener destructor\n" );
	CHandleFactory* pFactory( CHandleFactory::GetGlobalHandleFactory() );
	if( pFactory && pFactory->DoesHandleExist( *this ) )
	{
		pFactory->GetHandle( *this ).Disable();
	}
}
