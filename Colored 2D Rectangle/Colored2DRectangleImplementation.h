#ifndef COLORED2DRECTANGLEIMPLEMENTATION_H
#define COLORED2DRECTANGLEIMPLEMENTATION_H

#include "Colored 2D Rectangle/Colored2DRectangle.h"

class CColored2DRectangleImplementation
{
public:
					CColored2DRectangleImplementation( 
						const CColored2DRectangle& krRectangle );
	virtual void	Draw() const = 0;

protected:
	const CColored2DRectangle&	GetColored2DRectangle() const	{ return m_krRectangle; }

private:
	const CColored2DRectangleImplementation&	operator=( const 
													CColored2DRectangleImplementation& );

	const CColored2DRectangle&	m_krRectangle;
};

namespace NColored2DRectangle
{
	CColored2DRectangleImplementation*	ImplementColored2DRectangle( 
											const CColored2DRectangle& krRectangle );
}

	#endif
