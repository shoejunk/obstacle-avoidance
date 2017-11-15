#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <windows.h>
#include "Window/WindowImplementation.h"
#include "Hash Table/HashTable.h"
#include "WindowsCallback.h"

#include "Hash Table/HashTable.inl"

typedef THashTable< CWindowsCallback*, const CWindowsCallback*, HWND > CWindowsCallbackTable;

class CWindowsOpenGlWindow : public CWindowImplementation
{
public:
	static u32						GetMaxTitleSize();
	static CWindowsOpenGlWindow*	GetCurrentWindow()	{ return ms_pCurrentWindow; }
	static i32						GetNextChildWindowIdentifier();
	static void						SetCurrentWindow( CWindowsOpenGlWindow& rWindow );

public:
							CWindowsOpenGlWindow( const i8* pTitle, i32 iX, i32 iY, 
								f32 fWidth, f32 fHeight, bool bFullscreen, 
								CWindow& rWindow );
	virtual					~CWindowsOpenGlWindow();
	void					Terminate();
	virtual void			Draw() const;
	virtual bool			IsOpen() const;
	HWND					GetWindowHandle() const;
	HDC						GetDeviceContext() const	{ return m_oDeviceContext; }
	HINSTANCE				GetInstance() const			{ return m_oInstance; }
	virtual void			Resize( f32 fNewWidth, f32 fNewHeight );
	virtual const i8*		GetName() const;
	u64						GetWindowUID() const;
	virtual void			Activate();
	virtual void			Show();
	virtual void			SetDirty();

private:
	static LRESULT CALLBACK	GlobalWindowsCallback( HWND oThis, u32 uMessage, WPARAM oParameter1,
								LPARAM oParameter2 );

private:
			CWindowsOpenGlWindow();
	LRESULT	WindowsCallback( HWND, u32 uMessage, WPARAM, LPARAM );
	void	SetWindowHandle( HWND oWindowHandle );

private:
	static CWindowsOpenGlWindow*	ms_pCurrentWindow;
	static const i32				ms_kiBitsPerPixel = 24/*32*/;
	static const u32				ms_kuMaxTitleSize = 64;
	static i32						ms_iNextChildWindowIdentifier;
	static CWindowsCallbackTable	ms_oWindowsCallbackTable;

private:
	HINSTANCE			m_oInstance;
	WNDCLASS			m_oWindowClass;
	u32					m_uWindowStyle;
	u32					m_uWindowStyleExtended;
	HWND				m_oWindowHandle;
	HDC					m_oDeviceContext;
	HGLRC				m_oRenderingContext;
	i8					m_aTitle[ ms_kuMaxTitleSize + 1 ];
	bool				m_bIsTerminating;
	CWindowsCallback	m_oCallback;
};

#endif
