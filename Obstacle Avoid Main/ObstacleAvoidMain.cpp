#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <time.h>
#include "Window/Window.h"
#include "Input/Input.h"
#include "Windows Input/WindowsInputListener.h"
#include "Windows Input/WindowsInputMessage.h"
#include "Circle Bot/CircleBot.h"
#include "Obstacle Creator/ObstacleCreator.h"
#include "Handle/Handle.h"

i32 WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, i32 )
{
	// Setup the global handle factory
	CHandleFactory::CreateGlobalHandleFactory();

	// Setup the message variable:
	MSG oMessage;
	PeekMessage( &oMessage, NULL, 0, 0, PM_REMOVE );

	// Create everything else within a scope to ensure that handle factory is destroyed last
	{
		// Create the main application window and set it as the default window:
		CWindow oApplicationWindow( "Application", 0, 0, 680, 680, false );
		oApplicationWindow.Show();
		CWindow::SetDefaultWindow( &oApplicationWindow );

		// Create the application window input listener:
		CInput oApplicationInput;
		CWindowsInputListener oApplicationWindowsInputListener( &oApplicationInput,
			oApplicationWindow );

		// Set up the frame open message:
		CMessage oFrameOpenMessage( FRAME_OPEN_MESSAGE );

		// Create the circle bot:
		CCircleBot oCircleBot( 0.15f, 0.5f, 0.85f, 0.5f );

		// Create an obstacle:
		CObstacleCreator oObstacleCreator;

		// Game loop:
		do
		{
			oApplicationWindow.SetDirty();
			CF32Vector oForce( oObstacleCreator.CalculateForce(
				oCircleBot.GetPosition(), oCircleBot.GetRadius() ) );
			oCircleBot.ApplyForce( oForce );
			CMessenger::GlobalPush( oFrameOpenMessage );
			CObstacle* pCollision( oObstacleCreator.CollideObstaclesWithCircle(
				oCircleBot.GetPosition().X(), oCircleBot.GetPosition().Y(),
				oCircleBot.GetRadius() ) );
			if( pCollision )
			{
				f32 fCollisionAmount( -(pCollision->GetPosition().GetDistance(
					oCircleBot.GetPosition() ) - pCollision->GetRadius() -
					oCircleBot.GetRadius()) );
				assert( fCollisionAmount > 0.f );
				oCircleBot.Collide( fCollisionAmount, pCollision->GetPosition() );
			}
			if( PeekMessage( &oMessage, NULL, 0, 0, PM_REMOVE ) )
			{
				TranslateMessage( &oMessage );
				DispatchMessage( &oMessage );
			}
		} while( !oApplicationWindowsInputListener.IsButtonDown( VK_ESCAPE ) && !oApplicationWindowsInputListener.IsButtonDown( 0 ) );

		CMessenger::GlobalStopListening( oApplicationWindowsInputListener,
			CWindowsInputMessage::GetWindowsInputMessageType() );
	}

	CHandleFactory::DestroyGlobalHandleFactory();
	return( oMessage.wParam );
}
