#include "ListenerLatch.h"
#include "Messenger.h"

CListenerLatch::CListenerLatch()
	: m_bOn( false )
	, m_uMessage( 0 )
{
}

CListenerLatch::CListenerLatch( u32 uMessage )
	: m_bOn( false )
	, m_uMessage( uMessage )
{
	if( uMessage != 0 )
	{
		CMessenger::GlobalListen( *this, uMessage );
	}
}

CListenerLatch::~CListenerLatch()
{
	if(	CMessenger::GlobalIsListening( *this, m_uMessage ) )
	{
		CMessenger::GlobalStopListening( *this, m_uMessage );
	}
}

void CListenerLatch::Push( CMessage& rMessage )
{
	CListener::Push( rMessage );
	m_bOn = true;
}

bool CListenerLatch::IsOn() const
{
	return m_bOn;
}

void CListenerLatch::TurnOff()
{
	m_bOn = false;
}

void CListenerLatch::TurnOn()
{
	m_bOn = true;
}

void CListenerLatch::SetMessage( u32 uMessage )
{
	if( m_uMessage != 0 )
	{
		CMessenger::GlobalStopListening( *this, m_uMessage );
	}
	m_uMessage = uMessage;
	CMessenger::GlobalListen( *this, uMessage );
}
