#include "Window.h"
#include <assert.h>
#include "Messenger/Message.h"
#include "Messenger/Messenger.h"
#include "WindowImplementation.h"
#
#include "Dynamic Array/DynamicArray.inl"

CWindow* CWindow::ms_pDefaultWindow( NULL );

void CWindow::SetDefaultWindow( CWindow* pWindow )
{ 
	ms_pDefaultWindow = pWindow; 
}

CWindow::CWindow( const i8* kpWindowName, i32 iX, i32 iY, f32 fWidth, f32 fHeight, 
	bool bFullscreen )
	: m_pWindowImplementation( NULL )
{
	assert( fWidth >= 0.f && fHeight >= 0.f );
	m_pWindowImplementation = NWindow::ImplementWindow( kpWindowName, iX, iY, fWidth,
		fHeight, bFullscreen, *this );
}

CWindow::~CWindow()
{
	if( m_pWindowImplementation )
	{
		m_pWindowImplementation->Terminate();
		delete m_pWindowImplementation;
	}
}

void CWindow::Draw() const
{
	assert( m_pWindowImplementation );
	m_pWindowImplementation->Draw();
}

void CWindow::Draw2D() const
{
	assert( m_pWindowImplementation );
	m_pWindowImplementation->Draw2D();
}

f32 CWindow::GetWidth() const
{
	assert( m_pWindowImplementation );
	return m_pWindowImplementation->GetWidth();
}

f32 CWindow::GetHeight() const
{
	assert( m_pWindowImplementation );
	return m_pWindowImplementation->GetHeight();
}

void CWindow::Resize( f32 fNewWidth, f32 fNewHeight )
{
	assert( m_pWindowImplementation );
	m_pWindowImplementation->Resize( fNewWidth, fNewHeight );
}

bool CWindow::IsOpen() const
{
	assert( m_pWindowImplementation );
	return m_pWindowImplementation->IsOpen();
}

CWindowImplementation& CWindow::GetImplementation() const
{ 
	assert( m_pWindowImplementation );
	return *m_pWindowImplementation; 
}

void CWindow::Push( CMessage& rMessage )
{
	assert( rMessage.GetType() == FRAME_OPEN_MESSAGE );
	if( IsOpen() )
	{
		Draw();
	}
}

const i8* CWindow::GetName() const
{
	assert( m_pWindowImplementation );
	return m_pWindowImplementation->GetName();
}

u32 CWindow::GetDrawMessage() const
{
	assert( m_pWindowImplementation );
	return m_pWindowImplementation->GetDrawMessage();
}

u32 CWindow::GetDraw2DMessage() const
{
	assert( m_pWindowImplementation );
	return m_pWindowImplementation->GetDraw2DMessage();
}

u64 CWindow::GetWindowUID() const
{
	assert( m_pWindowImplementation );
	return m_pWindowImplementation->GetWindowUID();
}

void CWindow::Activate()
{
	assert( m_pWindowImplementation );
	m_pWindowImplementation->Activate();
}

void CWindow::Show()
{
	assert( m_pWindowImplementation );
	m_pWindowImplementation->Show();
}

void CWindow::SetDirty()
{
	assert( m_pWindowImplementation );
	m_pWindowImplementation->SetDirty();
}

CWindow::CWindow()	
{
}
