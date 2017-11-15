template< class DataType >
TLinkedListIterator< DataType >::TLinkedListIterator( 
	TLinkedList< DataType >& rLinkedList )
	: m_rLinkedList( rLinkedList )
	, m_pCurrentNode( rLinkedList.m_pHead )
	, m_pNextIterator( NULL )
{
}

template< class DataType >
bool TLinkedListIterator< DataType >::HasData() const
{
	return m_pCurrentNode != NULL;
}

template< class DataType >
bool TLinkedListIterator< DataType >::IsFirst() const
{
	return m_rLinkedList.m_pHead == m_pCurrentNode;
}

template< class DataType >
bool TLinkedListIterator< DataType >::IsLast() const
{
	assert( m_pCurrentNode );
	return m_pCurrentNode->GetNext() == NULL;
}

template< class DataType >
bool TLinkedListIterator< DataType >::IsListEmpty() const
{
	return m_rLinkedList.m_pHead == NULL;
}

template< class DataType >
bool TLinkedListIterator< DataType >::IsNext() const
{
	assert( m_pCurrentNode );
	return m_pCurrentNode->GetNext() != NULL;
}

template< class DataType >
DataType TLinkedListIterator< DataType >::Get() const
{
	assert( m_pCurrentNode );
	return m_pCurrentNode->GetData();
}

template< class DataType >
DataType& TLinkedListIterator< DataType >::GetReference() const
{
	assert( m_pCurrentNode );
	return m_pCurrentNode->GetData();
}

template< class DataType >
const DataType& TLinkedListIterator< DataType >::GetConstReference() const
{
	assert( m_pCurrentNode );
	return m_pCurrentNode->GetData();
}

template< class DataType >
void TLinkedListIterator< DataType >::GoToNext()
{
	assert( m_pCurrentNode );
	m_pCurrentNode = m_pCurrentNode->GetNext();
}

template< class DataType >
void TLinkedListIterator< DataType >::GoToFirst()
{
	m_pCurrentNode = m_rLinkedList.m_pHead;
}

template< class DataType >
void TLinkedListIterator< DataType >::GoToEnd()
{
	assert( !m_rLinkedList.IsCircular() );
	if( !m_pCurrentNode )
	{
		if( !m_rLinkedList.m_pHead )
		{
			return;
		}
		m_pCurrentNode = m_rLinkedList.m_pHead;
	}
	while( m_pCurrentNode->GetNext() )
	{
		m_pCurrentNode = m_pCurrentNode->GetNext();
	}
}

template< class DataType >
void TLinkedListIterator< DataType >::AddToEndOfList( DataType oData )
{
	if( m_rLinkedList.m_pHead )
	{
		TLinkedListNode< DataType >* pNode;
		if( m_pCurrentNode )
		{
			pNode = m_pCurrentNode;
		}
		else
		{
			pNode = m_rLinkedList.m_pHead;
		}
		while( pNode->GetNext() )
		{
			pNode = pNode->GetNext();
		}
		pNode->InsertAfter( oData );
		assert( !m_rLinkedList.IsCircular() );
		return;
	}
	m_rLinkedList.m_pHead = new TLinkedListNode< DataType >( oData );
	m_pCurrentNode = m_rLinkedList.m_pHead;
}

template< class DataType >
void TLinkedListIterator< DataType >::AddToStartOfList( DataType oData )
{
	TLinkedListNode< DataType >* pNext( m_rLinkedList.m_pHead );
	m_rLinkedList.m_pHead = new TLinkedListNode< DataType >( oData );
	m_rLinkedList.m_pHead->m_pNext = pNext;
	assert( !m_rLinkedList.IsCircular() );
}

template< class DataType >
void TLinkedListIterator< DataType >::InsertAfter( DataType oData )
{
	assert( m_pCurrentNode );
	m_pCurrentNode->InsertAfter( oData );
	assert( !m_rLinkedList.IsCircular() );
}

template< class DataType >
void TLinkedListIterator< DataType >::InsertBefore( DataType oData )
{
	assert( m_pCurrentNode );
	if( m_pCurrentNode == m_rLinkedList.m_pHead )
	{
		m_rLinkedList.m_pHead = new TLinkedListNode< DataType >( oData );
		m_rLinkedList.m_pHead = m_pCurrentNode;
		assert( !m_rLinkedList.IsCircular() );
		return;
	}
	TLinkedListNode< DataType >* pNode( m_rLinkedList.m_pHead );
	assert( pNode->GetNext() );
	while( pNode->GetNext() != m_pCurrentNode )
	{
		pNode = pNode->GetNext();
		assert( pNode->GetNext() );
	}
	pNode->InsertAfter( oData );
	assert( !m_rLinkedList.IsCircular() );
}

template< class DataType >
void TLinkedListIterator< DataType >::DeleteCurrentNode()
{
	assert( m_pCurrentNode );
	m_rLinkedList.Delete( m_pCurrentNode );
}

template< class DataType >
void TLinkedListIterator< DataType >::DeleteNextNode()
{
	assert( m_pCurrentNode && m_pCurrentNode->GetNext() );
	m_rLinkedList.DeleteNext( m_pCurrentNode );
}

template< class DataType >
const TLinkedListIterator< DataType >& TLinkedListIterator< DataType >::operator=( 
	const TLinkedListIterator< DataType >& )
{
	assert( false );
	return *this;
}
