#include "WindowsOpenGlWindow.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <assert.h>
#include "Common/Macros.h"
#include "Messenger/Messenger.h"
#include "Windows Input/WindowsInputMessage.h"
#include "Messenger/TypedMessage.h"
#include "Window/WindowImplementation.h"

CWindowsOpenGlWindow* CWindowsOpenGlWindow::ms_pCurrentWindow( NULL );
i32 CWindowsOpenGlWindow::ms_iNextChildWindowIdentifier( 0 );
CWindowsCallbackTable CWindowsOpenGlWindow::ms_oWindowsCallbackTable( 10, NULL );

CWindowImplementation* NWindow::ImplementWindow( const i8* kpWindowName, i32 iX, i32 iY, 
	f32 fWidth, f32 fHeight, bool bFullscreen, CWindow& rWindow )
{
	return new CWindowsOpenGlWindow( kpWindowName, iX, iY, fWidth, fHeight, bFullscreen, rWindow );
}

u32 CWindowsOpenGlWindow::GetMaxTitleSize()
{
	return ms_kuMaxTitleSize;
}

i32 CWindowsOpenGlWindow::GetNextChildWindowIdentifier()
{
	return ms_iNextChildWindowIdentifier++;
}

void CWindowsOpenGlWindow::SetCurrentWindow( CWindowsOpenGlWindow& rWindow )
{
	ms_pCurrentWindow = &rWindow;
}

CWindowsOpenGlWindow::CWindowsOpenGlWindow( const i8* pTitle, i32 iX, i32 iY, 
	f32 fWidth, f32 fHeight, bool bFullscreen, CWindow& rWindow )
	: CWindowImplementation( fWidth, fHeight, bFullscreen, rWindow )
	, m_uWindowStyle( 0 )
	, m_uWindowStyleExtended( 0 )
	, m_bIsTerminating( false )
	, m_oCallback( &CWindowsOpenGlWindow::WindowsCallback )
{
	m_oCallback.SetContext( this );
	assert( strlen( pTitle ) < ms_kuMaxTitleSize );
	strcpy_s( m_aTitle, pTitle );
	memset( &m_oWindowClass, 0, sizeof( m_oWindowClass ) );
	memset( &m_oDeviceContext, 0, sizeof( m_oDeviceContext ) );
	ms_pCurrentWindow = this;
	m_oInstance = GetModuleHandle( NULL );
	assert( m_oInstance );
	m_oWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	m_oWindowClass.lpfnWndProc = GlobalWindowsCallback;
	m_oWindowClass.cbClsExtra = 0;
	m_oWindowClass.cbWndExtra = 0;
	m_oWindowClass.hInstance = m_oInstance;
	m_oWindowClass.hIcon = LoadIcon( NULL, IDI_WINLOGO );
	m_oWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_oWindowClass.hbrBackground = NULL;
	m_oWindowClass.lpszMenuName = NULL;
	m_oWindowClass.lpszClassName = m_aTitle;
	if ( !RegisterClass( &m_oWindowClass ) )
	{
		assert( false );
	}
	if( IsFullscreen() )
	{
		m_uWindowStyleExtended = WS_EX_APPWINDOW;
		m_uWindowStyle = WS_POPUP;
		ShowCursor( TRUE );
		DEVMODE dmScreenSettings;
		memset( &dmScreenSettings,0,sizeof( dmScreenSettings ) );
		dmScreenSettings.dmSize = sizeof( dmScreenSettings );
		dmScreenSettings.dmPelsWidth	= static_cast< u32 >( GetWidth() );
		dmScreenSettings.dmPelsHeight	= static_cast< u32 >( GetHeight() );
		dmScreenSettings.dmBitsPerPel	= 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		i32 iReturn( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) );
		if ( iReturn != DISP_CHANGE_SUCCESSFUL )
		{
			assert( iReturn != DISP_CHANGE_BADDUALVIEW );
			assert( iReturn != DISP_CHANGE_BADFLAGS );
			assert( iReturn != DISP_CHANGE_BADMODE );
			assert( iReturn != DISP_CHANGE_BADPARAM );
			assert( iReturn != DISP_CHANGE_FAILED );
			assert( iReturn != DISP_CHANGE_NOTUPDATED );
			assert( iReturn != DISP_CHANGE_RESTART );
			assert( false );
		}
	}
	else
	{
		m_uWindowStyleExtended=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		m_uWindowStyle=WS_OVERLAPPEDWINDOW;
	}
	RECT WindowRect;
	WindowRect.left=(long)iX;
	WindowRect.right=iX + (long)GetWidth();
	WindowRect.top=(long)iY;
	WindowRect.bottom=iY + (long)GetHeight();
	if( !AdjustWindowRectEx( &WindowRect, m_uWindowStyle, false, m_uWindowStyleExtended ) )
	{
		assert( false );
	}
	m_oWindowHandle = CreateWindowEx( m_uWindowStyleExtended, TEXT( pTitle ), TEXT( pTitle ),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | m_uWindowStyle, iX, iY, 
		WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top, 
		NULL, NULL, m_oInstance, NULL );
	if( !m_oWindowHandle )
	{
		DWORD uError( GetLastError() );
		DEBUG_MESSAGE( "Error in CreateWindowEx (%d)\n", uError );
		assert( false );
	}
	ms_oWindowsCallbackTable.Store( m_oWindowHandle, &m_oCallback );
	m_oDeviceContext = GetDC( m_oWindowHandle );
	assert( m_oDeviceContext );
	static PIXELFORMATDESCRIPTOR oPixelFormatDescriptor =
	{
		sizeof( PIXELFORMATDESCRIPTOR ), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 
		ms_kiBitsPerPixel, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32/*16*/, 0, 0, 
		PFD_MAIN_PLANE, 0, 0, 0, 0
	};
	i32 iPixelFormat( ChoosePixelFormat( m_oDeviceContext, &oPixelFormatDescriptor ) );
	assert( iPixelFormat );
	if( !SetPixelFormat( m_oDeviceContext, iPixelFormat, &oPixelFormatDescriptor ) )
	{
		assert( false );
	}
	m_oRenderingContext = wglCreateContext( m_oDeviceContext );
	assert( m_oRenderingContext );
	if( !wglMakeCurrent( m_oDeviceContext, m_oRenderingContext ) )
	{
		assert( false );
	}
	Resize( GetWidth(), GetHeight() );
}

CWindowsOpenGlWindow::~CWindowsOpenGlWindow()
{
	assert( !m_oRenderingContext && !m_oDeviceContext && !m_oWindowHandle &&
		!m_oInstance );
}

void CWindowsOpenGlWindow::Terminate()
{
	// Let everyone know that this window is terminating:
	TTypedMessage< CWindow* > oClosedMessage( CWindow::GetWindowClosedMessageUID(), &GetWindow() );
	CMessenger::GlobalPush( oClosedMessage );

	// The above message may have triggered the termination of the window,
	// so only proceed if the window still exists:
	if( !m_oDeviceContext )
	{
		return;
	}
	if( IsFullscreen() )
	{
		ChangeDisplaySettings( NULL, 0 );
		ShowCursor( TRUE );
	}
	if ( wglMakeCurrent( NULL, NULL ) )
	{
		if( !wglDeleteContext( m_oRenderingContext ) )
		{
			assert( false );
		}
	}
	m_oRenderingContext = NULL;
	if( !ReleaseDC( m_oWindowHandle, m_oDeviceContext ) )
	{
		assert( false );
	}
	m_oDeviceContext = NULL;
	assert( m_oWindowHandle );
	if( !DestroyWindow( m_oWindowHandle ) )
	{
		assert( false );
	}
	m_oWindowHandle = NULL;
	if( !UnregisterClass( m_oWindowClass.lpszClassName, m_oInstance ) )
	{
		assert( false );
	}
	m_oInstance = NULL;
	TTypedMessage< CWindow* > oDestroyedMessage( CWindow::GetWindowDestroyedMessageUID(), 
		&GetWindow() );
	CMessenger::GlobalPush( oDestroyedMessage );
}

void CWindowsOpenGlWindow::Draw() const
{
	assert( m_oDeviceContext && m_oRenderingContext );

	// Prepare to draw:
	if( !wglMakeCurrent( m_oDeviceContext, m_oRenderingContext ) )
	{
		assert( false );
	}
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Draw the 3D scene:
	CWindowImplementation::Draw();

	// Switch to 2D mode:
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho( -1, 1 , 1 , -1, -1, 1 );
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	// Draw the 2D HUD:
	CWindowImplementation::Draw2D();

	// Switch back to 3D mode:
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glDepthMask(GL_TRUE);

	// Finish up:
	SwapBuffers( m_oDeviceContext );
	return;
}

bool CWindowsOpenGlWindow::IsOpen() const
{
	if( m_oWindowHandle )
	{
		return true;
	}
	else
	{
		return false;
	}
}

HWND CWindowsOpenGlWindow::GetWindowHandle() const
{
	return m_oWindowHandle;
}

void CWindowsOpenGlWindow::Resize( f32 fNewWidth, f32 fNewHeight )
{
	CWindowImplementation::Resize( fNewWidth, fNewHeight );
	glViewport( 0, 0, static_cast< GLsizei >( fNewWidth ), 
		static_cast< GLsizei >( fNewHeight ) );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0f, fNewWidth / fNewHeight, 1.f, 200.f );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	
	glEnable( GL_TEXTURE_2D );
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.3f, 0.3f, 0.3f, 0.5f );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glDepthMask(GL_TRUE);
}

const i8* CWindowsOpenGlWindow::GetName() const
{
	return m_aTitle;
}

u64 CWindowsOpenGlWindow::GetWindowUID() const
{
	return reinterpret_cast< u64 >( GetWindowHandle() );
}

void CWindowsOpenGlWindow::Activate()
{
	if( !wglMakeCurrent( m_oDeviceContext, m_oRenderingContext ) )
	{
		assert( false );
	}
}

void CWindowsOpenGlWindow::Show()
{
	ShowWindow( m_oWindowHandle, SW_SHOW );
	SetForegroundWindow( m_oWindowHandle );
	SetFocus( m_oWindowHandle );
}

void CWindowsOpenGlWindow::SetDirty()
{
	Draw();
}

LRESULT CALLBACK CWindowsOpenGlWindow::GlobalWindowsCallback( HWND oWindowHandle, 
	u32 uMessage, WPARAM oParameter1, LPARAM oParameter2 )
{
	CWindowsCallback* pCallback( NULL );
	u16 uNumFound( ms_oWindowsCallbackTable.Retrieve( oWindowHandle, &pCallback, 1 ) );
	
	// There should be one callback per window handle. If not, there's a problem.
	if( uNumFound > 0 )
	{
		assert( uNumFound == 1 );
		assert( pCallback );
		return pCallback->Call( oWindowHandle, uMessage, oParameter1, oParameter2 );
	}

	return DefWindowProc( oWindowHandle, uMessage, oParameter1, oParameter2 );
}

LRESULT CWindowsOpenGlWindow::WindowsCallback( HWND oWindowHandle, u32 uMessage,
	WPARAM oParameter1, LPARAM oParameter2 )
{
	switch( uMessage )
	{
		case WM_QUIT:
			break;
		case WM_CLOSE:
			Terminate();
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_DESTROY:
		case WM_SIZE:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:
		case WM_CAPTURECHANGED:
		{
			if( uMessage == WM_LBUTTONDOWN || uMessage == WM_RBUTTONDOWN )
				SetCapture( m_oWindowHandle );
			else if( uMessage == WM_LBUTTONUP || uMessage == WM_RBUTTONUP )
				ReleaseCapture();
			CWindowsInputMessage oWindowsInputMessage( 
				&GetWindow(), uMessage, oParameter1, oParameter2 );
			CMessenger::GlobalPush( oWindowsInputMessage );
			break;
		}
		case WM_COMMAND:
		{
			CMessage oMessage( oParameter1 );
			CMessenger::GlobalPush( oMessage );
			break;
		}
	}

	return DefWindowProc( oWindowHandle, uMessage, oParameter1, oParameter2 );
}

void CWindowsOpenGlWindow::SetWindowHandle( HWND oWindowHandle )
{
	m_oWindowHandle = oWindowHandle;
}
