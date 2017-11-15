#include "Colored2DRectangle.h"
#include "Colored2DRectangleImplementation.h"

CColored2DRectangle::CColored2DRectangle()
	: m_pImplementation( NULL )
	, m_oColor( 0.f, 0.f, 0.f )
{
}

CColored2DRectangle::CColored2DRectangle( f32 fX, f32 fY, f32 fWidth, f32 fHeight,
	f32 fRed, f32 fGreen, f32 fBlue )
	: m_oRectangle( fWidth, fHeight )
	, m_oColor( fRed, fGreen, fBlue )
	, m_oPosition( fX, fY )
{
	m_pImplementation = 
		NColored2DRectangle::ImplementColored2DRectangle( *this );
}

CColored2DRectangle::~CColored2DRectangle()
{
	if( m_pImplementation )
	{
		delete m_pImplementation;
	}
}

void CColored2DRectangle::Initialize( f32 fX, f32 fY, f32 fWidth, f32 fHeight, 
	f32 fRed, f32 fGreen, f32 fBlue )
{
	assert( !m_pImplementation );
	m_oRectangle.SetWidth( fWidth );
	m_oRectangle.SetHeight( fHeight );
	m_oColor.RedGreenBlue( fRed, fGreen, fBlue );
	m_oPosition.XY( fX, fY );
	m_pImplementation = NColored2DRectangle::ImplementColored2DRectangle( *this );
}

void CColored2DRectangle::Set( f32 fX, f32 fY, f32 fWidth, f32 fHeight, 
	f32 fRed, f32 fGreen, f32 fBlue )
{
	m_oRectangle.SetWidth( fWidth );
	m_oRectangle.SetHeight( fHeight );
	m_oColor.RedGreenBlue( fRed, fGreen, fBlue );
	m_oPosition.XY( fX, fY );
}

void CColored2DRectangle::Draw() const
{
	assert( m_pImplementation );
	m_pImplementation->Draw();
}

void CColored2DRectangle::SetPosition( f32 fX, f32 fY )
{
	m_oPosition.XY( fX, fY );
}
