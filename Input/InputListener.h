#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include "../Messenger/Listener.h"
#include "Input.h"

#include <assert.h>

class CInputListener : public CListener
{
public:
					CInputListener( CInput* pInput );
	virtual			~CInputListener()					{}
	virtual void	Push( CMessage& rMessage ) = 0;
	bool			IsButtonDown( u32 uButton ) const;

protected:
	void			SetButton( u32 uButton, bool bDown );
	void			SetAnalog( u32 uAnalog, f32 fValue ); 

private:
					CInputListener()					{}

	CInput*			m_pInput;
};

#endif