#ifndef LISTENERLATCH_H
#define LISTENERLATCH_H

#include "Listener.h"

class CListenerLatch: public CListener
{
public:
					CListenerLatch();
					CListenerLatch( u32 uMessage );
	virtual			~CListenerLatch();
	virtual void	Push( CMessage& rMessage );
	bool			IsOn() const;
	void			TurnOff();
	void			TurnOn();
	void			SetMessage( u32 uMessage );

private:
	bool			m_bOn;
	u32				m_uMessage;
};

#endif