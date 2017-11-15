#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

#include <assert.h>
#include "LinkedListIterator.h"

template< class DataType >
class TLinkedListNode
{
private:
									TLinkedListNode()	{ assert( false ); }
									TLinkedListNode( DataType oData );
	void							InsertAfter( DataType oData );
	TLinkedListNode< DataType >*	GetNext() const;
	DataType&						GetData();
	void							DeleteNext();

	DataType						m_oData;
	TLinkedListNode< DataType >*	m_pNext;

	friend class TLinkedListIterator< DataType >;
	friend class TLinkedList< DataType >;
};

#endif
