#ifndef HASHTABLE_H
#define HASHTABLE_H

template< class DataType >
class TLinkedList;

template< class DataType >
class TLinkedListIterator;

template< class DataType, typename KeyType >
class THashEntry;

template< class DataType, class ConstDataType, typename KeyType >
class THashTable
{
public:
			THashTable( u16 uTableSize, DataType oNull );
			~THashTable();
	void	Store( KeyType uKey, DataType oData );
	u16		Retrieve( KeyType uKey, DataType* pArray, u16 uArraySize );
	void	Remove( KeyType uKey );
	void	RemovePair( KeyType uKey, ConstDataType kData );
	bool	IsPair( KeyType uKey, ConstDataType kData );
	bool	IsEmpty() const;

private:
	u16	Hash( KeyType uKey );

private:
	TLinkedList< THashEntry< DataType, KeyType > >*			m_pTable;
	TLinkedListIterator< THashEntry< DataType, KeyType > >**	m_pIterators;
	u16															m_uTableSize;
	DataType													m_oNull;
};

#endif