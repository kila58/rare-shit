#include "Menu.h"

#pragma region "Virtual Keys"
typedef struct
{
	char m_def[ 16 ];
	char m_alt[ 16 ];
}KeyStroke_t;

static KeyStroke_t g_KeyStrokes[ ValveSDK::MOUSE_COUNT + ValveSDK::KEY_COUNT ] =
{
	{ "", "" },
	{ "0", ")" },		//KEY_0,
	{ "1", "!" },		//KEY_1,
	{ "2", "\"" },		//KEY_2,
	{ "3", "£" },		//KEY_3,
	{ "4", "$" },		//KEY_4,
	{ "5", "%" },		//KEY_5,
	{ "6", "^" },		//KEY_6,
	{ "7", "&" },		//KEY_7,
	{ "8", "*" },		//KEY_8,
	{ "9", "(" },		//KEY_9,
	{ "a", "A" },		//KEY_A,
	{ "b", "B" },		//KEY_B,
	{ "c", "C" },		//KEY_C,
	{ "d", "D" },		//KEY_D,
	{ "e", "E" },		//KEY_E,
	{ "f", "F" },		//KEY_F,
	{ "g", "G" },		//KEY_G,
	{ "h", "H" },		//KEY_H,
	{ "i", "I" },		//KEY_I,
	{ "j", "J" },		//KEY_J,
	{ "k", "K" },		//KEY_K,
	{ "l", "L" },		//KEY_L,
	{ "m", "M" },		//KEY_M,
	{ "n", "N" },		//KEY_N,
	{ "o", "O" },		//KEY_O,
	{ "p", "P" },		//KEY_P,
	{ "q", "Q" },		//KEY_Q,
	{ "r", "R" },		//KEY_R,
	{ "s", "S" },		//KEY_S,
	{ "t", "T" },		//KEY_T,
	{ "u", "U" },		//KEY_U,
	{ "v", "V" },		//KEY_V,
	{ "w", "W" },		//KEY_W,
	{ "x", "X" },		//KEY_X,
	{ "y", "Y" },		//KEY_Y,
	{ "z", "|" },		//KEY_Z,
	{ "0", "0" },		//KEY_PAD_0,
	{ "1", "1" },		//KEY_PAD_1,
	{ "2", "2" },		//KEY_PAD_2,
	{ "3", "3" },		//KEY_PAD_3,
	{ "4", "4" },		//KEY_PAD_4,
	{ "5", "5" },		//KEY_PAD_5,
	{ "6", "6" },		//KEY_PAD_6,
	{ "7", "7" },		//KEY_PAD_7,
	{ "8", "8" },		//KEY_PAD_8,
	{ "9", "9" },		//KEY_PAD_9,
	{ "/", "/" },		//KEY_PAD_DIVIDE,
	{ "*", "*" },		//KEY_PAD_MULTIPLY,
	{ "-", "-" },		//KEY_PAD_MINUS,
	{ "+", "+" },		//KEY_PAD_PLUS,
	{ "", "" },			//KEY_PAD_ENTER,
	{ ".", ">" },		//KEY_PAD_DECIMAL,
	{ "[", "{" },		//KEY_LBRACKET,
	{ "]", "}" },		//KEY_RBRACKET,
	{ ";", ":" },		//KEY_SEMICOLON,
	{ "'", "@" },		//KEY_APOSTROPHE,
	{ "`", "¬" },		//KEY_BACKQUOTE,
	{ ",", "<" },		//KEY_COMMA,
	{ ".", ">" },		//KEY_PERIOD,
	{ "/", "?" },		//KEY_SLASH,
	{ "\\", "|" },		//KEY_BACKSLASH,
	{ "-", "_" },		//KEY_MINUS,
	{ "=", "+" },		//KEY_EQUAL,
	{ "", "" },			//KEY_ENTER,
	{ "", "" },			//KEY_SPACE,
	{ "", "" },			//KEY_BACKSPACE,
	{ "", "" },			//KEY_TAB,
	{ "", "" },			//KEY_CAPSLOCK,
	{ "", "" },			//KEY_NUMLOCK,
	{ "", "" },			//KEY_ESCAPE,
	{ "", "" },			//KEY_SCROLLLOCK,
	{ "", "" },			//KEY_INSERT,
	{ "", "" },			//KEY_DELETE,
	{ "", "" },			//KEY_HOME,
	{ "", "" },			//KEY_END,
	{ "", "" },			//KEY_PAGEUP,
	{ "", "" },			//KEY_PAGEDOWN,
	{ "", "" },			//KEY_BREAK,
	{ "", "" },			//KEY_LSHIFT,
	{ "", "" },			//KEY_RSHIFT,
	{ "", "" },			//KEY_LALT,
	{ "", "" },			//KEY_RALT,
	{ "", "" },			//KEY_LCONTROL,
	{ "", "" },			//KEY_RCONTROL,
	{ "", "" },			//KEY_LWIN,
	{ "", "" },			//KEY_RWIN,
	{ "", "" },			//KEY_APP,
	{ "", "" },			//KEY_UP,
	{ "", "" },			//KEY_LEFT,
	{ "", "" },			//KEY_DOWN,
	{ "", "" },			//KEY_RIGHT,
	{ "", "" },			//KEY_F1,
	{ "", "" },			//KEY_F2,
	{ "", "" },			//KEY_F3,
	{ "", "" },			//KEY_F4,
	{ "", "" },			//KEY_F5,
	{ "", "" },			//KEY_F6,
	{ "", "" },			//KEY_F7,
	{ "", "" },			//KEY_F8,
	{ "", "" },			//KEY_F9,
	{ "", "" },			//KEY_F10,
	{ "", "" },			//KEY_F11,
	{ "", ")" },		//KEY_F12,
	{ "", "" },			//KEY_CAPSLOCKTOGGLE,
	{ "", "" },			//KEY_NUMLOCKTOGGLE,
	{ "", "" },			//KEY_SCROLLLOCKTOGGLE,
	{ "", "" },			//MOUSE_LEFT = MOUSE_FIRST,
	{ "", "" },			//MOUSE_RIGHT,
	{ "", "" },			//MOUSE_MIDDLE,
	{ "", "" },			//MOUSE_4,
	{ "", "" },			//MOUSE_5,
	{ "", "" },			//MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	{ "", "" },			//MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down
};
#pragma endregion

CKeyInput::CKeyInput( void )
{

}

CKeyInput::~CKeyInput( void )
{
	m_strChar.clear( );
}

void CKeyInput::Handle( int iKey )
{
	m_strChar.clear( );

	if( ( GetKeyState( VK_SHIFT ) & 0x8000 ) )
		m_strChar = g_KeyStrokes[ iKey ].m_alt;
	else m_strChar = g_KeyStrokes[ iKey ].m_def;
}

bool CMouseInput::ValidFlags( int flags )
{
	if( flags <= KEY_FLAG_NONE || flags == 3 || flags > KEY_FLAG_MOUSE5 )
		return false;

	return true;
}

CMouseInput::CMouseInput( void )
{
	SetKey( KEY_FLAG_MOUSE1 );
}

CMouseInput::CMouseInput( int flags )
{
	SetKey( flags );
}

bool CMouseInput::InEvent( int flags )
{
	auto bRetVal = false;
	auto iCurFlags = ValidFlags( flags ) ? flags : m_iVirtualKey;
	
	static short last[ 10 ];
	for( int i = 0; i < KEY_FLAG_MOUSE5 + 1; i++ )
	{
		short res = GetKeyState( i );
		if( !( res & 0x8000 ) && last[ i ] & 0x8000 && i == iCurFlags )
			bRetVal = true;
		last[ i ] = res;
	}

	return bRetVal;
}

bool CMouseInput::IsHover( int x, int y, int w, int h )
{
	Update( );
	return( ( m_iXPosition > x && m_iXPosition < x + w ) && ( m_iYPosition > y && y + h > m_iYPosition ) );
}

bool CMouseInput::IsPressed( int flags )
{
	int iCurFlags = ValidFlags( flags ) ? flags : m_iVirtualKey;
	return ( GetKeyState( iCurFlags ) & 0x8000 ) ? true : false;
}

int CMouseInput::x( void )
{
	Update( );
	return m_iXPosition;
}

int CMouseInput::y( void )
{
	Update( );
	return m_iYPosition;
}

void CMouseInput::GetMousePosition( int& x, int& y )
{
	x = m_iXPosition;
	y = m_iYPosition;
}

void CMouseInput::SetKey( int flags )
{
	if( !ValidFlags( flags ) )
		return;

	m_iVirtualKey = flags;
}

void CMouseInput::Update( void )
{
	g_pSurface->GetCursorPos( m_iXPosition, m_iYPosition );
}

void CMenu::Echo( const char* fmt, ... )
{
	va_list args;
	va_start( args, fmt );
	char pszBuffer[ 0x400 ];
	vsprintf_s( pszBuffer, fmt, args );
	va_end( args );
	m_strHistory.push_back( pszBuffer );
}

void CMenu::FilterArgs( std::string strInput, std::vector< std::string >& strArgs )
{
	std::size_t nPos = 0;
	while( true )
	{
		nPos = strInput.find_first_of( " \n\0" );
		if( nPos != std::string::npos )
		{
			strArgs.push_back( strInput.substr( 0, nPos ) );
			strInput.erase( 0, nPos + 1 );
		}
		else
		{
			if( !strInput.empty( ) )
				strArgs.push_back( strInput );

			break;
		}
	}
}

void CMenu::HandleInput( std::string strInput )
{
	if( strInput.empty( ) )
		return;

	std::vector< std::string > strArgs;
	FilterArgs( strInput, strArgs );

	if( strArgs.empty( ) )
		return;

	if( !strArgs[ 0 ].compare( "clear" ) )
	{
		m_strHistory.clear( );
		return;
	}

	Echo( "] %s", strInput.c_str( ) );
	if( !strArgs[ 0 ].compare( "help" ) )
	{
		for( std::size_t i = 0; i < g_CVars.GetAllCVars( ).size( ); i++ )
		{
			CVar* pCVar = g_CVars.GetAllCVars( )[ i ];
			if( !pCVar )
				continue;

			if( !pCVar->IsCommand( ) )
				continue;

			if( pCVar->HasArgs( ) )
			{
				for( std::size_t j = 0; j < pCVar->GetAllArgs( ).size( ); j++ )
				{
					if( pCVar->GetFloat( ) == pCVar->GetAllArgs( )[ j ].m_flValue )
						Echo( "%s = %s(%s) // %s", pCVar->GetName( ).c_str( ), pCVar->GetAllArgs( )[ j ].m_strName.c_str( ), pCVar->GetInfoString( ).c_str( ), pCVar->GetDescription( ).c_str( ) );
				}
			}
			else Echo( "%s = %s // %s", pCVar->GetName( ).c_str( ), pCVar->GetInfoString( ).c_str( ), pCVar->GetDescription( ).c_str( ) );
		}

		return;
	}

	if( g_CVars.IsCVar( strArgs[ 0 ] ) )
	{
		CVar* pCVar = g_CVars.GetCVar( strArgs[ 0 ] );
		if( strArgs.size( ) == 1 )
		{
			if( pCVar->HasArgs( ) )
			{
				for( std::size_t i = 0; i < pCVar->GetAllArgs( ).size( ); i++ )
				{
					if( pCVar->GetFloat( ) == pCVar->GetAllArgs( )[ i ].m_flValue )
						Echo( "%s = %s(%s) // %s", pCVar->GetName( ).c_str( ), pCVar->GetAllArgs( )[ i ].m_strName.c_str( ), pCVar->GetInfoString( ).c_str( ), pCVar->GetDescription( ).c_str( ) );
				}
			}
			else Echo( "%s = %s // %s", pCVar->GetName( ).c_str( ), pCVar->GetInfoString( ).c_str( ), pCVar->GetDescription( ).c_str( ) );

			return;
		}

		if( isdigit( strArgs[ 1 ].c_str( )[ 0 ] ) )
		{
			float flValue = std::strtof( strArgs[ 1 ].c_str( ), NULL );
			pCVar->Set( flValue );

			if( pCVar->HasArgs( ) )
			{
				for( std::size_t i = 0; i < pCVar->GetAllArgs( ).size( ); i++ )
				{
					if( pCVar->GetAllArgs( )[ i ].m_flValue == pCVar->GetFloat( ) )
					{
						Echo( "set %s to %s(%s)", pCVar->GetName( ).c_str( ), pCVar->GetAllArgs( )[ i ].m_strName.c_str( ), pCVar->GetInfoString( ).c_str( ) );
						return;
					}
				}
			}

			Echo( "set %s to %s", pCVar->GetName( ).c_str( ), pCVar->GetInfoString( ).c_str( ) );
			return;
		}
		else
		{
			std::transform( strArgs[ 1 ].begin( ), strArgs[ 1 ].end( ), strArgs[ 1 ].begin( ), ::tolower );
			bool bTrue = ( strArgs[ 1 ].compare( "true" ) == 0 ) ? true : false;
			bool bFalse = ( strArgs[ 1 ].compare( "false" ) == 0 ) ? true : false;

			if( bTrue || bFalse )
			{
				pCVar->Set( bTrue );

				if( bTrue )
				{
					if( pCVar->HasArgs( ) )
					{
						for( std::size_t i = 0; i < pCVar->GetAllArgs( ).size( ); i++ )
						{
							if( pCVar->GetAllArgs( )[ i ].m_flValue == pCVar->GetFloat( ) )
							{
								Echo( "set %s to %s(%s)", pCVar->GetName( ).c_str( ), pCVar->GetAllArgs( )[ i ].m_strName.c_str( ), pCVar->GetInfoString( ).c_str( ) );
								return;
							}
						}
					}
				}

				Echo( "set %s to %s", pCVar->GetName( ).c_str( ), pCVar->GetBool( ) ? "true" : "false" );
				return;
			}

			if( pCVar->HasArgs( ) )
			{
				for( std::size_t i = 0; i < pCVar->GetAllArgs( ).size( ); i++ )
				{
					if( !pCVar->GetAllArgs( )[ i ].m_strName.compare( strArgs[ 1 ] ) )
					{
						pCVar->SetByArg( strArgs[ 1 ] );
						Echo( "set %s to %s(%s)", pCVar->GetName( ).c_str( ), strArgs[ 1 ].c_str( ), pCVar->GetInfoString( ).c_str( ) );
						return;
					}
				}
			}
		}
	}
}

void CMenu::RenderTab( int x, int y, int w, int h, std::string strText, int iIndex, int& iStatus )
{
	auto bActive = ( iIndex == iStatus );
	auto bHover = m_pMouseInput->IsHover( x, y, w, h );
	auto color = ValveSDK::Color( 30, 30, 30, 230 );

	if( bActive )
		color = ValveSDK::Color( 0, 162, 232, 230 );
	else if( bHover )
		color = ValveSDK::Color( 0, 122, 174, 230 );

	if( bHover && m_pMouseInput->InEvent( ) )
		iStatus = iIndex;

	g_pRenderSurface->Rect( x, y, w, h, color );
	
	int iFontSize[ 2 ] = { 0 };
	g_pRenderSurface->GetTextSize( "Tabpage", strText.c_str( ), iFontSize );
	g_pRenderSurface->String( x + ( w / 2 ) - ( iFontSize[ 0 ] / 2 ), y + ( h / 2 ) - ( iFontSize[ 1 ] / 2 ), ValveSDK::Color( 255, 255, 255, 240 ), "Tabpage", strText.c_str( ) );
}

void CMenu::RenderCheckbox( int x, int y, std::string strText, std::string strCVar )
{
	auto pCVar = g_CVars.GetCVar( strCVar );
	if( !pCVar )
		return;

	auto bActive = pCVar->GetBool( );
	auto bHover = m_pMouseInput->IsHover( x, y, 20, 20 );

	static auto size = 20;
	g_pRenderSurface->Rect( x, y, size, size, ValveSDK::Color( 50, 50, 50, 240 ) );
	if( bActive )
		g_pRenderSurface->Rect( x, y, size, size, ValveSDK::Color( 0, 162, 232, 230 ) );
	else g_pRenderSurface->Rect( x, y, 2, size, ValveSDK::Color( 0, 162, 232, 230 ) );

	int iFontSize[ 2 ] = { 0 };
	g_pRenderSurface->GetTextSize( "Tahoma", strText, iFontSize );
	g_pRenderSurface->String( x + size + 5, y + ( size / 2 ) - ( iFontSize[ 1 ] / 2 ), ValveSDK::Color( 255, 255, 255, 230 ), "Tahoma", strText.c_str( ) );

	if( pCVar && bHover && m_pMouseInput->InEvent( ) )
	{
		pCVar->Set( !bActive );
	}
	
}

void CMenu::RenderSlider( int x, int y, int w, int h, std::string strText, std::string strCVar )
{
	auto pCVar = g_CVars.GetCVar( strCVar );
	if( !pCVar )
		return;

	g_pRenderSurface->Rect( x, y, w, h, ValveSDK::Color( 50, 50, 50, 240 ) );

	auto bHover = m_pMouseInput->IsHover( x, y, w, h );
	auto flValue = pCVar->GetFloat( );
	auto flStep = float( ( w / pCVar->GetMax( ) ) * flValue );

	int iCursorPos[ 2 ] = { 0 };
	m_pMouseInput->GetMousePosition( iCursorPos[ 0 ], iCursorPos[ 1 ] );

	float flDelta[ 2 ] = { 0.f };
	flDelta[ 0 ] = float( iCursorPos[ 0 ] - x );
	flDelta[ 1 ] = float( iCursorPos[ 1 ] );

	bHover = m_pMouseInput->IsHover( x - 3, y, w + 5, h );
	if( m_pMouseInput->IsPressed( ) && bHover )
	{
		if( !( flDelta[ 0 ] >= 0.f ) || !( flDelta[ 0 ] <= w + 5 ) )
			return;

		flValue = ceil( pCVar->GetMin( ) + ( ( pCVar->GetMax( ) + pCVar->GetMin( ) ) * ( flDelta[ 0 ] / w ) ) );
		pCVar->Set( flValue );
		
		flStep = flDelta[ 0 ];
		
	}

	char pszBuffer[ 0x20 ];
	sprintf_s( pszBuffer, "%d", ( int )flValue );

	auto strInfo = strText + std::string( ": " ) + pszBuffer;
	int iFontSize[ 2 ] = { 0 };

	g_pRenderSurface->GetTextSize( "Tahoma", strInfo, iFontSize );
	g_pRenderSurface->Rect( x, y, flStep, h, ValveSDK::Color( 0, 162, 232, 200 ) );
	g_pRenderSurface->String( x + ( w / 2 ) - ( iFontSize[ 0 ] / 2 ), y + ( h / 2 ) - ( iFontSize[ 1 ] / 2 ), ValveSDK::Color( 255, 255, 255, 240 ), "Tahoma", strInfo.c_str( ) );
}

void CMenu::RenderComboBox( int x, int y, int w, int h, std::vector< std::string > strNodes, std::string strCVar, bool& bState )
{
	auto pCVar = g_CVars.GetCVar( strCVar );
	if( !pCVar )
		return;

	auto iIndex = pCVar->GetInt( );
	auto nSize = strNodes.size( );

	if( iIndex >= ( int )nSize )
		iIndex = ( int )nSize - 1;

	int iFontSize[ 2 ] = { 0 };
	auto strCurrentString = strNodes[ iIndex ];

	g_pRenderSurface->GetTextSize( "Tahoma", strCurrentString, iFontSize );
	g_pRenderSurface->Rect( x, y, w, h, ValveSDK::Color( 50, 50, 50, 230 ) );
	g_pRenderSurface->Rect( x + w - h, y, h, h, ValveSDK::Color( 0, 122, 174, 230 ) );
	g_pRenderSurface->String( x + 5, y + ( h / 2 ) - ( iFontSize[ 1 ] / 2 ), ValveSDK::Color( 255, 255, 255, 230 ), "Tahoma", strCurrentString.c_str( ) );

	if( m_pMouseInput->IsHover( x + w - h, y, h, h ) && m_pMouseInput->InEvent( ) )
		bState = !bState;

	if( bState )
	{
		auto Y = y + h;
		for( int i = 0; i < ( int )nSize; i++ )
		{
			auto bHover = m_pMouseInput->IsHover( x, Y + ( i * iFontSize[ 1 ] ), w, iFontSize[ 1 ] );

			g_pRenderSurface->Rect( x, Y + ( i * iFontSize[ 1 ] ), w, iFontSize[ 1 ], bHover ? ValveSDK::Color( 70, 70, 70, 230 ) : ValveSDK::Color( 50, 50, 50, 230 ) );
			g_pRenderSurface->String( x + 5, Y + ( i * iFontSize[ 1 ] ), ValveSDK::Color( 255, 255, 255, 230 ), "Tahoma", strNodes[ i ].c_str( ) );

			if( bHover && m_pMouseInput->InEvent( ) )
			{
				pCVar->Set( i );
				bState = false;
			}
		}

		if( m_pMouseInput->InEvent( ) && !m_pMouseInput->IsHover( x, Y, w, iFontSize[ 1 ] * nSize ) )
			bState = false;
	}
}

void CMenu::RenderAimbotTab( int x, int y, int w, int h )
{
	static std::string strCheckboxes[ 10 ] = { "Active", "Autoshoot", "Autowall", "Distancebased FoV", "Recoil Control System", "No Recoil", "No Spread", "Weapon Config" };
	static std::string strCheckboxesCVars[ 10 ] = { "aim_active", "aim_autoshoot", "aim_autowall", "aim_distancebased", "aim_rcs", "aim_norecoil", "aim_nospread", "aim_weapons" };
	for( int i = 0; i < 8; i++ )
		RenderCheckbox( x, y + ( i * 20 ) + ( i * 5 ), strCheckboxes[ i ], strCheckboxesCVars[ i ] );

	static std::string strSlider[ 10 ] = { "FoV", "Smooth", "Time", "Smart Aim", "Autowall Damage" };
	static std::string strSliderCVars[ 10 ] = { "aim_fov", "aim_smooth", "aim_time", "aim_smart", "aim_autowall_damage" };	
	for( int i = 0; i < 5; i++ )
		RenderSlider( x, y + h - 205 + ( i * 25 ) + ( i * 10 ), w, 25, strSlider[ i ], strSliderCVars[ i ] );

	static std::string strComboboxLabel[ 10 ] = { "Hitbox:", "Smart Hitbox:", "Aim At:", "Hitscan:", "Silent Aim:", "Hitchance:" };
	int iFontSize[ 2 ] = { 0 };
	g_pRenderSurface->GetTextSize( "Tahoma", strComboboxLabel[ 0 ], iFontSize );
	for( int i = 0; i < 5; i++ )
		g_pRenderSurface->String( x + 230, y + 10 - ( iFontSize[ 1 ] / 2 ) + ( i * 25 ), ValveSDK::Color( 255, 255, 255, 230 ), "Tahoma", strComboboxLabel[ i ].c_str( ) );
	
	
	if( !m_bAimHitboxCombo && !m_bSmartHitboxCombo && !m_bAimAtCombo && !m_bAimHitscanCombo )
		RenderComboBox( x + 315, y + 100, 250, 20, m_strSilent, "aim_silent", m_bAimSilentCombo );
	if( !m_bAimHitboxCombo && !m_bSmartHitboxCombo && !m_bAimAtCombo )
		RenderComboBox( x + 315, y + 75, 250, 20, m_strHitscans, "aim_hitscan", m_bAimHitscanCombo );
	if( !m_bAimHitboxCombo && !m_bSmartHitboxCombo )
		RenderComboBox( x + 315, y + 50, 250, 20, m_strAimAt, "aim_at", m_bAimAtCombo );
	if( !m_bAimHitboxCombo )
		RenderComboBox( x + 315, y + 25, 250, 20, m_strHitboxes, "aim_smart_hitbox", m_bSmartHitboxCombo );
	RenderComboBox( x + 315, y, 250, 20, m_strHitboxes, "aim_hitbox", m_bAimHitboxCombo );
}

void CMenu::RenderVisualsTab( int x, int y, int w, int h )
{
	static std::string strCheckboxes[ 10 ] = { "Active", "Enemy Only", "Box Outlined", "Wireframe Chams" };
	static std::string strCheckboxesCVars[ 10 ] = { "vis_active", "vis_enemyonly", "vis_box_outlined", "vis_chams_wireframe" };
	for( int i = 0; i < 4; i++ )
		RenderCheckbox( x, y + ( i * 20 ) + ( i * 5 ), strCheckboxes[ i ], strCheckboxesCVars[ i ] );

	static std::string strComboboxLabel[ 10 ] = { "Bounding Box:", "Weapons:", "Hands:", "Chams:" };
	int iFontSize[ 2 ] = { 0 };
	g_pRenderSurface->GetTextSize( "Tahoma", strComboboxLabel[ 0 ], iFontSize );
	for( int i = 0; i < 4; i++ )
		g_pRenderSurface->String( x + 230, y + 10 - ( iFontSize[ 1 ] / 2 ) + ( i * 25 ), ValveSDK::Color( 255, 255, 255, 230 ), "Tahoma", strComboboxLabel[ i ].c_str( ) );
	
	if( !m_bVisBoxCombo && !m_bVisWeaponsCombo && !m_bVisHandsCombo )
		RenderComboBox( x + 315, y + 75, 250, 20, m_strVisChams, "vis_chams", m_bVisChamsCombo );
	if( !m_bVisBoxCombo && !m_bVisWeaponsCombo )
		RenderComboBox( x + 315, y + 50, 250, 20, m_strVisHands, "vis_hands", m_bVisHandsCombo );
	if( !m_bVisBoxCombo )
		RenderComboBox( x + 315, y + 25, 250, 20, m_strVisWeapons, "vis_weapons", m_bVisWeaponsCombo );
	RenderComboBox( x + 315, y, 250, 20, m_strVisBoxes, "vis_box", m_bVisBoxCombo );

}

void CMenu::RenderMiscTab( int x, int y, int w, int h )
{
	static std::string strCheckboxes[ 10 ] = { "Bunnyhop", "Autostrafe", "Visual No Recoil", "Spam on round start", "Spam 1TAP on Headshot", "Spam Sound" };
	static std::string strCheckboxesCVars[ 10 ] = { "misc_bunnyhop", "misc_bunnyhop", "misc_visnorecoil", "spam_roundstart", "spam_1tap", "spam_sound" };
	for( int i = 0; i < 6; i++ )
		RenderCheckbox( x, y + ( i * 20 ) + ( i * 5 ), strCheckboxes[ i ], strCheckboxesCVars[ i ] );
}

void _FixPos( int& x, int& y, int X, int Y )
{
	x += X;
	y += Y;
}
void _FixSize( int& w, int& h, int W, int H )
{
	w += W;
	h += H;
}

void CMenu::RenderConsole( int x, int y, int w, int h )
{
	int iFontSize[ 2 ] = { 0 };
	if( !m_strHistory.empty( ) )
	{
		auto X = x + 5;
		if( m_strHistory.size( ) < 34 )
		{
			for( std::size_t i = 0; i < m_strHistory.size( ); i++ )
			{
				g_pRenderSurface->GetTextSize( "Tahoma", m_strHistory[ i ], iFontSize );
				auto Y = y + ( i * iFontSize[ 1 ] ) + 2;
				g_pRenderSurface->String( X, Y, ValveSDK::Color( 255, 255, 255, 230 ), "Tahoma", m_strHistory[ i ].c_str( ) );
			}
		}
		else
		{
			for( std::size_t i = 0; i < 34; i++ )
			{
				g_pRenderSurface->GetTextSize( "Tahoma", m_strHistory[ i ], iFontSize );
				auto Y = y + ( i * iFontSize[ 1 ] ) + 2;
				g_pRenderSurface->String( X, Y, ValveSDK::Color( 255, 255, 255, 230 ), "Tahoma", m_strHistory[ i + m_strHistory.size( ) - 34 ].c_str( ) );
			}
		}
	}

	_FixPos( x, y, 0, h - 20 );
	_FixSize( w, h, 0, -h + 20 );
	g_pRenderSurface->GardientRect( x - 15, y, w / 2 + 15, 3, ValveSDK::Color( 0, 160, 255, 200 ), ValveSDK::Color( 160, 0, 255, 200 ), 1 );
	g_pRenderSurface->GardientRect( x + w / 2, y, w / 2 + 15, 3, ValveSDK::Color( 160, 0, 255, 200 ), ValveSDK::Color( 255, 255, 0, 200 ), 1 );
	_FixPos( x, y, 0, 5 );
	_FixSize( w, h, 0, 5 );

	if( !m_strCurrentInput.empty( ) )
	{
		g_pRenderSurface->GetTextSize( "Tahoma", m_strCurrentInput, iFontSize );
		g_pRenderSurface->String( x - 10, y + ( h / 2 ) - ( iFontSize[ 1 ] / 2 ), ValveSDK::Color( 255, 255, 255, 230 ), "Tahoma", m_strCurrentInput.c_str( ) );
	}
}

void CMenu::Drag( int w, int h )
{
	if( !m_pMouseInput )
		return;

	static int iXDif = 0;
	static int iYDif = 0;

	int iMousePosition[ 2 ] = { 0 };
	m_pMouseInput->GetMousePosition( iMousePosition[ 0 ], iMousePosition[ 1 ] );

	int iCurrentPosition[ 2 ] = { m_iX, m_iY };

	if( m_pMouseInput->IsHover( iCurrentPosition[ 0 ], iCurrentPosition[ 1 ], w, h ) && m_pMouseInput->IsPressed( ) )
	{
		if( iXDif == -1 || iYDif == -1 )
		{
			iXDif = iMousePosition[ 0 ] - m_iX;
			iYDif = iMousePosition[ 1 ] - m_iY;
		}
		m_iX += iMousePosition[ 0 ] - ( iXDif + iCurrentPosition[ 0 ] );
		m_iY += iMousePosition[ 1 ] - ( iYDif + iCurrentPosition[ 1 ] );
	}
	else
	{
		iXDif = -1;
		iYDif = -1;
	}
}

CMenu::CMenu( void )
{
	m_bActive = false;
	m_bAimHitboxCombo = false;
	m_bSmartHitboxCombo = false;
	m_bAimAtCombo = false;
	m_bAimHitscanCombo = false;
	m_bVisBoxCombo = false;
	m_bVisWeaponsCombo = false;

	SetPosition( 100, 20 );
	m_iW = 640;
	m_iH = 600;
	m_iCurrentTap = 0;

	m_pMouseInput = new CMouseInput( 1 );
	m_pKeyInput = new CKeyInput( );

	m_strHitboxes.push_back( "Pelvis" );
	m_strHitboxes.push_back( "Left Thigh" );
	m_strHitboxes.push_back( "Left Calf" );
	m_strHitboxes.push_back( "Left Foot" );
	m_strHitboxes.push_back( "Right Thigh" );
	m_strHitboxes.push_back( "Right Calf" );
	m_strHitboxes.push_back( "Right Foot" );
	m_strHitboxes.push_back( "Spine1" );
	m_strHitboxes.push_back( "Spine2" );
	m_strHitboxes.push_back( "Spine3" );
	m_strHitboxes.push_back( "Neck" );
	m_strHitboxes.push_back( "Head" );
	m_strHitboxes.push_back( "Left Upperarm" );
	m_strHitboxes.push_back( "Left Forearm" );
	m_strHitboxes.push_back( "Left Hand" );
	m_strHitboxes.push_back( "Right Upperarm" );
	m_strHitboxes.push_back( "Right Forearm" );
	m_strHitboxes.push_back( "Right Hand" );
	m_strHitboxes.push_back( "Left Clavicle" );
	m_strHitboxes.push_back( "Right Clavicle" );
	m_strHitboxes.push_back( "Helmet" );
	m_strHitboxes.push_back( "Spine4" );
	m_strHitscans.push_back( "Disabled" );
	m_strHitscans.push_back( "Normal" );
	m_strHitscans.push_back( "Through penetrable Walls" );
	m_strAimAt.push_back( "Enemy only" );
	m_strAimAt.push_back( "Team only" );
	m_strAimAt.push_back( "Both" );
	m_strSilent.push_back( "Disabled" );
	m_strSilent.push_back( "Silent" );
	m_strSilent.push_back( "Perfect Silent" );
	m_strVisBoxes.push_back( "Disabled" );
	m_strVisBoxes.push_back( "Border Box" );
	m_strVisBoxes.push_back( "Edge Bounding Box" );
	m_strVisWeapons.push_back( "Disabled" );
	m_strVisWeapons.push_back( "Weapon Symbol" );
	m_strVisWeapons.push_back( "Weapon Name" );
	m_strVisHands.push_back( "Disabled" );
	m_strVisHands.push_back( "Remove Hands " );
	m_strVisHands.push_back( "Wireframe Hands" );
	m_strVisChams.push_back( "Disabled" );
	m_strVisChams.push_back( "Normal" );
	m_strVisChams.push_back( "Full Brightness" );
}

CMenu::~CMenu( void )
{
	SafeDelete( &m_pMouseInput );
}

void CMenu::SetActive( bool active )
{
	m_bActive = active;

	if( g_pEngine->IsIngame( ) )
	{
		char pszBuffer[ 0x200 ];
		sprintf_s( pszBuffer, "cl_mouseenable %d", !active );
		g_pEngine->ClientCmd( pszBuffer );
	}
}

void CMenu::HandleInputChar( int iKey )
{
	if( iKey == ValveSDK::KEY_INSERT )
		SetActive( !m_bActive );

	if( !m_bActive )
		return;

	if( m_iCurrentTap != 3 )
		return;

	if( !m_pKeyInput )
		return;

	m_pKeyInput->Handle( iKey );

	switch( iKey )
	{
	case ValveSDK::KEY_ENTER:
		HandleInput( m_strCurrentInput );
		m_strCurrentInput.clear( );
		return;
	case ValveSDK::KEY_SPACE:
		m_strCurrentInput.append( " " );
		return;
	case ValveSDK::KEY_BACKSPACE:
		if( !m_strCurrentInput.empty( ) )
			m_strCurrentInput.erase( m_strCurrentInput.length( ) - 1 );
		return;
	}

	m_strCurrentInput.append( m_pKeyInput->m_strChar );
}

void CMenu::Render( void )
{
	if( !m_bActive )
		return;

	auto x = m_iX;
	auto y = m_iY;
	auto w = m_iW;
	auto h = m_iH;
	Drag( w, 25 );

	g_pRenderSurface->RectOutlined( x, y, w, h, 1, ValveSDK::Color( 50, 50, 50, 230 ), ValveSDK::Color( 0, 0, 0 ) );
	x += 5;
	y += 25;
	w -= 10;
	h -= 30;
	g_pRenderSurface->RectOutlined( x, y, w, h, 1, ValveSDK::Color( 30, 30, 30, 220 ), ValveSDK::Color( 0, 0, 0 ) );
	g_pRenderSurface->GardientRect( x, y, w / 2, 3, ValveSDK::Color( 0, 160, 255, 200 ), ValveSDK::Color( 160, 0, 255, 200 ), 1 );
	g_pRenderSurface->GardientRect( x + w / 2, y, w / 2, 3, ValveSDK::Color( 160, 0, 255, 200 ), ValveSDK::Color( 255, 255, 0, 200 ), 1 );
	y += 3;
	h -= 3;

	// render the menu main tabs
	static auto tabsize = w / 5;
	static std::string strTabs[ 5 ] = { "Aim Interface", "Visuals", "Misc", "Console", "Playerlist" };
	for( int i = 0; i < 5; i++ )
		RenderTab( x + ( i * tabsize ), y, tabsize, 30, strTabs[ i ], i, m_iCurrentTap );

	x += 5;
	y += 40;
	w -= 10,
	h -= 60;
	
	switch( m_iCurrentTap )
	{
	case 0:
		RenderAimbotTab( x + 10, y + 10, w - 20, h );
		break;
	case 1:
		RenderVisualsTab( x + 10, y + 10, w - 20, h );
		break;
	case 2:
		RenderMiscTab( x + 10, y + 10, w - 20, h );
		break;
	case 3:
		RenderConsole( x + 10, y + 10, w - 20, h );
		break;
	}

	int iCursorPos[ 2 ] = { 0 };
	m_pMouseInput->GetMousePosition( iCursorPos[ 0 ], iCursorPos[ 1 ] );
	g_pRenderSurface->Circle( iCursorPos[ 0 ] + 3, iCursorPos[ 1 ] + 5, 6, 3, ValveSDK::Color( 0, 0, 0 ) );
	g_pRenderSurface->Circle( iCursorPos[ 0 ] + 3, iCursorPos[ 1 ] + 5, 5, 3, ValveSDK::Color( 255, 255, 255 ) );
	g_pRenderSurface->Circle( iCursorPos[ 0 ] + 3, iCursorPos[ 1 ] + 5, 4, 3, ValveSDK::Color( 255, 255, 255 ) );
	g_pRenderSurface->Circle( iCursorPos[ 0 ] + 3, iCursorPos[ 1 ] + 5, 3, 3, ValveSDK::Color( 255, 255, 255 ) );
	g_pRenderSurface->Circle( iCursorPos[ 0 ] + 3, iCursorPos[ 1 ] + 5, 2, 3, ValveSDK::Color( 255, 255, 255 ) );
	g_pRenderSurface->Circle( iCursorPos[ 0 ] + 3, iCursorPos[ 1 ] + 5, 1, 3, ValveSDK::Color( 255, 255, 255 ) );
}

void CMenu::SetPosition( int x, int y )
{
	m_iX = x;
	m_iY = y;
}

CMenu* g_pMenu = nullptr;