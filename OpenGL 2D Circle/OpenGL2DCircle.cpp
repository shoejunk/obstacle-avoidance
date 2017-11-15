#include "OpenGL2DCircle.h"
#include "windows.h"
#include <gl\gl.h>
#include "Window/Window.h"

COpenGL2DCircle::COpenGL2DCircle()
	: CVisible()
	, m_fRadius( 1.f )
	, m_oPosition( 2 )
	, m_fRed( 1.f )
	, m_fGreen( 1.f )
	, m_fBlue( 1.f )
{
}

COpenGL2DCircle::COpenGL2DCircle( f32 fX, f32 fY, f32 fRadius, 
	f32 fRed, f32 fGreen, f32 fBlue )
	: CVisible()
	, m_fRadius( fRadius )
	, m_oPosition( fX, fY )
	, m_fRed( fRed )
	, m_fGreen( fGreen )
	, m_fBlue( fBlue )
{
}

void COpenGL2DCircle::Set( f32 fX, f32 fY, f32 fRadius, f32 fRed, f32 fGreen,
	f32 fBlue )
{
	m_fRadius = fRadius;
	m_oPosition.XY( fX, fY );
	m_fRed = fRed;
	m_fGreen = fGreen;
	m_fBlue = fBlue;
}

void COpenGL2DCircle::Draw() const
{	
	// Convert 0 - 1 to -1 - 1:
	f32 fX( ( m_oPosition.X() * 2.f ) - 1.f );
	f32 fY( ( m_oPosition.Y() * 2.f ) - 1.f );
	f32 fRadius( m_fRadius * 2.f );

	assert( CWindow::GetDefaultWindow() );
	f32 fAspectRatio( CWindow::GetDefaultWindow()->GetWidth() / CWindow::GetDefaultWindow()->GetHeight() );
	glColor3f( m_fRed, m_fGreen, m_fBlue );
	glBegin( GL_TRIANGLE_FAN );
		glVertex2f( fX, fY );
		for( f32 fAngle( 0 ); fAngle < 2 * PI; fAngle += 0.1f )
		{
			glVertex2f( fX + static_cast< GLfloat >( sin( fAngle ) ) * fRadius, 
				fY + ( static_cast< GLfloat >( cos( fAngle ) ) * fRadius * fAspectRatio ) );
		}
		glVertex2f( fX, fY + ( fRadius * fAspectRatio ) );
	glEnd();
}

const CF32Vector& COpenGL2DCircle::GetPositionConst() const
{
	assert( m_oPosition.GetNumDimensions() == 2 );
	return m_oPosition;
}

CF32Vector& COpenGL2DCircle::GetPosition()
{
	assert( m_oPosition.GetNumDimensions() == 2 );
	return m_oPosition;
}

void COpenGL2DCircle::SetColor( f32 fRed, f32 fGreen, f32 fBlue )
{
	m_fRed = fRed;
	m_fGreen = fGreen;
	m_fBlue = fBlue;
}
