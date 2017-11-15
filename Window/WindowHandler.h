#include "../Common/Types.h"

class CWindow;

class CWindowHandler
{
public:
				
				CWindowHandler();
				~CWindowHandler();
	void		AddWindow( CWindow* pWindow );
	void		RemoveWindow( CWindow* pWindow );

protected:
	CWindow*	GetWindow( u32 uWindowIndex );
	u32			GetNumWindows() const;

private:
	static const u32	ms_kuMaxWindows = 10;

	CWindow*	m_aWindowList[ ms_kuMaxWindows ];
	u32			m_uNumWindows;
};