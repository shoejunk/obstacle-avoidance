#include "Colored2DRectangleImplementation.h"

CColored2DRectangleImplementation::CColored2DRectangleImplementation( 
	const CColored2DRectangle& krRectangle ) 
	: m_krRectangle( krRectangle )
{
}

const CColored2DRectangleImplementation& CColored2DRectangleImplementation::operator=( 
	const CColored2DRectangleImplementation& )
{ 
	assert( false );
	return *( NColored2DRectangle::ImplementColored2DRectangle( m_krRectangle ) );
}
