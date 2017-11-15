#include "Obstacle.h"
#include "Window/Window.h"
#include "Messenger/Messenger.h"
#include "Windows Input/MouseMessage.h"

CObstacle::CObstacle( f32 fX, f32 fY, f32 fRadius )
	: m_oGeometry( fX, fY, fRadius, 1.f, 0.f, 0.f )
	, m_eState( NORMAL )
{
	CMessenger::GlobalListen( *this, CMouseMessage::GetMouseMessageUID() );
}

CObstacle::~CObstacle()
{
	CMessenger::GlobalStopListening( *this, CMouseMessage::GetMouseMessageUID() );
}

f32 CObstacle::X() const
{ 
	return m_oGeometry.GetPositionConst().X(); 
}

f32 CObstacle::Y() const
{ 
	return m_oGeometry.GetPositionConst().Y(); 
}

bool CObstacle::CollideWithCircle( f32 fX, f32 fY, f32 fRadius ) const
{
	CF32Vector oPosition( fX, fY );
	f32 fCombinedRadius( fRadius + m_oGeometry.GetRadius() );
	if( m_oGeometry.GetPositionConst().GetDistanceSquared( oPosition ) <
		fCombinedRadius * fCombinedRadius )
	{
		return true;
	}
	return false;
}

CF32Vector CObstacle::CalculateForce( const CF32Vector& krPosition, f32 fRadius ) const
{
	// Apply a force in the direction of the vector from the obstacle to the position:
	CF32Vector oForce( krPosition - GetPosition() );
	oForce.Normalize();

	// Apply a larger force, the closer the position is to the obstacle:
	f32 fDistance( krPosition.GetDistance( GetPosition() ) - fRadius - GetRadius() );
	fDistance = NUtilities::Min( fDistance, 1.f );
	fDistance = NUtilities::Max( fDistance, 0.0001f );
	fDistance *= fDistance;
	f32 fForce( 0.005f / fDistance );
	return oForce * fForce;
}

void CObstacle::Push( CMessage& rMessage )
{
	if( rMessage.GetType() == CMouseMessage::GetMouseMessageUID() )
	{
		CMouseMessage& rMouseMessage( static_cast< CMouseMessage& >( rMessage ) );

		f32 fX( (f32)rMouseMessage.GetNormalX() );
		f32 fY( (f32)rMouseMessage.GetNormalY() );
		CF32Vector oMousePosition( fX, fY );

		if( rMouseMessage.GetMouseAction() == CMouseMessage::LEFT_BUTTON_DOWN )
		{
			// Check to see if the mouse is over the obstacle:
			if( oMousePosition.GetDistanceSquared( m_oGeometry.GetPosition() ) < 
				m_oGeometry.GetRadius() * m_oGeometry.GetRadius() )
			{
				m_eState = MOVING;
				m_oGeometry.GetPosition().XY( fX, fY );
			}
		}
		else if( rMouseMessage.GetMouseAction() == CMouseMessage::LEFT_BUTTON_UP )
		{
			if( m_eState == MOVING )
			{
				m_eState = NORMAL;
			}
		}
		else if( rMouseMessage.GetMouseAction() == CMouseMessage::RIGHT_BUTTON_DOWN )
		{
			// Check to see if the mouse is over the obstacle:
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
			if( m_eState == MOVING )
			{
				m_oGeometry.GetPosition().XY( fX, fY );
			}
			else if( m_eState == RESIZING )
			{
				m_oGeometry.SetRadius( m_oGeometry.GetPosition().GetDistance( 
					oMousePosition ) );
			}
		}
	}
}
