#include "LinkedListNode.inl"

template< class DataType >
TLinkedList< DataType >::TLinkedList()
	: m_pHead( NULL )
	, m_pIteratorList( NULL )
{
}

template< class DataType >
TLinkedList< DataType >::~TLinkedList()
{
	// Delete all iterators and nodes:
	TLinkedListIterator< DataType >* pIterator( m_pIteratorList );
	while( pIterator )
	{
		TLinkedListIterator< DataType >* pNext( pIterator->m_pNextIterator );
		delete pIterator;
		pIterator = pNext;
	}
	TLinkedListNode< DataType >* pNode( m_pHead );
	while( pNode )
	{
		TLinkedListNode< DataType >* pNext( pNode->GetNext() );
		delete pNode;
		pNode = pNext;
	}
}

template< class DataType >
TLinkedListIterator< DataType >* TLinkedList< DataType >::GetIterator()
{
	if( m_pIteratorList )
	{
		TLinkedListIterator< DataType >* pIterator( m_pIteratorList );
		while( pIterator->m_pNextIterator )
		{
			pIterator = pIterator->m_pNextIterator;
		}
		pIterator->m_pNextIterator = new TLinkedListIterator< DataType >( *this );
		return pIterator->m_pNextIterator;
	}
	else
	{
		m_pIteratorList = new TLinkedListIterator< DataType >( *this );
		return m_pIteratorList;
	}
}

template< class DataType >
void TLinkedList< DataType >::ReleaseIterator( TLinkedListIterator< DataType >&	rIterator )
{
	TLinkedListIterator< DataType >* pNext( rIterator.m_pNextIterator );
	if( m_pIteratorList == &rIterator )
	{
		delete m_pIteratorList;
		m_pIteratorList = pNext;
		return;
	}
	TLinkedListIterator< DataType >* pPrevious( m_pIteratorList );
	assert( pPrevious->m_pNextIterator );
	while( pPrevious->m_pNextIterator != &rIterator )
	{
		pPrevious = pPrevious->m_pNextIterator;
		assert( pPrevious->m_pNextIterator );
	}
	delete &rIterator;
	pPrevious->m_pNextIterator = pNext;
}

template< class DataType >
void TLinkedList< DataType >::ClearList()
{
	TLinkedListIterator< DataType >* pIterator( m_pIteratorList );
	while( pIterator )
	{
		pIterator->m_pCurrentNode = NULL;
		pIterator = pIterator->m_pNextIterator;
	}
	TLinkedListNode< DataType >* pNode( m_pHead );
	while( pNode )
	{
		TLinkedListNode< DataType >* pNext( pNode->GetNext() );
		delete pNode;
		pNode = pNext;
	}
	m_pHead = NULL;
	assert( !IsCircular() );
}

template< class DataType >
void TLinkedList< DataType >::AddFront( DataType oData )
{
	if( m_pHead )
	{
		TLinkedListNode< DataType >* pNext( m_pHead );
		m_pHead = new TLinkedListNode< DataType >( oData );
		m_pHead->m_pNext = pNext;
		return;
	}
	m_pHead = new TLinkedListNode< DataType >( oData );
}

template< class DataType >
bool TLinkedList< DataType >::IsInList( const DataType& krData ) const
{
	TLinkedListNode< DataType >* pNode( m_pHead );
	while( pNode )
	{
		if( pNode->GetData() == krData )
		{
			return true;
		}
		pNode = pNode->GetNext();
	}
	return false;
}

// Delete the first node of any data in the list that is equal to the given data.
// Assert if the data is not in the list:
template< class DataType >
void TLinkedList< DataType >::Remove( DataType oData )
{
	TLinkedListNode< DataType >* pNode( m_pHead );
	while( pNode )
	{
		if( pNode->GetData() == oData )
		{
			Delete( pNode );
			return;
		}
		pNode = pNode->GetNext();
	}
	assert( false );
}

template< class DataType >
void TLinkedList< DataType >::UpdateIteratorsAboutDeletedNode( 
	TLinkedListNode< DataType >* pNode )
{
	assert( pNode );
	TLinkedListIterator< DataType >* pIterator( m_pIteratorList );
	while( pIterator )
	{
		if( pIterator->m_pCurrentNode == pNode )
		{
			pIterator->m_pCurrentNode = pNode->GetNext();
		}
		pIterator = pIterator->m_pNextIterator;
	}
}

template< class DataType >
void TLinkedList< DataType >::Delete( TLinkedListNode< DataType >* pNode )
{
	assert( pNode );
	UpdateIteratorsAboutDeletedNode( pNode );
	TLinkedListNode< DataType >* pNext( pNode->GetNext() );
	if( m_pHead == pNode )
	{
		delete m_pHead;
		m_pHead = pNext;
		return;
	}
	TLinkedListNode< DataType >* pPrevious( m_pHead );
	assert( pPrevious->GetNext() );
	while( pPrevious->GetNext() != pNode )
	{
		pPrevious = pPrevious->GetNext();
		assert( pPrevious->GetNext() );
	}
	pPrevious->DeleteNext();
}

template< class DataType >
void TLinkedList< DataType >::DeleteNext( TLinkedListNode< DataType >* pNode )
{
	assert( pNode && pNode->GetNext() );
	UpdateIteratorsAboutDeletedNode( pNode->GetNext() );
	pNode->DeleteNext();
}

template< class DataType >
bool TLinkedList< DataType >::IsCircular()
{
	if( !m_pHead || !m_pHead->GetNext() )
	{
		return false;
	}
	TLinkedListNode< DataType >* pNode( m_pHead->GetNext() );
	TLinkedListNode< DataType >* pPrevious( m_pHead );
	TLinkedListNode< DataType >* pNext;
	while( pNode )
	{
		if( pNode == m_pHead )
		{
			return true;
		}
		pNext = pNode->m_pNext;
		pNode->m_pNext = pPrevious;
		pPrevious = pNode;
		pNode = pNext;
	}
	pNode = pPrevious;
	pPrevious = NULL;
	while( pNode != m_pHead )
	{
		pNext = pNode->m_pNext;
		pNode->m_pNext = pPrevious;
		pPrevious = pNode;
		pNode = pNext;
	}
	return false;
}

