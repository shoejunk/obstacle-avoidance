#ifndef LINKEDLISTITERATOR_H
#define LINKEDLISTITERATOR_H

template< class DataType >
class TLinkedList;

template< class DataType >
class TLinkedListNode;

template< class DataType >
class TLinkedListIterator
{
public:
					TLinkedListIterator( TLinkedList< DataType >& rLinkedList );
	bool			HasData() const;
	bool			IsFirst() const;
	bool			IsLast() const;
	bool			IsListEmpty() const;
	bool			IsNext() const;
	DataType		Get() const;
	DataType&		GetReference() const;
	const DataType&	GetConstReference() const;
	void			GoToNext();
	void			GoToFirst();
	void			GoToEnd();
	void			AddToEndOfList( DataType oData );
	void			AddToStartOfList( DataType oData );
	void			InsertAfter( DataType oData );
	void			InsertBefore( DataType oData );
	void			DeleteCurrentNode();
	void			DeleteNextNode();

private:
	const TLinkedListIterator&	operator=( const TLinkedListIterator< DataType >& );

	TLinkedList< DataType >&			m_rLinkedList;
	TLinkedListNode< DataType >*		m_pCurrentNode;
	TLinkedListIterator< DataType >*	m_pNextIterator;

	friend class TLinkedList< DataType >;
};

#endif
