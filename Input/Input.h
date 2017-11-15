#ifndef INPUT_H
#define INPUT_H

#include "../Messenger/Messenger.h"

class CInputListener;

class CInput
{
public:
	static u32		GetMaxNumButtons();
	static u32		GetMaxNumAnalogs();
	static u32		GetButtonMessageType();
	static u32		GetAnalogMessageType();

					CInput();
					~CInput();
	bool			IsButtonDown( u32 uButton ) const;
	f32				GetAnalogState( u32 uAnalog ) const;

private:
	void			SetButton( u32 uButton, bool bDown );
	void			SetAnalog( u32 uAnalog, f32 fValue ); 

	static const u32	ms_kuMaxNumButtons = 1000;
	static const u32	ms_kuMaxNumAnalogs = 100;
	static const u32	ms_kuButtonMessageType = 4546;
	static const u32	ms_kuAnalogMessageType = 3985;

	bool				m_akButtonList[ ms_kuMaxNumButtons ];
	f32					m_akAnalogList[ ms_kuMaxNumAnalogs ];

	friend class CInputListener;
};

#endif