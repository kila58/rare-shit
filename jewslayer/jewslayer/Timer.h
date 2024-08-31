#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"

class Timer
{
private:
	bool	m_bStarted;
	bool	m_bFinished;
	DWORD	m_dwStartTime;
	DWORD	m_dwCurrentTime;
	DWORD	m_dwTime;

private:
	void	Proceed( void );
	void	StartTimer( void );

public:
	Timer( void );
	Timer( DWORD dwTime );
	~Timer( void );
	bool	finished( void );
	void	Reset( void );
	void	Run( void );
	void	Setup( DWORD dwTime );
	void	SetTime( DWORD dwTime );
};

#endif