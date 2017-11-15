#include "Rectangle.h"
#include <assert.h>

CRectangle::CRectangle()
	: m_oHalfDimensions( 2 )
{
}

CRectangle::CRectangle( f32 fWidth, f32 fHeight )
	: m_oHalfDimensions( fWidth / 2, fHeight / 2 )
{
}

void CRectangle::SetWidth( f32 fWidth )
{
	assert( m_oHalfDimensions.GetNumDimensions() == 2 );
	m_oHalfDimensions.X( fWidth / 2 );
}

void CRectangle::SetHeight( f32 fHeight )
{
	assert( m_oHalfDimensions.GetNumDimensions() == 2 );
	m_oHalfDimensions.Y( fHeight / 2 );
}

f32 CRectangle::GetWidth() const
{
	assert( m_oHalfDimensions.GetNumDimensions() == 2 );
	return( m_oHalfDimensions.X() * 2 );
}

f32 CRectangle::GetHeight() const
{
	assert( m_oHalfDimensions.GetNumDimensions() == 2 );
	return( m_oHalfDimensions.Y() * 2 );
}

f32 CRectangle::GetHalfWidth() const
{
	assert( m_oHalfDimensions.GetNumDimensions() == 2 );
	return m_oHalfDimensions.X();
}

f32 CRectangle::GetHalfHeight() const
{
	assert( m_oHalfDimensions.GetNumDimensions() == 2 );
	return m_oHalfDimensions.Y();
}
