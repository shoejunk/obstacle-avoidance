#ifndef LISTENER_H
#define LISTENER_H

#include "Message.h"

class CMessenger;

class CListener
{
public:
	virtual			~CListener();
	virtual void	Push( CMessage& )						{}
	virtual void	Push( CMessage& rMessage, CMessenger& )	{ Push( rMessage ); }
};

#endif
