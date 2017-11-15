#ifndef TIMERIMPLEMENTATION_H
#define TIMERIMPLEMENTATION_H

#include "../Common/Types.h"

class CTimerImplementation
{
public:
	virtual void	Start() = 0;
	virtual f32		End() = 0;
	virtual void	Restart() = 0;
	virtual bool	HasStarted() const = 0;
	virtual f32		GetElapsedTime() = 0;
	virtual f32		GetElapsedTimeAndReset() = 0;
	virtual void	Set( f32 fSeconds ) = 0;
};

namespace NTimer
{
	CTimerImplementation*	CreateTimer();
};

#endif TIMERIMPLEMENTATION_H
