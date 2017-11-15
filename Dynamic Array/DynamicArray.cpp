#include "DynamicArray.h"

CDynamicArray::CDynamicArray( u16 uStartingAllocation )
	: m_uAllocated( uStartingAllocation )
	, m_uSize( 0 )
{
}

u16 CDynamicArray::GetSize() const
{
	return m_uSize;
}
