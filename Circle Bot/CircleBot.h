#ifndef CIRCLEBOT_H
#define CIRCLEBOT_H

#include "OpenGL 2D Circle/OpenGL2DCircle.h"
#include "Messenger/Listener.h"
#include "Timer/Timer.h"
#include "Dynamic Array/DynamicArray.h"

class CCircleBot : public CListener
{
private:
	enum ECircleBotState
	{
		NORMAL,
		MOUSE_MOVING_BOT,
		MOUSE_MOVING_DESTINATION,
		STOPPED,
		RESIZING,
	};

private:
	static const f32	ms_kfSpeed;
	static const f32	ms_kfMaxRotationSpeed;

public:
						CCircleBot( f32 fStartX, f32 fStartY, f32 fDestinationX, 
							f32 fDestinationY );
						~CCircleBot();
	virtual void		Push( CMessage& rMessage );
	void				CalculateFacing();
	const CF32Vector&	GetPosition() const	{ return m_oGeometry.GetPositionConst(); }
	f32					GetRadius() const	{ return m_oGeometry.GetRadius(); }
	void				Reset();
	void				Stop();
	void				ApplyForce( CF32Vector& rForce );
	void				Collide( f32 fCollisionAmount, const CF32Vector& krCollisionSource );

private:
	void	Update();
	void	AddInternalForce( const CF32Vector& krPosition );
	void	ApplyInternalForce( CF32Vector& rForce );

private:
	COpenGL2DCircle					m_oGeometry;
	f32								m_fFacing;
	COpenGL2DCircle					m_oDestination;
	CTimer							m_oMovementTimer;
	f32								m_fStartX;
	f32								m_fStartY;
	ECircleBotState					m_eState;
	CF32Vector						m_oExternalForce;
	bool							m_bStuck;
	TDynamicArray< CF32Vector* >	m_oInternalForces;
	CF32Vector						m_oAnchorPosition;
	f32								m_fAnchorTimer;
};

#endif // CIRCLEBOT_H
