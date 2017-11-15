#include "ObstacleCreator.h"
#include <assert.h>
#include "Windows Input/MouseMessage.h"
#include "Messenger/Messenger.h"
#include "Window/Window.h"

#include "Dynamic Array/DynamicArray.inl"

CObstacleCreator::CObstacleCreator()
	: m_oObstacles( 0, NULL )
{
	CMessenger::GlobalListen( *this, CMouseMessage::GetMouseMessageUID() );
	assert( CWindow::GetDefaultWindow() );
	CMessenger::GlobalListen( *this, CWindow::GetDefaultWindow()->GetDraw2DMessage() );
}

CObstacleCreator::~CObstacleCreator()
{
	CMessenger::GlobalStopListening( *this, CMouseMessage::GetMouseMessageUID() );
	assert( CWindow::GetDefaultWindow() );
	CMessenger::GlobalStopListening( *this, CWindow::GetDefaultWindow()->GetDraw2DMessage() );
	for( u16 i( 0 ); i < m_oObstacles.GetSize( ); ++i )
	{
		if( m_oObstacles[ i ] )
		{
			delete m_oObstacles[ i ];
		}
	}
}

void CObstacleCreator::Push( CMessage& rMessage )
{
	if( rMessage.GetType() == CMouseMessage::GetMouseMessageUID() )
	{
		CMouseMessage& rMouseMessage( static_cast<CMouseMessage&>( rMessage ) );
		if( rMouseMessage.GetMouseAction() == CMouseMessage::LEFT_BUTTON_DOUBLE_CLICK )
		{
			// On double-click, create or destroy an obstacle.  First see if there are
			// any obstacles under the mouse:
			u16 uIndex;
			if( GetObstacleIndexAt( rMouseMessage.GetNormalX(),
				rMouseMessage.GetNormalY(), uIndex ) )
			{
				// Found an obstacle under the mouse.  Destroy it:
				delete m_oObstacles[ uIndex ];
				m_oObstacles.RemoveByIndex( uIndex );
			}
			else
			{
				// No obstacles under the mouse, so create a new one:
				m_oObstacles.Add( new CObstacle( rMouseMessage.GetNormalX(),
					rMouseMessage.GetNormalY(), 0.02f ) );
			}
		}
	}
	else if( rMessage.GetType() == CWindow::GetDefaultWindow()->GetDraw2DMessage() )
	{
		for( u16 i( 0 ); i < m_oObstacles.GetSize(); ++i )
		{
			if( m_oObstacles[ i ] )
			{
				m_oObstacles[ i ]->Draw();
			}
		}
	}
}

CObstacle* CObstacleCreator::CollideObstaclesWithCircle( 
	f32 fX, f32 fY, f32 fRadius ) const
{
	for( u16 i( 0 ); i < m_oObstacles.GetSize(); ++i )
	{
		if( m_oObstacles[ i ] && m_oObstacles[ i ]->CollideWithCircle( 
			fX, fY, fRadius ) )
		{
			return m_oObstacles[ i ];
		}
	}
	return NULL;
}

CF32Vector CObstacleCreator::CalculateForce( const CF32Vector& krPosition, 
	f32 fRadius ) const
{
	CF32Vector oForce( 0.f, 0.f );
	u32 uCount( 0 );
	for( u16 i( 0 ); i < m_oObstacles.GetSize(); ++i )
	{
		CObstacle* pObstacle( m_oObstacles[ i ] );
		if( pObstacle )
		{
			oForce += pObstacle->CalculateForce( krPosition, fRadius );
			++uCount;
		}
	}
	if( uCount > 1 )
	{
		oForce /= (f32)uCount;
	}
	return oForce;
}

bool CObstacleCreator::GetObstacleIndexAt( f32 fX, f32 fY, u16& uIndex )
{
	CF32Vector oTestPosition( fX, fY );
	for( uIndex = 0; uIndex < m_oObstacles.GetSize(); ++uIndex )
	{
		CObstacle* pObstacle( m_oObstacles[ uIndex ] );
		if( pObstacle )
		{
			if( pObstacle->GetPosition().GetDistanceSquared( 
				oTestPosition ) < pObstacle->GetRadius() * pObstacle->GetRadius() )
			{
				return true;
			}
		}
	}
	return false;
}
