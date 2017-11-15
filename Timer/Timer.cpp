#include "Timer.h"
#include <assert.h>
#include "TimerImplementation.h"

CTimer::CTimer()
	: m_pTimerImplementation( NTimer::CreateTimer() )
{
	assert( m_pTimerImplementation );
}

CTimer::~CTimer()
{
	delete m_pTimerImplementation;
}

void CTimer::Start()
{
	assert( m_pTimerImplementation );
	m_pTimerImplementation->Start();
}

f32 CTimer::End()
{
	assert( m_pTimerImplementation );
	return m_pTimerImplementation->End();
}

void CTimer::Restart()
{
	assert( m_pTimerImplementation );
	m_pTimerImplementation->Restart();
}

bool CTimer::HasStarted() const
{
	assert( m_pTimerImplementation );
	return m_pTimerImplementation->HasStarted();
}

f32 CTimer::GetElapsedTime()
{
	assert( m_pTimerImplementation );
	return m_pTimerImplementation->GetElapsedTime();
}

f32 CTimer::GetElapsedTimeAndReset()
{
	assert( m_pTimerImplementation );
	return m_pTimerImplementation->GetElapsedTimeAndReset();
}

void CTimer::Set( f32 fSeconds )
{
	assert( m_pTimerImplementation );
	m_pTimerImplementation->Set( fSeconds );
}
