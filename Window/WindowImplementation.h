#ifndef WINDOWIMPLEMENTATION_H
#define WINDOWIMPLEMENTATION_H

#include "Common/Types.h"

#include <assert.h>

class CWindow;

class CWindowImplementation
{
public:
						CWindowImplementation( f32 fWidth, f32 fHeight, bool bFullscreen,
							CWindow& rWindow );
	virtual				~CWindowImplementation()	{}
	virtual void		Draw() const;
	virtual void		Draw2D() const;
	f32					GetWidth() const;
	f32 				GetHeight() const;
	virtual void		Resize( f32 fNewWidth, f32 fNewHeight );
	virtual bool		IsOpen() const = 0;
	virtual const i8*	GetName() const = 0;
	u32					GetDrawMessage() const		{ return m_uDrawMessage; }
	u32					GetDraw2DMessage() const	{ return m_uDraw2DMessage; }
	virtual u64			GetWindowUID() const = 0;
	virtual void		Terminate() = 0;
	virtual void		Activate() = 0;
	virtual void		Show() = 0;
	virtual void		SetDirty() = 0;
	CWindow&			GetWindow() const	{ return m_rWindow; }

protected:
	bool		IsFullscreen() const;

private:
	CWindowImplementation&	operator=( const CWindowImplementation& );

	f32			m_fWidth;
	f32			m_fHeight;
	bool		m_bFullscreen;
	CWindow&	m_rWindow;
	u32			m_uDrawMessage;
	u32			m_uDraw2DMessage;
};

namespace NWindow
{
	CWindowImplementation*	ImplementWindow( const i8* kpWindowName, i32 iX, i32 iY, 
								f32 fWidth, f32 fHeight, bool bFullscreen, 
								CWindow& rWindow );
}

#endif
