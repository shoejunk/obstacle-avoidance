#ifndef COLORED2DRECTANGLE_H
#define COLORED2DRECTANGLE_H

#include "Vector/Vector2.h"
#include "Color/Color.h"
#include "Rectangle/Rectangle.h"
#include "Visible/Visible.h"

class CColored2DRectangleImplementation;

class CColored2DRectangle : public CVisible
{
public:
						CColored2DRectangle();
						CColored2DRectangle( f32 fX, f32 fY, f32 fWidth, 
							f32 fHeight, f32 fRed, f32 fGreen, f32 fBlue );
	virtual				~CColored2DRectangle();
	void				Initialize( f32 fX, f32 fY, f32 fWidth, f32 fHeight, 
							f32 fRed, f32 fGreen, f32 fBlue );
	void				Set( f32 fX, f32 fY, f32 fWidth, f32 fHeight, 
							f32 fRed, f32 fGreen, f32 fBlue );
	virtual void		Draw() const;
	const CRectangle&	GetRectangle() const				{ return m_oRectangle; }
	const CColor&		GetColor() const					{ return m_oColor; }
	const CF32Vector2&	GetPosition() const					{ return m_oPosition; }
	void				SetColor( const CColor& krColor )	{ m_oColor = krColor; }
	void				X( f32 fX )							{ m_oPosition.X( fX ); }
	void				Y( f32 fY )							{ m_oPosition.Y( fY ); }
	f32					X() const							{ return m_oPosition.X(); }
	f32					Y() const							{ return m_oPosition.Y(); }
	f32					R() const							{ return m_oColor.R(); }
	f32					G() const							{ return m_oColor.G(); }
	f32					B() const							{ return m_oColor.B(); }
	void				R( f32 fR )							{ m_oColor.R( fR ); }
	void				G( f32 fG )							{ m_oColor.G( fG ); }
	void				B( f32 fB )							{ m_oColor.B( fB ); }
	void				SetPosition( f32 fX, f32 fY );

private:
	CRectangle							m_oRectangle;
	CColor								m_oColor;
	CF32Vector2							m_oPosition;
	CColored2DRectangleImplementation*	m_pImplementation;
};

#endif
