#ifndef __MENU_H__
#define __MENU_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

enum eKeyFlags
{
	KEY_FLAG_NONE = 0,
	KEY_FLAG_MOUSE1,
	KEY_FLAG_MOUSE2,
	KEY_FLAG_MOUSE3 = 4,
	KEY_FLAG_MOUSE4,
	KEY_FLAG_MOUSE5,
};

class CKeyInput
{
public:
	std::string	m_strChar;

public:
	CKeyInput( void );
	~CKeyInput( void );
	void Handle( int iKey );
};

class CMouseInput
{
public:
	int		m_iVirtualKey;
	int		m_iXPosition;
	int		m_iYPosition;

private:
	bool	ValidFlags( int flags );

public:
	CMouseInput( void );
	CMouseInput( int flags );
	bool	InEvent( int flags = KEY_FLAG_NONE );
	bool	IsHover( int x, int y, int w, int h );
	bool	IsPressed( int flags = KEY_FLAG_NONE );
	int		x( void );
	int		y( void );
	void	GetMousePosition( int& x, int& y );
	void	SetKey( int flags );
	void	Update( void );
};

class CMenu
{
private:
	bool			m_bActive;
	bool			m_bAimHitboxCombo;
	bool			m_bSmartHitboxCombo;
	bool			m_bAimAtCombo;
	bool			m_bAimHitscanCombo;
	bool			m_bAimSilentCombo;
	bool			m_bVisBoxCombo;
	bool			m_bVisWeaponsCombo;
	bool			m_bVisHandsCombo;
	bool			m_bVisChamsCombo;
	int				m_iX;
	int				m_iY;
	int				m_iW;
	int				m_iH;
	CKeyInput*		m_pKeyInput;
	CMouseInput*	m_pMouseInput;
	std::vector< std::string >	m_strHitboxes;
	std::vector< std::string >	m_strAimAt;
	std::vector< std::string >	m_strHitscans;
	std::vector< std::string >	m_strSilent;
	std::string					m_strCurrentInput;
	std::vector< std::string >	m_strHistory;
	std::vector< std::string >	m_strVisBoxes;
	std::vector< std::string >	m_strVisWeapons;
	std::vector< std::string >	m_strVisHands;
	std::vector< std::string >	m_strVisChams;

	int				m_iCurrentTap;
private:
	void Echo( const char* fmt, ... );
	void FilterArgs( std::string strInput, std::vector< std::string >& strArgs );
	void HandleInput( std::string strInput );
	void RenderTab( int x, int y, int w, int h, std::string strText, int iIndex, int& iStatus );
	void RenderCheckbox( int x, int y, std::string strText, std::string strCVar );
	void RenderSlider( int x, int y, int w, int h, std::string strText, std::string strCVar );
	void RenderComboBox( int x, int y, int w, int h, std::vector< std::string > strNotes, std::string strCVar, bool& bState );
	void Drag( int w, int h );


	void RenderAimbotTab( int x, int y, int w, int h );
	void RenderVisualsTab( int x, int y, int w, int );
	void RenderMiscTab( int x, int y, int w, int h );
	void RenderConsole( int x, int y, int w, int h );

public:
	CMenu( void );
	~CMenu( void );

	void SetActive( bool active );
	void HandleInputChar( int iKey );
	void Render( void );
	void SetPosition( int x, int y );
};

extern CMenu* g_pMenu;

#endif