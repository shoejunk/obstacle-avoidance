#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Common/Types.h"

class CDynamicArray
{
public:
			CDynamicArray( u16 uStartingAllocation );
	u16		GetSize() const;
	void	Clear()	{ m_uSize = 0; }

protected:
	u16		GetAllocated() const			{ return m_uAllocated; }
	void	SetAllocated( u16 uAllocated )	{ m_uAllocated = uAllocated; }
	void	SetSize( u16 uSize )			{ m_uSize = uSize; }

private:
	u16	m_uAllocated;
	u16	m_uSize;
};

template< typename Type >
class TDynamicArray : public CDynamicArray
{
public:
				TDynamicArray( u16 uStartingAllocation, Type oNull );
				~TDynamicArray();
	Type&		operator[]( u16 uIndex );
	const Type&	operator[]( u16 uIndex ) const;
	u16			Add( const Type& krData );
	void		RemoveByIndex( u16 uIndex );
	void		Remove( const Type& krData );
	i32			Find( const Type& krData ) const;

private:
	Type*	m_pArray;
	Type	m_oNull;
};

#endif
