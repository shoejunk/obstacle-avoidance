#include <assert.h>
#include "Common/Types.h"
#include "Common/Utilities.h"
#include "Linked List/LinkedList.h"
#include "Linked List/LinkedListIterator.h"
#include "HashEntry.h"

#include "Linked List/LinkedList.inl"
#include "Linked List/LinkedListIterator.inl"
#include "HashEntry.inl"

template< typename DataType, class ConstDataType, typename KeyType >
THashTable< DataType, ConstDataType, KeyType >::THashTable( u16 uTableSize, DataType oNull )
	: m_pTable( new TLinkedList< THashEntry< DataType, KeyType > >[ uTableSize ] )
	, m_pIterators( new TLinkedListIterator< THashEntry< DataType, KeyType > >*[ uTableSize ] )
	, m_uTableSize( uTableSize )
	, m_oNull( oNull )
{
	assert( m_pTable && m_uTableSize > 0 );
	for( u16 i( 0 ); i < uTableSize; ++i )
	{
		m_pIterators[ i ] = m_pTable[ i ].GetIterator();
	}
}

template< class DataType, class ConstDataType, typename KeyType >
THashTable< DataType, ConstDataType, KeyType >::~THashTable()
{
	assert( m_pTable );
	for( u16 i( 0 ); i < m_uTableSize; ++i )
	{
		assert( m_pIterators[ i ] );
		m_pTable[ i ].ReleaseIterator( *m_pIterators[ i ] );
	}
	delete[] m_pTable;
	delete[] m_pIterators;
}

template< class DataType, class ConstDataType, typename KeyType >
void THashTable< DataType, ConstDataType, KeyType >::Store( KeyType uKey, DataType oData )
{
	assert( m_pTable );
	m_pTable[ Hash( uKey ) ].AddFront( THashEntry< DataType, KeyType >( uKey, oData ) );
}

template< class DataType, class ConstDataType, typename KeyType >
u16 THashTable< DataType, ConstDataType, KeyType >::Retrieve( KeyType uKey, DataType* pArray, 
	u16 uArraySize )
{
	assert( m_pIterators );
	u16 uIndex( Hash( uKey ) );
	TLinkedListIterator< THashEntry< DataType, KeyType > >* pIterator( m_pIterators[ uIndex ] );
	assert( pIterator );
	pIterator->GoToFirst();
	u16 uCount( 0 );
	for( ; pIterator->HasData(); pIterator->GoToNext() )
	{
		const THashEntry< DataType, KeyType >& krEntry( pIterator->GetConstReference() );
		if( krEntry.DoesMatch( uKey ) )
		{
			if( uCount < uArraySize )
			{
				pArray[ uCount ] = krEntry.GetData();
			}
			++uCount;
		}
	}
	return uCount;
}

template< class DataType, class ConstDataType, typename KeyType >
void THashTable< DataType, ConstDataType, KeyType >::Remove( KeyType uKey )
{
	assert( m_pIterators );
	u16 uIndex( Hash( uKey ) );
	TLinkedListIterator< THashEntry< DataType, KeyType > >* pIterator( m_pIterators[ uIndex ] );
	assert( pIterator );
	pIterator->GoToFirst();
	while( pIterator->HasData() )
	{
		const THashEntry< DataType, KeyType >& krEntry( pIterator->GetConstReference() );
		if( krEntry.DoesMatch( uKey ) )
		{
			pIterator->DeleteCurrentNode();
		}
		else
		{
			pIterator->GoToNext();
		}
	}
}

template< class DataType, class ConstDataType, typename KeyType >
void THashTable< DataType, ConstDataType, KeyType >::RemovePair( KeyType uKey, ConstDataType kData )
{
	assert( m_pIterators );
	u16 uIndex( Hash( uKey ) );
	TLinkedListIterator< THashEntry< DataType, KeyType > >* pIterator( m_pIterators[ uIndex ] );
	assert( pIterator );
	pIterator->GoToFirst();
	while( pIterator->HasData() )
	{
		const THashEntry< DataType, KeyType >& krEntry( pIterator->GetConstReference() );
		if( krEntry.DoesMatch( uKey ) && krEntry.GetData() == kData )
		{
			pIterator->DeleteCurrentNode();
		}
		else
		{
			pIterator->GoToNext();
		}
	}
}

template< class DataType, class ConstDataType, typename KeyType >
bool THashTable< DataType, ConstDataType, KeyType >::IsPair( KeyType uKey, ConstDataType kData )
{
	assert( m_pIterators );
	u16 uIndex( Hash( uKey ) );
	TLinkedListIterator< THashEntry< DataType, KeyType > >* pIterator( m_pIterators[ uIndex ] );
	assert( pIterator );
	pIterator->GoToFirst();
	bool bReturn( false );
	while( pIterator->HasData() )
	{
		const THashEntry< DataType, KeyType >& krEntry( pIterator->GetConstReference() );
		if( krEntry.DoesMatch( uKey ) && krEntry.GetData() == kData )
		{
			bReturn = true;
			break;
		}
		pIterator->GoToNext();
	}
	return bReturn;
}

template< typename DataType, class ConstDataType, typename KeyType >
bool THashTable< DataType, ConstDataType, KeyType >::IsEmpty() const
{
	assert( m_pIterators );
	for( u16 i( 0 ); i < m_uTableSize; ++i )
	{
		TLinkedListIterator< THashEntry< DataType, KeyType > >* pIterator( m_pIterators[ i ] );
		assert( pIterator );
		if( !pIterator->IsListEmpty() )
		{
			return false;
		}
	}
	return true;
}

template< typename DataType, class ConstDataType, typename KeyType >
u16 THashTable< DataType, ConstDataType, KeyType >::Hash( KeyType uKey )
{
	return( NUtilities::MurmurHash2( &uKey, sizeof( KeyType ), 0xBC132EB9 ) % m_uTableSize );
}
