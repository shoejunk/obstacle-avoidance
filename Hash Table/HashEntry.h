#ifndef HASHENTRY_H
#define HASHENTRY_H

#include "../Common/Types.h"

template< typename DataType, typename KeyType >
class THashEntry
{
public:
				THashEntry( KeyType uKey, const DataType& krData );
	bool		DoesMatch( KeyType uKey ) const	{ return uKey == m_uKey; }
	DataType	GetData() const					{ return m_oData; }

private:
	KeyType		m_uKey;
	DataType	m_oData;
};

#endif