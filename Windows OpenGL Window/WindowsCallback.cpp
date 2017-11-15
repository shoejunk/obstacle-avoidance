#include "WindowsCallback.h"
#include "windows.h"
#include "Window/Window.h"
#include "WindowsOpenGlWindow.h"

CWindowsCallback::CWindowsCallback( FWindowsCallback oCallback )
	: m_oCallback( oCallback )
	, m_pContext( NULL )
{
}

LRESULT CWindowsCallback::Call( HWND oHandle, u32 uMessage, WPARAM oParam1,LPARAM oParam2 )
{
	assert( m_pContext );
	return ( m_pContext->*m_oCallback )( oHandle, uMessage, oParam1, oParam2 );
}
