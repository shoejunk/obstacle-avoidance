#ifndef WINDOWSTIMER_H
#define WINDOWSTIMER_H

#include "../Timer/TimerImplementation.h"

class CWindowsTimer : public CTimerImplementation
{
public:
					CWindowsTimer();
	virtual			~CWindowsTimer()	{}
	virtual void	Start();
	virtual f32		End();
	virtual void	Restart();
	virtual bool	HasStarted() const;
	virtual f32		GetElapsedTime();
	virtual f32		GetElapsedTimeAndReset();
	virtual void	Set( f32 fSeconds );

private:
	i64	m_iStartTicks;
	i64	m_iTicksPerSecond;
};

#endif
