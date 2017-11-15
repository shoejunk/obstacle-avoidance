#include "Messenger.h"
#include "Message.h"
#include "Listener.h"
#include "Handle/Handle.h"
#include "Messenger/TypedMessage.h"

#include "Hash Table/HashTable.inl"

CMessenger CMessenger::ms_oGlobalMessenger;

void CMessenger::GlobalPush( CMessage& rMessage )
{
	ms_oGlobalMessenger.Push( rMessage );
}

void CMessenger::GlobalListen( CListener& rListener, u32 uMessageType )
{
	ms_oGlobalMessenger.Listen( rListener, uMessageType );
}

void CMessenger::GlobalStopListening( const CListener& krListener, u32 uMessageType )
{
	ms_oGlobalMessenger.StopListening( krListener, uMessageType );
}

bool CMessenger::GlobalIsListening( const CListener& krListener, u32 uMessageType )
{
	return ms_oGlobalMessenger.IsListening( krListener, uMessageType );
}

CMessenger::CMessenger()
	: m_oListenerTable( ms_kuTableSize, NULL )
{
	if( this != &ms_oGlobalMessenger )
	{
		TTypedMessage< CMessenger* > oNewMessengerMessage( 
			ms_kuNewMessengerMessageUID, this );
		GlobalPush( oNewMessengerMessage );
	}
}

CMessenger::~CMessenger()
{
	if( this != &ms_oGlobalMessenger )
	{
		TTypedMessage< CMessenger* > oDeleteMessengerMessage( 
			ms_kuDeleteMessengerMessageUID, this );
		GlobalPush( oDeleteMessengerMessage );
	}
	assert( m_oListenerTable.IsEmpty() );
}

void CMessenger::Push( CMessage& rMessage )
{
	// Store listeners in an array:
	CListener* aFoundListeners[ ms_kuMaxListenersPerMessage ];
	u16 uNumListeners( m_oListenerTable.Retrieve( rMessage.GetType(), aFoundListeners, 
		ms_kuMaxListenersPerMessage ) );
	assert( uNumListeners <= ms_kuMaxListenersPerMessage );

	// Attach listeners to handles:
	THandle< CListener >* aListenerHandles[ ms_kuMaxListenersPerMessage ];
	assert( CHandleFactory::GetGlobalHandleFactory() );
	for( u16 i( 0 ); i < uNumListeners; ++i )
	{
		aListenerHandles[ i ] = &CHandleFactory::GetGlobalHandleFactory()->CreateHandle( *aFoundListeners[ i ] );
	}

	// Push to listener objects:
	for( u16 i( 0 ); i < uNumListeners; ++i )
	{
		assert( aListenerHandles[ i ] );
		if( aListenerHandles[ i ]->Get() )
		{
			aListenerHandles[ i ]->Get()->Push( rMessage, *this );
		}
	}

	// Release the handles:
	for( u16 i( 0 ); i < uNumListeners; ++i )
	{
		CHandleFactory::GetGlobalHandleFactory()->DeleteHandle( *(aListenerHandles[i]) );
	}
}

void CMessenger::Listen( CListener& krListener, u32 uMessageType )
{
	m_oListenerTable.Store( uMessageType, &krListener );
}

void CMessenger::StopListening( const CListener& krListener, u32 uMessageType )
{
	m_oListenerTable.RemovePair( static_cast< u32 >( uMessageType ), &krListener );
}

bool CMessenger::IsListening( const CListener& krListener, u32 uMessageType )
{
	return m_oListenerTable.IsPair( uMessageType, &krListener );
}
