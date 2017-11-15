#ifndef WINDOWSCALLBACK_H
#define WINDOWSCALLBACK_H

#include <windows.h>
#include "Common/Types.h"
#include <assert.h>

class CWindowsOpenGlWindow;

typedef LRESULT ( CWindowsOpenGlWindow::*FWindowsCallback )( HWND, u32 uMessage, WPARAM, LPARAM );

class CWindowsCallback
{
public:
			CWindowsCallback( FWindowsCallback oCallback );
	void	SetContext( CWindowsOpenGlWindow* pContext )	{ m_pContext = pContext; }
	LRESULT	Call( HWND oHandle, u32 uMessage, WPARAM oParam1,LPARAM oParam2 );

private:
						CWindowsCallback()	{ assert( false ); };
	
private:
	FWindowsCallback		m_oCallback;
	CWindowsOpenGlWindow*	m_pContext;
};

#endif
