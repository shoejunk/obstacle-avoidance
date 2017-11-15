#include "WindowHandler.h"
#include "assert.h"

CWindowHandler::CWindowHandler()
: m_uNumWindows( 0 )
{
	for( u32 i( 0 ); i < ms_kuMaxWindows; ++i )
	{
		m_aWindowList[ i ] = NULL;
	}
}

CWindowHandler::~CWindowHandler()
{
}

void CWindowHandler::AddWindow( CWindow* pWindow )
{
	assert( m_uNumWindows < ms_kuMaxWindows && pWindow != NULL );
	m_aWindowList[ m_uNumWindows ] = pWindow;
	++m_uNumWindows;
}

void CWindowHandler::RemoveWindow( CWindow* pWindow )
{
	bool bFound( false );
	for( u32 i( 0 ); i < m_uNumWindows; ++i )
	{
		if( !bFound && m_aWindowList[ i ] == pWindow )
		{
			bFound = true;
		}
		if( bFound )
		{
			if( i + 1 < m_uNumWindows )
			{
				m_aWindowList[ i ] = m_aWindowList[ i + 1 ];
			}
			else
			{
				m_aWindowList[ i ] = NULL;
			}
		}
	}
	assert( bFound );
}

CWindow* CWindowHandler::GetWindow( u32 uWindowIndex )
{
	assert( uWindowIndex < m_uNumWindows );
	return m_aWindowList[ uWindowIndex ];
}

u32 CWindowHandler::GetNumWindows() const
{
	return m_uNumWindows;
}
