#ifndef VISIBLELISTENER_H
#define VISIBLELISTENER_H

#include "../Messenger/Listener.h"

class CVisible;

class CVisibleListener : public CListener
{
public:
					CVisibleListener( bool bIs2D = false );
					CVisibleListener( const CVisible& krVisible, bool bIs2D = false );
					~CVisibleListener();
	void			SetVisible( const CVisible& krVisible );
	virtual void	Push( const CMessage& krMessage );
	void			Hide();
	void			Show();
	bool			IsHidden();

private:
	CVisibleListener&	operator=( const CVisibleListener& );

	static const u32	ms_kuDrawMessageUID = 39843;
	static const u32	ms_kuDraw2DMessageUID = 0x3DD71328;

	const CVisible*		m_kpVisible;
	bool				m_bIs2D;
};

#endif
