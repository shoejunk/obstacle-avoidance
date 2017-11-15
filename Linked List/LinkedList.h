#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedListNode.h"
#include "LinkedListIterator.h"

template< class DataType >
class TLinkedList
{
public:
										TLinkedList();
										~TLinkedList();
	TLinkedListIterator< DataType >*	GetIterator();
	void								ReleaseIterator( TLinkedListIterator< DataType >&
											rIterator );
	void								ClearList();
	void								AddFront( DataType oData );
	bool								IsInList( const DataType& krData ) const;
	void								Remove( DataType oData );

private:
	void	UpdateIteratorsAboutDeletedNode( TLinkedListNode< DataType >* pNode );
	void	Delete( TLinkedListNode< DataType >* pNode );
	void	DeleteNext( TLinkedListNode< DataType >* pNode );
	bool	IsCircular();

	TLinkedListNode< DataType >*		m_pHead;
	TLinkedListIterator< DataType >*	m_pIteratorList;

	friend class TLinkedListIterator< DataType >;
};

#endif
