#ifndef MOUSEMESSAGE_H
#define MOUSEMESSAGE_H

#include "../Messenger/Message.h"

class CMouseMessage : public CMessage
{
public:
	enum EMouseAction
	{
		LEFT_BUTTON_DOWN,
		MIDDLE_BUTTON_DOWN,
		RIGHT_BUTTON_DOWN,
		LEFT_BUTTON_UP,
		MIDDLE_BUTTON_UP,
		RIGHT_BUTTON_UP,
		LEFT_BUTTON_DOUBLE_CLICK,
		RIGHT_BUTTON_DOUBLE_CLICK,
		DRAG,
		LOSE_CONTROL,
	};

	static u32	GetMouseMessageUID();

private:
	static const u32	ms_kuMouseMessageUID = 44953;

public:
					CMouseMessage( EMouseAction eMouseAction, u32 uX, u32 uY,
						f32 fNormalX, f32 fNormalY );
	EMouseAction	GetMouseAction() const;
	u32				X() const;
	u32				Y() const;
	f32				GetNormalX() const	{ return m_fNormalX; }
	f32				GetNormalY() const	{ return m_fNormalY; }

private:
	EMouseAction	m_eMouseAction;
	u32				m_uX;
	u32				m_uY;
	f32				m_fNormalX;
	f32				m_fNormalY;
};

#endif
