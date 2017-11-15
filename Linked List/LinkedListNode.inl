template< class DataType >
TLinkedListNode< DataType >::TLinkedListNode( DataType oData )
	: m_oData( oData )
	, m_pNext( NULL )
{
}

template< class DataType >
void TLinkedListNode< DataType >::InsertAfter( DataType oData )
{
	TLinkedListNode< DataType >* pNext( m_pNext );
	m_pNext = new TLinkedListNode< DataType >( oData );
	assert( m_pNext );
	m_pNext->m_pNext = pNext;
}

template< class DataType >
TLinkedListNode< DataType >* TLinkedListNode< DataType >::GetNext() const
{
	return m_pNext;
}

template< class DataType >
DataType& TLinkedListNode< DataType >::GetData()
{
	return m_oData;
}

template< class DataType >
void TLinkedListNode< DataType >::DeleteNext()
{
	assert( m_pNext );
	TLinkedListNode< DataType >* pNext( m_pNext->m_pNext );
	delete m_pNext;
	m_pNext = pNext;
}
