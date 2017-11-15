#include "DynamicArray.h"
#include <string.h>

template< typename Type >
TDynamicArray< Type >::TDynamicArray( u16 uStartingAllocation, Type oNull )
	: CDynamicArray( uStartingAllocation )
	, m_pArray( NULL )
	, m_oNull( oNull )
{
	if( uStartingAllocation > 0 )
	{
		m_pArray = new Type[ GetAllocated() ];
	}
}

template< typename Type >
TDynamicArray< Type >::~TDynamicArray()
{
	if( m_pArray )
	{
		delete[] m_pArray;
	}
}

template< typename Type >
Type& TDynamicArray< Type >::operator[]( u16 uIndex )
{
	if( uIndex >= GetAllocated() )
	{
		Type* pOld( m_pArray );
		u16 uOldAllocated( GetAllocated() );
		do
		{
			SetAllocated( ( GetAllocated() == 0 ? 2 : GetAllocated() * 2 ) );
		} while( uIndex >= GetAllocated() );
		m_pArray = new Type[ GetAllocated() ];
		if( pOld )
		{
			memcpy( m_pArray, pOld, uOldAllocated * sizeof( Type ) );
			delete[] pOld;
		}
	}
	if( uIndex >= GetSize() )
	{
		for( u16 i( GetSize() ); i <= uIndex; ++i )
		{
			m_pArray[ i ] = m_oNull;
		}
		SetSize( uIndex + 1 );
	}
	return m_pArray[ uIndex ];
}

template< typename Type >
const Type& TDynamicArray< Type >::operator[]( u16 uIndex ) const
{
	assert( uIndex < GetSize() );
	return m_pArray[ uIndex ];
}

template< typename Type >
u16 TDynamicArray< Type >::Add( const Type& krData )
{
	u16 uIndex( GetSize() );
	(*this)[ uIndex ] = krData;
	return uIndex;
}

template< typename Type >
void TDynamicArray< Type >::RemoveByIndex( u16 uIndex )
{
	SetSize( GetSize() - 1 );
	for( u16 i( uIndex ); i < GetSize(); ++i )
	{
		m_pArray[ i ] = m_pArray[ i + 1 ];
	}
}

template< typename Type >
void TDynamicArray< Type >::Remove( const Type& krData )
{
	for( u16 i( 0 ); i < GetSize(); )
	{
		if( krData == m_pArray[ i ] )
		{
			RemoveByIndex( i );
		}
		else
		{
			++i;
		}
	}
}

template< typename Type >
i32 TDynamicArray< Type >::Find( const Type& krData ) const
{
	for( u16 i( 0 ); i < GetSize(); ++i )
	{
		if( krData == m_pArray[ i ] )
		{
			return i;
		}
	}
	return -1;
}
