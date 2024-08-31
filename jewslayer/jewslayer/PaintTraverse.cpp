#include "PaintTraverse.h"
#include "Menu.h"
#include "Visuals.h"

typedef void( __thiscall* oPaintTraverse )( ValveSDK::IPanel*, unsigned int, bool, bool );
void __fastcall hkPaintTraverse( ValveSDK::IPanel* thisptr, int edx, unsigned int VGUIPanel, bool forceRepaint, bool allowForce )
{	
	g_pPanelVMTHook->GetMethod< oPaintTraverse >( 41 )( thisptr, VGUIPanel, forceRepaint, allowForce );

	g_pRenderSurface->AddFont( "Arial", "Arial", 14, 400, 0, 0, ValveSDK::FONTFLAG_ANTIALIAS );
	g_pRenderSurface->AddFont( "Tabpage", "Tahoma", 18, 400, 0, 0, ValveSDK::FONTFLAG_ANTIALIAS );
	g_pRenderSurface->AddFont( "Tahoma", "Tahoma", 14, 400, 0, 0, ValveSDK::FONTFLAG_ANTIALIAS );
	g_pRenderSurface->CreateAllFonts( );
	
	if( !thisptr->GetName( VGUIPanel ).compare( "MatSystemTopPanel" ) )
	{
		g_pRenderSurface->String( 5, 5, ValveSDK::Color( 255, 255, 255 ), "Arial", "Jewslayer" );
		
		ValveSDK::CBaseEntity* pLocal = g_pTools->GetLocalPlayer( );
		if( pLocal )
		{
			g_pVisuals->Main( pLocal );
		}		
		
		g_pMenu->Render( );
	}
}