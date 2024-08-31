#include "CVarSystem.h"
#include "const.h"

std::size_t CVar::GetArgIndexByArg( std::string strArg )
{
	if( strArg.empty( ) )
		return -1;

	for( std::size_t i = 0; i < m_vArgs.size( ); i++ )
		if( !m_vArgs.at( i ).m_strName.compare( strArg ) )
			return i;

	return -1;
}

CVar::CVar( std::string strName, std::string strDescription, bool active, bool bCommand )
{
	Setup( strName, strDescription, active ? 1.f : 0.f, 1.f, 0.f, bCommand );
}

CVar::CVar( std::string strName, std::string strDescription, float flValue, float flMaxValue, float flMinValue, bool bCommand )
{
	Setup( strName, strDescription, flValue, flMaxValue, flMinValue, bCommand );
}

CVar::CVar( std::string strName, std::string strDescription, int iValue, int iMaxValue, int iMinValue, bool bCommand )
{
	Setup( strName, strDescription, iValue, iMaxValue, iMinValue, bCommand );
}

CVar::~CVar( void )
{
	Release( );
}

bool CVar::GetBool( void )
{
	return ( m_flValue >= 1.f );
}

bool CVar::HasArgs( void )
{
	return !m_vArgs.empty( );
}

bool CVar::IsArg( std::string strArg )
{
	return( GetArgIndexByArg( strArg ) != -1 );
}

bool CVar::IsCommand( void )
{
	return m_bCommand;
}

bool CVar::SetByArg( std::string strArg )
{
	if( !HasArgs( ) )
		return false;

	std::size_t i = GetArgIndexByArg( strArg );
	if( i == -1 )
		return false;

	Set( m_vArgs.at( i ).m_flValue );

	return true;
}

float CVar::GetFloat( void )
{
	return m_flValue;
}

float CVar::GetMax( void )
{
	return m_flMaxValue;
}

float CVar::GetMin( void )
{
	return m_flMinValue;
}

int CVar::GetInt( void )
{
	return int( m_flValue );
}

std::string CVar::GetName( void )
{
	return m_strName;
}

std::string CVar::GetInfoString( void )
{
	static char pszBuffer[ 0x400 ];
	if( m_flMaxValue == 1.f && m_flMinValue == 0.f )
		sprintf_s( pszBuffer, "%s", GetBool( ) ? "true" : "false" );
	else sprintf_s( pszBuffer, "%.2f", m_flValue );

	return pszBuffer;
}

std::string CVar::GetDescription( void )
{
	return m_strDescription;
}

std::vector< CVar::StrArg > CVar::GetAllArgs( void )
{
	return m_vArgs;
}

void CVar::AddArg( std::string strArg, bool active )
{
	AddArg( strArg, active ? 1.f : 0.f );
}

void CVar::AddArg( std::string strArg, float flValue )
{
	if( GetArgIndexByArg( strArg ) != -1 )
		return;

	m_vArgs.push_back( { strArg, flValue } );
}

void CVar::AddArg( std::string strArg, int iValue )
{
	AddArg( strArg, float( iValue ) );
}

void CVar::Setup( std::string strName, std::string strDescription, bool active, bool bCommand )
{
	Setup( strName, strDescription, active ? 1.f : 0.f, 1.f, 0.f, bCommand );
}

void CVar::Setup( std::string strName, std::string strDescription, float flValue, float flMaxValue, float flMinValue, bool bCommand )
{
	SetName( strName );
	SetDescription( strDescription );
	m_flMaxValue = flMaxValue;
	m_flMinValue = flMinValue;
	Set( flValue );
	SetCommand( bCommand );
}

void CVar::Setup( std::string strName, std::string strDescription, int iValue, int iMaxValue, int iMinValue, bool bCommand )
{
	Setup( strName, strDescription, float( iValue ), float( iMaxValue ), float( iMinValue ), bCommand );
}

void CVar::SetName( std::string strName )
{
	m_strName = strName;
}

void CVar::SetDescription( std::string strDescription )
{
	m_strDescription = strDescription;
}

void CVar::SetCommand( bool bCommand )
{
	m_bCommand = bCommand;
}

void CVar::Set( bool active )
{
	Set( active ? 1.f : 0.f );
}

void CVar::Set( float flValue )
{
	if( flValue > m_flMaxValue )
		m_flValue = m_flMaxValue;
	else if( flValue < m_flMinValue )
		m_flValue = m_flMinValue;
	else m_flValue = flValue;
}

void CVar::Set( int iValue )
{
	Set( float( iValue ) );
}

void CVar::Release( void )
{
	m_vArgs.clear( );
}

std::size_t CVarSystem::GetCVarIndexByName( std::string strName )
{
	if( strName.empty( ) )
		return -1;

	for( std::size_t i = 0; i < m_vpCVars.size( ); i++ )
		if( !m_vpCVars.at( i )->GetName( ).compare( strName ) )
			return i;

	return -1;
}

CVarSystem::CVarSystem( void )
{

}

CVarSystem::~CVarSystem( void )
{
	Release( );
}


bool CVarSystem::IsCVar( std::string strName )
{
	return( GetCVarIndexByName( strName ) != -1 );
}

CVar* CVarSystem::NewCVar( std::string strName, std::string strDescription, bool active, bool bCommand, bool push )
{
	return NewCVar( strName, strDescription, active ? 1.f : 0.f, 1.f, 0.f, bCommand, push );
}

CVar* CVarSystem::NewCVar( std::string strName, std::string strDescription, float flValue, float flMaxValue, float flMinValue, bool bCommand, bool push )
{
	std::size_t i = GetCVarIndexByName( strName );
	if( i != -1 )
		return m_vpCVars.at( i );

	CVar* pCVar = new CVar( strName, strDescription, flValue, flMaxValue, flMinValue, bCommand );
	if( push )
		PushCVar( pCVar );

	return pCVar;
}

CVar* CVarSystem::NewCVar( std::string strName, std::string strDescription, int iValue, int iMaxValue, int iMinValue, bool bCommand, bool push )
{
	return NewCVar( strName, strDescription, float( iValue ), float( iMaxValue ), float( iMinValue ), bCommand, push );
}

CVar* CVarSystem::GetCVar( std::string strName )
{
	std::size_t i = GetCVarIndexByName( strName );
	if( i == -1 )
		return nullptr;

	return m_vpCVars.at( i );
}

std::vector< CVar* > CVarSystem::GetAllCVars( void )
{
	return m_vpCVars;
}

void CVarSystem::PushCVar( CVar* pCVar )
{
	if( !pCVar )
		return;

	m_vpCVars.push_back( pCVar );
}

void CVarSystem::Release( void )
{
	for( std::size_t i = 0; i < m_vpCVars.size( ); i++ )
	{
		delete m_vpCVars.at( i );
		m_vpCVars.at( i ) = nullptr;
	}
	m_vpCVars.clear( );
}

void InitCVars( void )
{
#pragma region "Aimbot"
	g_CVars.NewCVar( "aim_active", "Enable/disable the aimbot", true );
	g_CVars.NewCVar( "aim_autoshoot", "Enable/disable autoshoot", false );
	g_CVars.NewCVar( "aim_rcs", "Enable/disable aimbot recoil control system", false );
	g_CVars.NewCVar( "aim_autowall", "Enable/disable shooting trough penetrable walls", false );
	g_CVars.NewCVar( "aim_autowall_damage", "Adjust the minimal damage to shoot trough walls", 2.f, 100.f, 1.f );
	g_CVars.NewCVar( "aim_silent", "Enable/disable silent/perfect silent aimbot", 0, 2, 0 );
	g_CVars.NewCVar( "aim_weapons", "Enable/disable weapon group specific configs", false );
	g_CVars.NewCVar( "aim_norecoil", "Removes the weapon recoil", true );
	g_CVars.NewCVar( "aim_nospread", "Removes the weapon spread !won't work in MM!", false );	
	g_CVars.NewCVar( "aim_fov", "Adjust the custom field of view for the aimbot", 20, 180, 0 );
	g_CVars.NewCVar( "aim_distancebased", "Use distancebased field of view", false );
	g_CVars.NewCVar( "aim_smooth", "Adjust the custom smooth amount", 5, 50, 0 );
	g_CVars.NewCVar( "aim_time", "Adjust the aimbot active time", 0, 1000, 0 );
	g_CVars.NewCVar( "aim_hitscan", "Enable/disable hitscans and switch between normal/trough walls", 0, 2, 0 );
	g_CVars.NewCVar( "aim_smart", "Switch the hitbox after x bullets", 0, 150, 0 );

	auto pCVar = g_CVars.NewCVar( "aim_at", "Switch between enemy only/team only/all", 0, 2, 0, true, false );
	pCVar->AddArg( "enemy", 0 );
	pCVar->AddArg( "team", 1 );
	pCVar->AddArg( "all", 2 );
	g_CVars.PushCVar( pCVar );
	pCVar = g_CVars.NewCVar( "aim_hitbox", "custom aimbot hitbox", ValveSDK::HITBOX_NECK, ValveSDK::HITBOX_MAX - 1, 0, true, false );
	pCVar->AddArg( "pelvis", ValveSDK::HITBOX_PELVIS );
	pCVar->AddArg( "l_thigh", ValveSDK::HITBOX_L_THIGH );
	pCVar->AddArg( "l_calf", ValveSDK::HITBOX_L_CALF );
	pCVar->AddArg( "l_foot", ValveSDK::HITBOX_L_FOOT );
	pCVar->AddArg( "r_thigh", ValveSDK::HITBOX_R_THIGH );
	pCVar->AddArg( "r_calf", ValveSDK::HITBOX_R_CALF );
	pCVar->AddArg( "r_foot", ValveSDK::HITBOX_R_FOOT );
	pCVar->AddArg( "spine1", ValveSDK::HITBOX_SPINE1 );
	pCVar->AddArg( "spine2", ValveSDK::HITBOX_SPINE2 );
	pCVar->AddArg( "spine3", ValveSDK::HITBOX_SPINE3 );
	pCVar->AddArg( "neck", ValveSDK::HITBOX_NECK );
	pCVar->AddArg( "head", ValveSDK::HITBOX_HEAD );
	pCVar->AddArg( "l_upperarm", ValveSDK::HITBOX_L_UPPERARM );
	pCVar->AddArg( "l_forearm", ValveSDK::HITBOX_L_FOREARM );
	pCVar->AddArg( "l_hand", ValveSDK::HITBOX_L_HAND );
	pCVar->AddArg( "r_upperarm", ValveSDK::HITBOX_R_UPPERARM );
	pCVar->AddArg( "r_forearm", ValveSDK::HITBOX_R_FOREARM );
	pCVar->AddArg( "r_hand", ValveSDK::HITBOX_R_HAND );
	pCVar->AddArg( "l_clavicle", ValveSDK::HITBOX_L_CLAVICLE );
	pCVar->AddArg( "r_clavicle", ValveSDK::HITBOX_R_CLAVICLE );
	pCVar->AddArg( "helmet", ValveSDK::HITBOX_HELMET );
	pCVar->AddArg( "spine4", ValveSDK::HITBOX_SPINE4 );
	g_CVars.PushCVar( pCVar );
	pCVar = g_CVars.NewCVar( "aim_smart_hitbox", "custom smart aimbot hitbox", ValveSDK::HITBOX_SPINE3, ValveSDK::HITBOX_MAX - 1, 0, true, false );
	pCVar->AddArg( "pelvis", ValveSDK::HITBOX_PELVIS );
	pCVar->AddArg( "l_thigh", ValveSDK::HITBOX_L_THIGH );
	pCVar->AddArg( "l_calf", ValveSDK::HITBOX_L_CALF );
	pCVar->AddArg( "l_foot", ValveSDK::HITBOX_L_FOOT );
	pCVar->AddArg( "r_thigh", ValveSDK::HITBOX_R_THIGH );
	pCVar->AddArg( "r_calf", ValveSDK::HITBOX_R_CALF );
	pCVar->AddArg( "r_foot", ValveSDK::HITBOX_R_FOOT );
	pCVar->AddArg( "spine1", ValveSDK::HITBOX_SPINE1 );
	pCVar->AddArg( "spine2", ValveSDK::HITBOX_SPINE2 );
	pCVar->AddArg( "spine3", ValveSDK::HITBOX_SPINE3 );
	pCVar->AddArg( "neck", ValveSDK::HITBOX_NECK );
	pCVar->AddArg( "head", ValveSDK::HITBOX_HEAD );
	pCVar->AddArg( "l_upperarm", ValveSDK::HITBOX_L_UPPERARM );
	pCVar->AddArg( "l_forearm", ValveSDK::HITBOX_L_FOREARM );
	pCVar->AddArg( "l_hand", ValveSDK::HITBOX_L_HAND );
	pCVar->AddArg( "r_upperarm", ValveSDK::HITBOX_R_UPPERARM );
	pCVar->AddArg( "r_forearm", ValveSDK::HITBOX_R_FOREARM );
	pCVar->AddArg( "r_hand", ValveSDK::HITBOX_R_HAND );
	pCVar->AddArg( "l_clavicle", ValveSDK::HITBOX_L_CLAVICLE );
	pCVar->AddArg( "r_clavicle", ValveSDK::HITBOX_R_CLAVICLE );
	pCVar->AddArg( "helmet", ValveSDK::HITBOX_HELMET );
	pCVar->AddArg( "spine4", ValveSDK::HITBOX_SPINE4 );
	g_CVars.PushCVar( pCVar );
#pragma endregion

#pragma region "Visuals"
	g_CVars.NewCVar( "vis_active", "Enable/disable player visuals", true );
	g_CVars.NewCVar( "vis_enemyonly", "Enable/disable esp only for enemys", true );
	pCVar = g_CVars.NewCVar( "vis_box", "Choose between bounding different styles", 1, 2, 0, true, false );
	pCVar->AddArg( "normal", 1 );
	pCVar->AddArg( "edge", 2 );
	g_CVars.PushCVar( pCVar );
	g_CVars.NewCVar( "vis_box_outlined", "Enable/disable outlined bounding boxes", true );
	pCVar = g_CVars.NewCVar( "vis_weapons", "Enable/disable player heatlhbar", 1, 2, 0, true, false );
	pCVar->AddArg( "Weapon Symbol", 1 );
	pCVar->AddArg( "Weapon Name", 2 );
	g_CVars.PushCVar( pCVar );
	g_CVars.NewCVar( "vis_chams", "Enable/disable colored models", 1, 2, 0 );
	g_CVars.NewCVar( "vis_chams_wireframe", "Enable/disable wireframe chams", false );
	g_CVars.NewCVar( "vis_hands", "Enable/disable hand render flags", 0, 2, 0 );
#pragma endregion
	
#pragma region "Misc"
	g_CVars.NewCVar( "playerlist", "Enable/disable configurable player list", false, false );
	g_CVars.NewCVar( "misc_visnorecoil", "Remove visuals recoil", true );
	g_CVars.NewCVar( "misc_bunnyhop", "Enable/disable automatic jumps", true );
	g_CVars.NewCVar( "spam_roundstart", "Spam on round begin a string", true );
	g_CVars.NewCVar( "spam_1tap", "Spam a string when a player get rekt", true );
	g_CVars.NewCVar( "spam_sound", "Play a sound when player get rekt", false );
	pCVar = g_CVars.NewCVar( "misc_pitch", "Pitch anti aim", 0, 1, 0, true, false );
	pCVar->AddArg( "emotion", 1 );
	pCVar->AddArg( "down", 2 );
	g_CVars.PushCVar( pCVar );

	pCVar = g_CVars.NewCVar( "misc_yaw", "Yaw anti aim", 0, 1, 0, true, false );
	pCVar->AddArg( "fdynamic", 1 );
	g_CVars.PushCVar( pCVar );
#pragma endregion

#pragma region "Skins"
	g_CVars.NewCVar( "skin_knife_model", "Custom knife model", 6, 10, 0, false );
#pragma endregion	
}

CVarSystem g_CVars = CVarSystem( );