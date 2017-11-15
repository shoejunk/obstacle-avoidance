#include "WindowsOpenGlWindowHandler.h"
#include "../Window/Window.h"

CWindowsOpenGlWindowHandler::CWindowsOpenGlWindowHandler()
{
}

CWindowsOpenGlWindowHandler::~CWindowsOpenGlWindowHandler()
{
}

void CWindowsOpenGlWindowHandler::Draw()
{
	for( u32 i( 0 ); i < GetNumWindows(); ++i )
	{
		GetWindow( i )->Draw();
	}
}
