#include "VisibleListener.h"
#include <assert.h>
#include "Common/Macros.h"
#include "Visible.h"
#include "Messenger/Messenger.h"

CVisibleListener::CVisibleListener( bool bIs2D )
	: m_kpVisible( NULL )
	, m_bIs2D( bIs2D )
{
}

CVisibleListener::CVisibleListener( const CVisible& krVisible, bool bIs2D )
	: m_kpVisible( &krVisible )
	, m_bIs2D( bIs2D )
{
	if( bIs2D )
	{
		CMessenger::GlobalListen( *this, ms_kuDraw2DMessageUID );
	}
	else
	{
		CMessenger::GlobalListen( *this, ms_kuDrawMessageUID );
	}
}

CVisibleListener::~CVisibleListener()
{
	if( CMessenger::GlobalIsListening( *this, ms_kuDrawMessageUID ) )
	{
		CMessenger::GlobalStopListening( *this, ms_kuDrawMessageUID );
	}
	if( CMessenger::GlobalIsListening( *this, ms_kuDraw2DMessageUID ) )
	{
		CMessenger::GlobalStopListening( *this, ms_kuDraw2DMessageUID );
	}
}

void CVisibleListener::SetVisible( const CVisible& krVisible )
{
	assert( m_kpVisible == NULL && 
		!CMessenger::GlobalIsListening( *this, ms_kuDraw2DMessageUID ) &&
		!CMessenger::GlobalIsListening( *this, ms_kuDrawMessageUID ) );
	m_kpVisible = &krVisible;
	if( m_bIs2D )
	{
		CMessenger::GlobalListen( *this, ms_kuDraw2DMessageUID );
	}
	else
	{
		CMessenger::GlobalListen( *this, ms_kuDrawMessageUID );
	}
}

void CVisibleListener::Push( const CMessage& )
{
	assert( m_kpVisible );
	m_kpVisible->Draw();
}

void CVisibleListener::Hide()
{
	assert( CMessenger::GlobalIsListening( *this, ms_kuDrawMessageUID ) || 
		CMessenger::GlobalIsListening( *this, ms_kuDraw2DMessageUID ) );
	if(  CMessenger::GlobalIsListening( *this, ms_kuDrawMessageUID ) )
	{
		CMessenger::GlobalStopListening( *this, ms_kuDrawMessageUID );
	}
	if(  CMessenger::GlobalIsListening( *this, ms_kuDraw2DMessageUID ) )
	{
		CMessenger::GlobalStopListening( *this, ms_kuDraw2DMessageUID );
	}
}

void CVisibleListener::Show()
{
	if( m_bIs2D )
	{
		assert( !CMessenger::GlobalIsListening( *this, ms_kuDraw2DMessageUID )  );
		CMessenger::GlobalListen( *this, ms_kuDraw2DMessageUID );
	}
	else
	{
		assert( !CMessenger::GlobalIsListening( *this, ms_kuDrawMessageUID )  );
		CMessenger::GlobalListen( *this, ms_kuDrawMessageUID );
	}
}

bool CVisibleListener::IsHidden()
{
	if( m_bIs2D )
	{
		return( !CMessenger::GlobalIsListening( *this, ms_kuDraw2DMessageUID ) );
	}

	return( !CMessenger::GlobalIsListening( *this, ms_kuDrawMessageUID ) );
}

CVisibleListener& CVisibleListener::operator=( const CVisibleListener& )
{
	assert( false );
	return (*this);
}
