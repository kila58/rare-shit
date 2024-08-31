#ifndef __CVARSYSTEM_H__
#define __CVARSYSTEM_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"

class CVar
{
private:
	class StrArg
	{
	public:
		std::string	m_strName;
		float		m_flValue;
	};

private:
	std::string				m_strName;
	std::string				m_strDescription;
	float					m_flValue;
	float					m_flMaxValue;
	float					m_flMinValue;
	bool					m_bCommand;
	std::vector< StrArg >	m_vArgs;

private:
	std::size_t				GetArgIndexByArg( std::string strArg );

public:
	CVar( std::string strName, std::string strDescription, bool active, bool bCommand = true );
	CVar( std::string strName, std::string strDescription, float flValue, float flMaxValue = 1.f, float flMinValue = 0.f, bool bCommand = true );
	CVar( std::string strName, std::string strDescription, int iValue, int iMaxValue = 1, int iMinValue = 0, bool bCommand = true );
	~CVar( void );
	bool					ContainsCVars( void );
	bool					GetBool( void );
	bool					HasArgs( void );
	bool					IsArg( std::string strArg );
	bool					IsCommand( void );
	bool 					SetByArg( std::string strArg );
	float					GetFloat( void );
	float					GetMax( void );
	float					GetMin( void );
	int 					GetInt( void );
	std::string				GetName( void );
	std::string				GetInfoString( void );
	std::string				GetDescription( void );
	std::vector< StrArg >	GetAllArgs( void );
	void 					AddArg( std::string strArg, bool active );
	void 					AddArg( std::string strArg, float flValue );
	void 					AddArg( std::string strArg, int iValue );
	void 					Setup( std::string strName, std::string strDescription, bool active, bool bCommand = true );
	void 					Setup( std::string strName, std::string strDescription, float flValue, float flMaxValue = 1.f, float flMinValue = 0.f, bool bCommand = true );
	void 					Setup( std::string strName, std::string strDescription, int iValue, int iMaxValue = 1, int iMinValue = 0, bool bCommand = true );
	void 					SetName( std::string strName );
	void 					SetDescription( std::string strDescription );
	void					SetCommand( bool bCommand );
	void 					Set( bool active );
	void 					Set( float flValue );
	void 					Set( int iValue );
	void 					Release( void );
};

class CVarSystem
{
private:
	std::vector< CVar* >	m_vpCVars;

private:
	std::size_t				GetCVarIndexByName( std::string strName );
public:
	CVarSystem( void );
	~CVarSystem( void );
	bool					IsCVar( std::string strName );
	CVar*					NewCVar( std::string strName, std::string strDescription, bool active, bool bCommand = true, bool push = true );
	CVar*					NewCVar( std::string strName, std::string strDescription, float flValue, float flMaxValue = 1.f, float flMinValue = 0.f, bool bCommand = true, bool push = true );
	CVar*					NewCVar( std::string strName, std::string strDescription, int iValue, int iMaxValue = 1, int iMinValue = 0, bool bCommand = true, bool push = true );
	CVar*					GetCVar( std::string strName );
	std::vector< CVar* >	GetAllCVars( void );
	void					PushCVar( CVar* pCVar );
	void					Release( void );
};

extern CVarSystem g_CVars;
extern void InitCVars( void );

#endif