#include "WindowImplementation.h"
#include "Messenger/Messenger.h"
#include "Window/Window.h"

CWindowImplementation::CWindowImplementation( f32 fWidth, f32 fHeight, bool bFullscreen,
	CWindow& rWindow )
	: m_fWidth( fWidth )
	, m_fHeight( fHeight )
	, m_bFullscreen( bFullscreen )
	, m_rWindow( rWindow )
	, m_uDrawMessage( NUtilities::RandomU32() )
	, m_uDraw2DMessage( NUtilities::RandomU32() )
{
}

void CWindowImplementation::Draw() const
{
	CMessage oDrawMessage( m_uDrawMessage );
	CMessenger::GlobalPush( oDrawMessage );
}

void CWindowImplementation::Draw2D() const
{
	CMessage oDrawMessage( m_uDraw2DMessage );
	CMessenger::GlobalPush( oDrawMessage );
}

f32	CWindowImplementation::GetWidth() const
{
	return m_fWidth;
}

f32 CWindowImplementation::GetHeight() const
{
	return m_fHeight;
}

void CWindowImplementation::Resize( f32 fNewWidth, f32 fNewHeight )
{
	assert( fNewWidth >= 0.f && fNewHeight >= 0.f );
	m_fWidth = fNewWidth;
	m_fHeight = fNewHeight;
}

bool CWindowImplementation::IsFullscreen() const
{
	return m_bFullscreen;
}

CWindowImplementation& CWindowImplementation::operator=( const CWindowImplementation& )
{
	assert( false );
	return *this;
}
