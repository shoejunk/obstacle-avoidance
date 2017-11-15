#ifndef WINDOWSINPUTMESSAGE_H
#define WINDOWSINPUTMESSAGE_H

#include "Windows.h"
#include "../Common/Types.h"
#include "../Messenger/Message.h"
#include "../Window/Window.h"

class CWindowsInputMessage : public CMessage
{
public:
	static u32	GetWindowsInputMessageType();
				CWindowsInputMessage( CWindow* pWindow, u32 uMessage, 
					WPARAM oParameter1, LPARAM oParameter2 );

	CWindow*	GetWindow() const;
	u32			GetMessage() const;
	WPARAM		GetParameter1() const;
	LPARAM		GetParameter2() const;

private:
						CWindowsInputMessage();

	static const u32	ms_kuWindowsInputMessageType = 0x77C4A918;

	CWindow*			m_pWindow;
	u32					m_uMessage;
	WPARAM				m_oParameter1;
	LPARAM				m_oParameter2;
};

#endif