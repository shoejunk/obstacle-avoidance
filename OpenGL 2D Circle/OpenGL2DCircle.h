#ifndef OPENGL2DCIRCLE
#define OPENGL2DCIRCLE

#include "Common/Types.h"
#include "Vector/Vector.h"
#include "Visible/Visible.h"

class CWindow;

class COpenGL2DCircle : public CVisible
{
public:
						COpenGL2DCircle();
						COpenGL2DCircle( f32 fX, f32 fY, f32 fRadius, 
							f32 fRed, f32 fGreen, f32 fBlue );
	void				Set( f32 fX, f32 fY, f32 fRadius, f32 fRed, f32 fGreen,
							f32 fBlue );
	virtual void		Draw() const;
	f32					GetRadius() const			{ return m_fRadius; }
	const CF32Vector&	GetPositionConst() const;
	CF32Vector&			GetPosition();
	void				SetRadius( f32 fRadius )	{ m_fRadius = fRadius; }
	void				SetColor( f32 fRed, f32 fGreen, f32 fBlue );

private:
	f32			m_fRadius;
	CF32Vector	m_oPosition;
	f32			m_fRed;
	f32			m_fGreen;
	f32			m_fBlue;
};

#endif
