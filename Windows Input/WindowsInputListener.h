#ifndef WINDOWSINPUTLISTENER_H
#define WINDOWSINPUTLISTENER_H

#include "../Input/InputListener.h"

class CWindow;

class CWindowsInputListener : public CInputListener
{
public:
					CWindowsInputListener( CInput* pInput, CWindow& rWindow );
	virtual			~CWindowsInputListener();
	virtual void	Push( CMessage& rMessage );

private:
							CWindowsInputListener();
	CWindowsInputListener&	operator=( const CWindowsInputListener& );

	static const u32	ms_kuLeftMouseDownMessageUID = 33928;

	CWindow&		m_rWindow;
};

#endif
