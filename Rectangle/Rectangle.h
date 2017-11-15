#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Common/Types.h"
#include "Vector/Vector.h"

class CRectangle
{
public:
			CRectangle();
			CRectangle( f32 fWidth, f32 fHeight );
	void	SetWidth( f32 fWidth );
	void	SetHeight( f32 fHeight );
	f32		GetWidth() const;
	f32		GetHeight() const;
	f32		GetHalfWidth() const;
	f32		GetHalfHeight() const;

private:
	CF32Vector	m_oHalfDimensions;
};

#endif
