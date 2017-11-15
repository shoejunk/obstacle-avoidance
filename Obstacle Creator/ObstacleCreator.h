#ifndef OBSTACLECREATOR_H
#define OBSTACLECREATOR_H

#include "Dynamic Array/DynamicArray.h"
#include "Obstacle/Obstacle.h"
#include "Messenger/Listener.h"

class CObstacleCreator : public CListener
{
public:
					CObstacleCreator();
					~CObstacleCreator();
	virtual void	Push( CMessage& rMessage );
	CObstacle*		CollideObstaclesWithCircle( f32 fX, f32 fY, f32 fRadius ) const;
	CF32Vector		CalculateForce( const CF32Vector& krPosition, f32 fRadius ) const;

private:
	bool	GetObstacleIndexAt( f32 fX, f32 fY, u16& uIndex  );

private:
	TDynamicArray< CObstacle* >	m_oObstacles;
};

#endif // OBSTACLECREATOR_H
