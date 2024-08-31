#include "Color Manager.h" // Base Header
#include "SDK.h"
//===================================================================================


#define CHEAT_ORANGE COLORCODE( 255, 100, 0, 200 )
#define CHEAT_YELLOW COLORCODE( 255, 255, 0, 200 )
#define CHEAT_PURPLE COLORCODE( 55, 25, 128, 200 )
#define CHEAT_RED COLORCODE( 255, 0, 0, 200 )
#define CHEAT_GREEN COLORCODE( 0, 255, 0, 200 )
#define CHEAT_BLUE COLORCODE( 0, 0, 255, 200 )
#define CHEAT_BLACK COLORCODE( 0, 0, 0, 200 )
#define CHEAT_WHITE COLORCODE( 255, 255, 255, 200 )
#define CHEAT_PINK COLORCODE( 255, 0, 255, 200 )
//===================================================================================
void CColorManager::Initialize( void )
{
	AddColor("objectives", CHEAT_BLUE);	// 0
	AddColor( "teamone",	COLORCODE( 153, 194, 216, 255 )		);	// 1
	AddColor( "teamtwo",	COLORCODE( 255, 000, 000, 255 )		);	// 2 //terror	
	AddColor( "teamthree",	COLORCODE( 77, 77, 255, 255)		);	// 3 // CT
	AddColor( "teamfour",	COLORCODE( 255, 128, 0, 255 )		);	// 4
	AddColor( "background", COLORCODE(  30,  30,  30, 128 )		);	// 5
	AddColor( "menu_on",	COLORCODE(  0,  128, 255, 255 )		);	// 6
	AddColor( "menu_off",	COLORCODE( 255, 255, 255, 255 )		);	// 7
	AddColor("menu_color", COLORCODE(100,255,100,255));	// 7
}
//===================================================================================
// Basically, you could just get the color without the index, 
// just use the second function that searches the corresponding color by name comparison
//===================================================================================
DWORD CColorManager::dwGetColor( int iIndex )
{
	if ( iIndex < 0 || ( unsigned int )iIndex > m_Colors.size() )
	{	
		return 0xFFFFFFFF;
	}

	return m_Colors[ iIndex ].dwColor;
}
//===================================================================================
DWORD CColorManager::dwGetColor( const char* pszName )
{
	for (auto item = m_Colors.begin(); item != m_Colors.end();item++)
	{
		if ( streql(item->strName.c_str(),pszName) )
		{
			return item->dwColor;
		}
	}
	return 0xFFFFFFFF;
}
//===================================================================================
void CColorManager::SetColor( const char* pszName, DWORD dwNewColor )
{
	for (auto item = m_Colors.begin(); item != m_Colors.end();item++)
	{
		if ( streql(item->strName.c_str(),pszName) )
		{
			item->dwColor = dwNewColor;
		}
	}
}
//===================================================================================
void CColorManager::AddColor( const char* pszName, DWORD dwNewColor )
{
	color_t color;
	color.dwColor = dwNewColor;
	color.strName = pszName;

	m_Colors.push_back( color );
}
//===================================================================================