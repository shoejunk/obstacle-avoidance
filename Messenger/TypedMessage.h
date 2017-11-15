#ifndef TYPEDMESSAGE_H
#define TYPEDMESSAGE_H

#include "../Messenger/Message.h"

template< class CType >
class TTypedMessage : public CMessage
{
public:
			TTypedMessage( u32 uType, CType oData );
	CType	GetData() const	{ return m_oData; }

private:
	CType	m_oData;
};

template< typename CType >
TTypedMessage< CType >::TTypedMessage( u32 uType, CType oData ) 
	: CMessage( uType )
	, m_oData( oData ) 
{}

#endif
