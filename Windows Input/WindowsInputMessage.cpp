#include "WindowsInputMessage.h"

u32 CWindowsInputMessage::GetWindowsInputMessageType()
{
	return ms_kuWindowsInputMessageType;
}

CWindowsInputMessage::CWindowsInputMessage( CWindow* pWindow, u32 uMessage, 
	WPARAM oParameter1, LPARAM oParameter2 )
	: CMessage( ms_kuWindowsInputMessageType )
	, m_pWindow( pWindow )
	, m_uMessage( uMessage )
	, m_oParameter1( oParameter1 )
	, m_oParameter2( oParameter2 )
{
}

CWindow* CWindowsInputMessage::GetWindow() const
{
	return m_pWindow;
}

u32 CWindowsInputMessage::GetMessage() const
{
	return m_uMessage;
}

WPARAM CWindowsInputMessage::GetParameter1() const
{
	return m_oParameter1;
}

LPARAM CWindowsInputMessage::GetParameter2() const
{
	return m_oParameter2;
}

CWindowsInputMessage::CWindowsInputMessage()
	: CMessage( ms_kuWindowsInputMessageType )
{
}
