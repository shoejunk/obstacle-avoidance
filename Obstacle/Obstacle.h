#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "OpenGL 2D Circle/OpenGL2DCircle.h"
#include "Messenger/Listener.h"

class CObstacle : public CListener
{
private:
	enum EObstacleState
	{
		NORMAL,
		MOVING,
		RESIZING,
	};

public:
						CObstacle( f32 fX, f32 fY, f32 fRadius );
						~CObstacle();
	f32					X() const;
	f32					Y() const;
	const CF32Vector&	GetPosition() const	{ return m_oGeometry.GetPositionConst(); }
	f32					GetRadius() const	{ return m_oGeometry.GetRadius(); }
	bool				CollideWithCircle( f32 fX, f32 fY, f32 fRadius ) const;
	CF32Vector			CalculateForce( const CF32Vector& krPosition, 
							f32 fRadius ) const;
	virtual void		Push( CMessage& rMessage );
	void				Draw() const		{ m_oGeometry.Draw(); }

private:
	COpenGL2DCircle	m_oGeometry;
	EObstacleState	m_eState;
};

#endif // OBSTACLE_H
