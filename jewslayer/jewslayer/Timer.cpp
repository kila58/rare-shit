#include "Timer.h"

void Timer::Proceed( void )
{
	if( !m_bFinished )
		m_dwCurrentTime = timeGetTime( );
}

void Timer::StartTimer( void )
{
	if( !m_bStarted )
	{
		m_bStarted = true;
		m_bFinished = false;
		m_dwStartTime = timeGetTime( );
	}
}

Timer::Timer( void )
{
	Setup( 0 );
}

Timer::Timer( DWORD dwTime )
{
	Setup( dwTime );
}

Timer::~Timer( void )
{
	Setup( 0 );
}

bool Timer::finished( void )
{
	if( m_bFinished )
		return true;

	return ( m_dwCurrentTime - m_dwStartTime >= m_dwTime );
}

void Timer::Reset( void )
{
	Setup( m_dwTime );
}

void Timer::Run( void )
{
	StartTimer( );
	Proceed( );
}

void Timer::Setup( DWORD dwTime )
{
	m_bStarted = false;
	m_bFinished = false;
	m_dwStartTime = 0;
	m_dwCurrentTime = 0;
	m_dwTime = dwTime;
}

void Timer::SetTime( DWORD dwTime )
{
	m_dwTime = dwTime;
}