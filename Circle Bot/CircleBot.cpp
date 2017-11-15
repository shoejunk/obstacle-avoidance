#include "CircleBot.h"
#include <assert.h>
#include "Common/Utilities.h"
#include "Window/Window.h"
#include "Messenger/Messenger.h"
#include "Windows Input/MouseMessage.h"

#include "Dynamic Array/DynamicArray.inl"

const f32 CCircleBot::ms_kfSpeed = 0.1f;
const f32 CCircleBot::ms_kfMaxRotationSpeed = 0.05f;

CCircleBot::CCircleBot( f32 fStartX, f32 fStartY, f32 fDestinationX, 
	f32 fDestinationY )
	: m_oGeometry( fStartX, fStartY, 0.02f, 0.f, 0.f, 1.f )
	, m_oDestination( fDestinationX, fDestinationY, 0.02f, 0.f, 1.f, 0.f )
	, m_fStartX( fStartX )
	, m_fStartY( fStartY )
	, m_eState( NORMAL )
	, m_oExternalForce( 0.f, 0.f )
	, m_bStuck( false )
	, m_oInternalForces( 2, NULL )
	, m_oAnchorPosition( fStartX, fStartY )
	, m_fAnchorTimer( 0.2f )
{
	// Listen for frame open messages to update the bot:
	CMessenger::GlobalListen( *this, FRAME_OPEN_MESSAGE );

	// Listen for the mouse message to allow player to move bot and destination:
	CMessenger::GlobalListen( *this, CMouseMessage::GetMouseMessageUID() );

	// Listen for the 2D draw message:
	assert( CWindow::GetDefaultWindow() );
	CMessenger::GlobalListen( *this, CWindow::GetDefaultWindow()->GetDraw2DMessage() );

	// Start the timer:
	m_oMovementTimer.Start();
}

CCircleBot::~CCircleBot()
{
	// Stop listening for frame open messages to update the bot:
	CMessenger::GlobalStopListening( *this, FRAME_OPEN_MESSAGE );

	// Stop listening for the mouse message to allow player to move bot and destination:
	CMessenger::GlobalStopListening( *this, CMouseMessage::GetMouseMessageUID() );

	// Stop listening for the 2D draw message:
	assert( CWindow::GetDefaultWindow() );
	CMessenger::GlobalStopListening( *this, CWindow::GetDefaultWindow()->GetDraw2DMessage() );

	// Delete the internal forces:
	for( u16 i( 0 ); i < m_oInternalForces.GetSize(); ++i )
	{
		delete m_oInternalForces[ i ];
	}
}

void CCircleBot::Push( CMessage& rMessage )
{
	if( rMessage.GetType() == FRAME_OPEN_MESSAGE )
	{
		Update();
	}
	else if( rMessage.GetType() == CMouseMessage::GetMouseMessageUID() )
	{
		CMouseMessage& rMouseMessage( static_cast< CMouseMessage& >( rMessage ) );

		// Convert mouse screen position to 0 - 1:
		assert( CWindow::GetDefaultWindow() );
		assert( CWindow::GetDefaultWindow()->GetWidth() > 0 );
		assert( CWindow::GetDefaultWindow()->GetHeight() > 0 );
		f32 fX( (f32)rMouseMessage.X() / (f32)CWindow::GetDefaultWindow()->GetWidth() );
		f32 fY( (f32)rMouseMessage.Y() / (f32)CWindow::GetDefaultWindow()->GetHeight() );
		CF32Vector oMousePosition( fX, fY );

		if( rMouseMessage.GetMouseAction() == CMouseMessage::LEFT_BUTTON_DOWN )
		{
			// Check to see if the mouse is over the destination or the bot:
			if( oMousePosition.GetDistanceSquared( m_oDestination.GetPosition() ) < 
				m_oDestination.GetRadius() * m_oDestination.GetRadius() )
			{
				m_eState = MOUSE_MOVING_DESTINATION;
				m_oDestination.GetPosition().XY( fX, fY );
			}
			else if( oMousePosition.GetDistanceSquared( 
				m_oGeometry.GetPosition() ) < m_oGeometry.GetRadius() * 
				m_oGeometry.GetRadius() )
			{
				m_eState = MOUSE_MOVING_BOT;
				m_oGeometry.GetPosition().XY( fX, fY );
				m_fStartX = fX;
				m_fStartY = fY;
			}
		}
		else if( rMouseMessage.GetMouseAction() == CMouseMessage::LEFT_BUTTON_UP )
		{
			m_eState = NORMAL;
		}
		else if( rMouseMessage.GetMouseAction() == CMouseMessage::RIGHT_BUTTON_DOWN )
		{
			// Check to see if the mouse is over the bot:
			if( oMousePosition.GetDistanceSquared( m_oGeometry.GetPosition() ) < 
				m_oGeometry.GetRadius() * m_oGeometry.GetRadius() )
			{
				m_eState = RESIZING;
				m_oGeometry.SetRadius( m_oGeometry.GetPosition().GetDistance( 
					oMousePosition ) );
			}
		}
		else if( rMouseMessage.GetMouseAction() == CMouseMessage::RIGHT_BUTTON_UP )
		{
			if( m_eState == RESIZING )
			{
				m_eState = NORMAL;
			}
		}
		else if( rMouseMessage.GetMouseAction() == CMouseMessage::DRAG )
		{
			if( m_eState == MOUSE_MOVING_DESTINATION )
			{
				m_oDestination.GetPosition().XY( fX, fY );
			}
			else if( m_eState == MOUSE_MOVING_BOT )
			{
				m_oGeometry.GetPosition().XY( fX, fY );
				m_fStartX = fX;
				m_fStartY = fY;
			}
			else if( m_eState == RESIZING )
			{
				m_oGeometry.SetRadius( m_oGeometry.GetPosition().GetDistance( 
					oMousePosition ) );
			}
		}
	}
	else if( rMessage.GetType() == CWindow::GetDefaultWindow()->GetDraw2DMessage() )
	{
		m_oGeometry.Draw();
		m_oDestination.Draw();
	}
}

void CCircleBot::CalculateFacing()
{
	// Calculate the facing:
	f32 fDestinationX( m_oDestination.GetPosition().X() );
	f32 fStartX( m_oGeometry.GetPosition().X() );
	f32 fDestinationY( m_oDestination.GetPosition().Y() );
	f32 fStartY( m_oGeometry.GetPosition().Y() );
	f32 fDeltaX( fDestinationX - fStartX );
	f32 fDeltaY( fDestinationY - fStartY );
	CF32Vector oDirection( fDeltaX, fDeltaY );
	oDirection.SafeNormalize();
	oDirection *= 5.f;
	CF32Vector oNormalExternal( m_oExternalForce );
	oNormalExternal.SafeNormalize();
	if( m_bStuck )
	{
		// Circle bot hasn't made any progress in a while, so this is a bad place. Add an internal
		// force field at this location to deter the bot from coming here:
		CF32Vector oInternalPosition( m_oGeometry.GetPosition() );
		AddInternalForce( oInternalPosition );
		m_bStuck = false;
		m_oGeometry.SetColor( 1.f, 1.f, 0.f );
	}
	m_oGeometry.SetColor( 0.f, 0.f, 1.f );
	oDirection += m_oExternalForce;
	ApplyInternalForce( oDirection );
	oDirection.SafeNormalize( );
	fDeltaX = oDirection.X();
	fDeltaY = oDirection.Y();
	f32 fTargetFacing;
	if( NUtilities::AbsoluteValue( fDeltaX ) > 0.f )
	{
		fTargetFacing = static_cast< f32 >( atan( fDeltaY / fDeltaX ) );
		if( fDeltaX < 0.f )
		{
			fTargetFacing = NUtilities::RotateWrapRadians( fTargetFacing + PI );
		}
	}
	else if( fDeltaY > 0.f )
	{
		fTargetFacing = PI * 0.5f;
	}
	else
	{
		fTargetFacing = -PI * 0.5f;
	}
	m_fFacing = fTargetFacing;
}

void CCircleBot::Reset()
{
	if( m_eState != MOUSE_MOVING_BOT )
	{
		m_oGeometry.GetPosition().XY( m_fStartX, m_fStartY );
		m_bStuck = false;

		// Remove the internal forces:
		for( u16 i( 0 ); i < m_oInternalForces.GetSize( ); ++i )
		{
			delete m_oInternalForces[ i ];
		}
		m_oInternalForces.Clear();
	}
}

void CCircleBot::Stop()
{ 
	if( m_eState != MOUSE_MOVING_BOT )
	{
		m_eState = STOPPED; 
	}
}

void CCircleBot::ApplyForce( CF32Vector& rForce )
{
	m_oExternalForce = rForce;
}

void CCircleBot::Collide( f32 fCollisionAmount, const CF32Vector& krCollisionSource )
{
	CF32Vector oBackTrackMovement( m_oGeometry.GetPosition() - krCollisionSource );
	oBackTrackMovement.SafeNormalize();
	oBackTrackMovement *= fCollisionAmount;
	m_oGeometry.GetPosition() += oBackTrackMovement;
}

void CCircleBot::Update()
{
	if( m_eState == MOUSE_MOVING_BOT || m_eState == STOPPED || m_eState == RESIZING )
	{
		// Don't allow normal movement while the mouse is moving the bot:
		m_oMovementTimer.Restart();
	}
	else
	{
		f32 fElapsedTime( m_oMovementTimer.GetElapsedTimeAndReset( ) );

		m_fAnchorTimer -= fElapsedTime;

		if( m_fAnchorTimer <= 0.f )
		{
			f32 fDistance( m_oAnchorPosition.GetDistanceSquared( m_oGeometry.GetPosition() ) );
			if( fDistance < 0.00006f )
			{
				m_bStuck = true;
			}
			else
			{
				m_bStuck = false;
			}
			m_fAnchorTimer = 0.2f;
			m_oAnchorPosition.XY( m_oGeometry.GetPosition().X(), m_oGeometry.GetPosition().Y() );
		}
		CalculateFacing();

		// Move:
		f32 fXMove( static_cast< f32 >( cos( m_fFacing ) ) );
		f32 fYMove( static_cast< f32 >( sin( m_fFacing ) ) );
		CF32Vector oMove( fXMove, fYMove );

		oMove *= ( ms_kfSpeed * fElapsedTime );
		m_oGeometry.GetPosition() += oMove;

		// Check to see if bot has reached destination:
		if( m_oGeometry.GetPosition().GetDistanceSquared( 
			m_oDestination.GetPosition() ) < ( ( m_oGeometry.GetRadius() + m_oDestination.GetRadius() ) *
			(m_oGeometry.GetRadius() + m_oDestination.GetRadius()) ) )
		{
			// Destination reached.  Start over:
			Reset();
		}
	}
}

void CCircleBot::AddInternalForce( const CF32Vector& krPosition )
{
	CF32Vector* pNewForce( new CF32Vector( krPosition.X(), krPosition.Y() ) );
	m_oInternalForces.Add( pNewForce );
}

void CCircleBot::ApplyInternalForce( CF32Vector& rForce )
{
	// Add internal forces:
	for( u16 i( 0 ); i < m_oInternalForces.GetSize( ); ++i )
	{
		assert( m_oInternalForces[ i ] );
		CF32Vector& rInternalForcePoint( *m_oInternalForces[ i ] );

		// Apply a force in the direction of the vector from the force point to the position:
		CF32Vector& rPosition( m_oGeometry.GetPosition( ) );
		CF32Vector oForce( rPosition - rInternalForcePoint );
		oForce.SafeNormalize();

		// Apply a larger force, the closer the position is to the force point:
		f32 fDistance( rPosition.GetDistance( rInternalForcePoint ) );
		fDistance = NUtilities::Min( fDistance, 1.f );
		fDistance = NUtilities::Max( fDistance, 0.0001f );
		fDistance *= fDistance;
		f32 fForce( 0.005f / fDistance );
		rForce += ( oForce * fForce );
	}
}
