#include "WindowsTimer.h"
#include <windows.h>
#include <assert.h>

CTimerImplementation* NTimer::CreateTimer()
{
	return new CWindowsTimer;
}

CWindowsTimer::CWindowsTimer()
	: m_iStartTicks( -1 )
	, m_iTicksPerSecond( 0 )
{
	LARGE_INTEGER iTicksPerSecond;
	QueryPerformanceFrequency( &iTicksPerSecond );
	m_iTicksPerSecond = iTicksPerSecond.QuadPart;
	assert( m_iTicksPerSecond > 0 );
}

void CWindowsTimer::Start()
{
	assert( m_iStartTicks == -1 );
	LARGE_INTEGER iStartTicks;
	QueryPerformanceCounter( &iStartTicks );
	m_iStartTicks = iStartTicks.QuadPart;
}

f32 CWindowsTimer::End()
{
	assert( m_iStartTicks != -1 );
	LARGE_INTEGER iEndTicks;
	QueryPerformanceCounter( &iEndTicks );
	f32 fTime( static_cast< f32 >( iEndTicks.QuadPart - m_iStartTicks ) / 
		static_cast< f32 >( m_iTicksPerSecond ) );
	m_iStartTicks = -1;
	return fTime;
}

void CWindowsTimer::Restart()
{
	assert( m_iStartTicks != -1 );
	LARGE_INTEGER iStartTicks;
	QueryPerformanceCounter( &iStartTicks );
	m_iStartTicks = iStartTicks.QuadPart;
}

bool CWindowsTimer::HasStarted() const
{
	return( m_iStartTicks != -1 ); 
}

f32 CWindowsTimer::GetElapsedTime()
{
	assert( m_iStartTicks != -1 );
	LARGE_INTEGER iEndTicks;
	QueryPerformanceCounter( &iEndTicks );
	return( static_cast< f32 >( iEndTicks.QuadPart - m_iStartTicks ) / 
		static_cast< f32 >( m_iTicksPerSecond ) );
}

f32 CWindowsTimer::GetElapsedTimeAndReset()
{
	assert( m_iStartTicks != -1 );
	LARGE_INTEGER iEndTicks;
	QueryPerformanceCounter( &iEndTicks );
	f32 fTime( static_cast< f32 >( iEndTicks.QuadPart - m_iStartTicks ) / 
		static_cast< f32 >( m_iTicksPerSecond ) );
	m_iStartTicks = iEndTicks.QuadPart;
	return fTime;
}

void CWindowsTimer::Set( f32 fSeconds )
{
	LARGE_INTEGER iCurrentTicks;
	QueryPerformanceCounter( &iCurrentTicks );
	m_iStartTicks = iCurrentTicks.QuadPart - static_cast< i64 >( 
		( fSeconds * static_cast< f32 >( m_iTicksPerSecond ) ) );
}
