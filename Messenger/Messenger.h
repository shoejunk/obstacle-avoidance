#ifndef MESSENGER_H
#define MESSENGER_H

#include "Message.h"
#include "Listener.h"
//#include "Binary Tree/BinaryTree.h"
#include "Hash Table/HashTable.h"

typedef THashTable< CListener*, const CListener*, u32 > CListenerTable;

class CMessenger
{
private:
	static CMessenger	ms_oGlobalMessenger;
	static const u32	ms_kuTableSize = 500;
	static const u16	ms_kuMaxListenersPerMessage = 500;
	static const u32	ms_kuNewMessengerMessageUID = 0x628D0C60;
	static const u32	ms_kuDeleteMessengerMessageUID = 0x44044028;

public:
	static void			GlobalPush( CMessage& rMessage );
	static void			GlobalListen( CListener& rListener, u32 uMessageType );
	static void			GlobalStopListening( const CListener& krListener, 
							u32 uMessageType );
	static bool			GlobalIsListening( const CListener& krListener, 
							u32 uMessageType );
	static CMessenger&	GetGlobalMessenger()	{ return ms_oGlobalMessenger; }
	static u32			GetNewMessengerMessageUID()	
							{ return ms_kuNewMessengerMessageUID; }
	static u32			GetDeleteMessengerMessageUID()	
							{ return ms_kuDeleteMessengerMessageUID; }

public:
			CMessenger();
			~CMessenger();
	void	Push( CMessage& rMessage );
	void	Listen( CListener& krListener, u32 uMessageType );
	void	StopListening( const CListener& krListener, u32 uMessageType );
	bool	IsListening( const CListener& krListener, u32 uMessageType );

private:
	CListenerTable			m_oListenerTable;
};

#endif
