#ifndef TIMER_H
#define TIMER_H

#include "../Common/Types.h"

class CTimerImplementation;

class CTimer
{
public:
			CTimer();
			~CTimer();
	void	Start();
	f32		End();
	void	Restart();
	bool	HasStarted() const;
	f32		GetElapsedTime();
	f32		GetElapsedTimeAndReset();
	void	Set( f32 fSeconds );

private:
	CTimerImplementation*	m_pTimerImplementation;
};

#endif TIMER_H
