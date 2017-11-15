#ifndef WINDOW_H
#define WINDOW_H

#include "Common/Types.h"
#include "Colored 2D Rectangle/Colored2DRectangle.h"
#include "Messenger/Message.h"

class CWindowImplementation;

class CWindow
{
private:
	static CWindow*		ms_pDefaultWindow;
	static const u32	ms_kuWindowResizeMessageUID = 0xB8924FDA;
	static const u32	ms_kuWindowClosedMessageUID = 0xFBB2374A;
	static const u32	ms_kuWindowDestroyedMessageUID = 0x3E3F3064;

public:
	static void		SetDefaultWindow( CWindow* pWindow );
	static CWindow*	GetDefaultWindow()				{ return ms_pDefaultWindow; }
	static u32		GetWindowResizeMessageUID()		{ return ms_kuWindowResizeMessageUID; }
	static u32		GetWindowClosedMessageUID()		{ return ms_kuWindowClosedMessageUID; }
	static u32		GetWindowDestroyedMessageUID()	{ return ms_kuWindowDestroyedMessageUID; }

public:
							CWindow( const i8* kpWindowName, i32 iX, i32 iY, 
								f32 fWidth, f32 fHeight, bool bFullscreen );
	virtual					~CWindow();
	virtual void			Draw() const;
	virtual void			Draw2D() const;
	f32						GetWidth() const;
	f32 					GetHeight() const;
	virtual void			Resize( f32 fNewWidth, f32 fNewHeight );
	virtual bool			IsOpen() const;
	CWindowImplementation&	GetImplementation() const;
	virtual void			Push( CMessage& rMessage );
	virtual const i8*		GetName() const;
	u32						GetDrawMessage() const;
	u32						GetDraw2DMessage() const;
	u64						GetWindowUID() const;
	void					Activate();
	void					Show();
	void					SetDirty();
	
private:
	CWindow();

private:
	CWindowImplementation*		m_pWindowImplementation;
};

#endif