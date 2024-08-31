#pragma once

// Windows
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <io.h>
#include <time.h>
#include <string>
#include <cmath>
#include <vector>

// DirectX Headers
#include <d3d11.h> 
#include "d3d9.h"
#include "d3d9Types.h"
#include "ddraw.h"

// DirectX Libraries
#pragma comment(lib, "d3d11.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "DDRAW.lib")
#pragma comment (lib, "Winmm.lib")
#pragma comment(lib, "user32.lib")
// Engine Classes
/*#include "draw.h"
#include "cConfigs.h"*/

// Hooking
#include "VMTHook.h"

#ifndef CLIENT_DLL
#define CLIENT_DLL
#endif

#include <stdio.h>
#include <vector>
#include <string>
#include <d3d9.h>
#include <time.h>
#include <iostream>
#include <sstream>

#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN

#include "public\\tier0\\wchartypes.h"

// Public
// #include "ILuaInterface.h"
#include "public\\cdll_int.h"
#include "public\\iprediction.h"
#include "public\\bone_setup.h"
#include "public\\icliententitylist.h"
#include "public\\ienginevgui.h"
#include "public\\IGameUIFuncs.h"
#include "public\\dlight.h"
#include "public\\r_efx.h" 
#include "public\\igameevents.h"
#include "public\\view_shared.h"
#include "public\\inetchannel.h"
#include "public\\iachievementmgr.h"
#include "netadr.h"
#include <Color.h>
// Client
#include "game\\client\\imessagechars.h"
#include "game\\client\\iclientmode.h"
#include "game\\client\\cliententitylist.h"
#include "game\\client\\cdll_client_int.h"
#include "game\\client\\cbase.h"
#include "game\\client\\c_baseanimating.h"
#include "game\\client\\c_basecombatweapon.h"
#include "game\\client\\c_baseplayer.h"
#include "game\\client\\c_baseentity.h"
#include "game\\client\\enginesprite.h"
#include "game\\client\\input.h"
#include "dbg.h"

//#include "game\\client\\iinput.h"
#include "game\\client\\c_playerresource.h"
#include "game\\client\\iviewrender.h"
#include "game\\client\\viewrender.h"
#include "game\\client\\game_controls\\commandmenu.h"
#include "game\\client\\hudelement.h"




#include "public\\engine\\ivmodelrender.h"
#include "public\\engine\\ivdebugoverlay.h"
#include "public\\engine\\ivmodelinfo.h"
#include "public\\engine\\IEngineTrace.h"
#include "public\\engine\\IEngineSound.h"
#include "inetchannel.h"

// Material System
#include "public\\materialsystem\\imaterialsystemstub.h"
#include "public\\materialsystem\\itexture.h"
#include "public\\materialsystem\\IMaterialVar.h"
#include "public\\tier1\\checksum_md5.h"
// VGUI
#include "public\\matsys_controls\\matsyscontrols.h"
#include "public\\vgui\\IClientPanel.h"
#include "public\\vgui\\IPanel.h"
#include "public\\vgui\\ISurface.h"
#include "public\\vgui\\ILocalize.h"
#include "public\\collisionutils.h"
#include "public\\vstdlib\\random.h"


// VGUI Controls
#include "public\\vgui_controls\\Panel.h"

// VGUI Material Surface
#include "public\\VGuiMatSurface\\IMatSystemSurface.h"
#include "public\\mathlib\\vector.h"

// Shared
#include "game\\shared\\usermessages.h"
#include "game\\shared\\basecombatweapon_shared.h"
#include "game\\shared\\takedamageinfo.h"
#include "game\\shared\\igamemovement.h"
// #include "cprediction.h"

#pragma comment(lib, "C:/hl2sdk-gmod/lib/public/tier0.lib")
#pragma comment(lib, "C:/hl2sdk-gmod/lib/public/tier1.lib")
#pragma comment(lib, "C:/hl2sdk-gmod/lib/public/tier2.lib")
#pragma comment(lib, "C:/hl2sdk-gmod/lib/public/tier3.lib")
#pragma comment(lib, "C:/hl2sdk-gmod/lib/public/mathlib.lib")
#pragma comment(lib, "C:/hl2sdk-gmod/lib/public/vstdlib.lib")

#include "io.h"

#include "ISteamClient012.h"
#include "ISteamFriends010.h"

#define IsValid( pointer )				( pointer && pointer != 0 && HIWORD( pointer ) )
#define print(strText) MessageBoxA(0, strText, "BigHack", 0);

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)	// Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
// Auto reconstructed from vtable block @ 0x000DFF48
// from "vguimatsurface.dylib", by VTableRec.idc
class CMatSystemSurface
{
public:													//  Index Offset
	virtual void* CMatSystemSurface::Connect(void * (*)(char  const*, int *));								// 0000  0000
	virtual void* CMatSystemSurface::Disconnect(void);								// 0001  0004
	virtual void* CMatSystemSurface::QueryInterface(char  const*);								// 0002  0008
	virtual void* CMatSystemSurface::Init(void);								// 0003  000C
	virtual void* CMatSystemSurface::Shutdown(void);								// 0004  0010
	virtual void* CMatSystemSurface::RunFrame(void);								// 0005  0014
	virtual void* CMatSystemSurface::GetEmbeddedPanel(void);								// 0006  0018
	virtual void* CMatSystemSurface::SetEmbeddedPanel(unsigned int);								// 0007  001C
	virtual void* CMatSystemSurface::PushMakeCurrent(unsigned int, bool);								// 0008  0020
	virtual void* CMatSystemSurface::PopMakeCurrent(unsigned int);								// 0009  0024
	virtual void* CMatSystemSurface::DrawSetColor(int, int, int, int);								// 0010  0028
	virtual void* CMatSystemSurface::DrawSetColor(Color);								// 0011  002C
	virtual void* CMatSystemSurface::DrawFilledRect(int, int, int, int);								// 0012  0030
	virtual void* CMatSystemSurface::DrawFilledRectArray(vgui::IntRect *, int);								// 0013  0034
	virtual void* CMatSystemSurface::DrawOutlinedRect(int, int, int, int);								// 0014  0038
	virtual void* CMatSystemSurface::DrawLine(int, int, int, int);								// 0015  003C
	virtual void* CMatSystemSurface::DrawPolyLine(int *, int *, int);								// 0016  0040
	virtual void* CMatSystemSurface::DrawSetTextFont(unsigned long);								// 0017  0044
	virtual void* CMatSystemSurface::DrawSetTextColor(int, int, int, int);								// 0018  0048
	virtual void* CMatSystemSurface::DrawSetTextColor(Color);								// 0019  004C
	virtual void* CMatSystemSurface::DrawSetTextPos(int, int);								// 0020  0050
	virtual void* CMatSystemSurface::DrawGetTextPos(int &, int &);								// 0021  0054
	virtual void* CMatSystemSurface::DrawPrintText(wchar_t  const*, int, FontDrawType_t drawType = FONT_DRAW_DEFAULT);								// 0022  0058
	virtual void* CMatSystemSurface::DrawUnicodeChar(wchar_t, vgui::FontDrawType_t);								// 0023  005C
	virtual void* CMatSystemSurface::DrawFlushText(void);								// 0024  0060
	virtual void* CMatSystemSurface::CreateHTMLWindow(vgui::IHTMLEvents *, unsigned int);								// 0025  0064
	virtual void* CMatSystemSurface::PaintHTMLWindow(vgui::IHTML *);								// 0026  0068
	virtual void* CMatSystemSurface::DeleteHTMLWindow(vgui::IHTML *);								// 0027  006C
	virtual void* CMatSystemSurface::DrawGetTextureId(char  const*);								// 0028  0070
	virtual void* CMatSystemSurface::DrawGetTextureFile(int, char *, int);								// 0029  0074
	virtual void* CMatSystemSurface::DrawSetTextureFile(int, char  const*, int, bool);								// 0030  0078
	virtual void* CMatSystemSurface::DrawSetTextureRGBA(int, unsigned char  const*, int, int, int, bool);								// 0031  007C
	virtual void* CMatSystemSurface::DrawSetTexture(int);								// 0032  0080
	virtual void* CMatSystemSurface::DrawGetTextureSize(int, int &, int &);								// 0033  0084
	virtual void* CMatSystemSurface::DrawTexturedRect(int, int, int, int);								// 0034  0088
	virtual void* CMatSystemSurface::IsTextureIDValid(int);								// 0035  008C
	virtual void* CMatSystemSurface::DeleteTextureByID(int);								// 0036  0090
	virtual void* CMatSystemSurface::CreateNewTextureID(bool);								// 0037  0094
	virtual void* CMatSystemSurface::GetScreenSize(int &, int &);								// 0038  0098
	virtual void* CMatSystemSurface::SetAsTopMost(unsigned int, bool);								// 0039  009C
	virtual void* CMatSystemSurface::BringToFront(unsigned int);								// 0040  00A0
	virtual void* CMatSystemSurface::SetForegroundWindow(unsigned int);								// 0041  00A4
	virtual void* CMatSystemSurface::SetPanelVisible(unsigned int, bool);								// 0042  00A8
	virtual void* CMatSystemSurface::SetMinimized(unsigned int, bool);								// 0043  00AC
	virtual void* CMatSystemSurface::IsMinimized(unsigned int);								// 0044  00B0
	virtual void* CMatSystemSurface::FlashWindow(unsigned int, bool);								// 0045  00B4
	virtual void* CMatSystemSurface::SetTitle(unsigned int, wchar_t  const*);								// 0046  00B8
	virtual void* CMatSystemSurface::SetAsToolBar(unsigned int, bool);								// 0047  00BC
	virtual void* CMatSystemSurface::CreatePopup(unsigned int, bool, bool, bool, bool, bool);								// 0048  00C0
	virtual void* CMatSystemSurface::SwapBuffers(unsigned int);								// 0049  00C4
	virtual void* CMatSystemSurface::Invalidate(unsigned int);								// 0050  00C8
	virtual void* CMatSystemSurface::SetCursor(unsigned long);								// 0051  00CC
	virtual void* CMatSystemSurface::SetCursorAlwaysVisible(bool);								// 0052  00D0
	virtual void* CMatSystemSurface::IsCursorVisible(void);								// 0053  00D4
	virtual void* CMatSystemSurface::ApplyChanges(void);								// 0054  00D8
	virtual void* CMatSystemSurface::IsWithin(int, int);								// 0055  00DC
	virtual void* CMatSystemSurface::HasFocus(void);								// 0056  00E0
	virtual void* CMatSystemSurface::SupportsFeature(vgui::ISurface::SurfaceFeature_e);								// 0057  00E4
	virtual void* CMatSystemSurface::RestrictPaintToSinglePanel(unsigned int);								// 0058  00E8
	virtual void* CMatSystemSurface::SetModalPanel(unsigned int);								// 0059  00EC
	virtual void* CMatSystemSurface::GetModalPanel(void);								// 0060  00F0
	virtual void* CMatSystemSurface::UnlockCursor(void);								// 0061  00F4
	virtual void* CMatSystemSurface::LockCursor(void);								// 0062  00F8
	virtual void* CMatSystemSurface::SetTranslateExtendedKeys(bool);								// 0063  00FC
	virtual void* CMatSystemSurface::GetTopmostPopup(void);								// 0064  0100
	virtual void* CMatSystemSurface::SetTopLevelFocus(unsigned int);								// 0065  0104
	virtual HFont CMatSystemSurface::CreateFont(void);								// 0066  0108
	virtual void* CMatSystemSurface::SetFontGlyphSet(unsigned long, char  const*, int, int, int, int, int, int var1 = 0, int var2 = 0);								// 0067  010C
	virtual void* CMatSystemSurface::AddCustomFontFile(char  const*, char  const*);								// 0068  0110
	virtual void* CMatSystemSurface::GetFontTall(unsigned long);								// 0069  0114
	virtual void* CMatSystemSurface::GetFontTallRequested(unsigned long);								// 0070  0118
	virtual void* CMatSystemSurface::GetFontAscent(unsigned long, wchar_t);								// 0071  011C
	virtual void* CMatSystemSurface::IsFontAdditive(unsigned long);								// 0072  0120
	virtual void* CMatSystemSurface::GetCharABCwide(unsigned long, int, int &, int &, int &);								// 0073  0124
	virtual void* CMatSystemSurface::GetCharacterWidth(unsigned long, int);								// 0074  0128
	virtual void* CMatSystemSurface::GetTextSize(unsigned long, wchar_t  const*, int &, int &);								// 0075  012C
	virtual void* CMatSystemSurface::GetNotifyPanel(void);								// 0076  0130
	virtual void* CMatSystemSurface::SetNotifyIcon(unsigned int, unsigned long, unsigned int, char  const*);								// 0077  0134
	virtual void* CMatSystemSurface::PlaySound(char  const*);								// 0078  0138
	virtual void* CMatSystemSurface::GetPopupCount(void);								// 0079  013C
	virtual void* CMatSystemSurface::GetPopup(int);								// 0080  0140
	virtual void* CMatSystemSurface::ShouldPaintChildPanel(unsigned int);								// 0081  0144
	virtual void* CMatSystemSurface::RecreateContext(unsigned int);								// 0082  0148
	virtual void* CMatSystemSurface::AddPanel(unsigned int);								// 0083  014C
	virtual void* CMatSystemSurface::ReleasePanel(unsigned int);								// 0084  0150
	virtual void* CMatSystemSurface::MovePopupToFront(unsigned int);								// 0085  0154
	virtual void* CMatSystemSurface::MovePopupToBack(unsigned int);								// 0086  0158
	virtual void* CMatSystemSurface::SolveTraverse(unsigned int, bool);								// 0087  015C
	virtual void* CMatSystemSurface::PaintTraverse(unsigned int);								// 0088  0160
	virtual void* CMatSystemSurface::EnableMouseCapture(unsigned int, bool);								// 0089  0164
	virtual void* CMatSystemSurface::GetWorkspaceBounds(int &, int &, int &, int &);								// 0090  0168
	virtual void* CMatSystemSurface::GetAbsoluteWindowBounds(int &, int &, int &, int &);								// 0091  016C
	virtual void* CMatSystemSurface::GetProportionalBase(int &, int &);								// 0092  0170
	virtual void* CMatSystemSurface::CalculateMouseVisible(void);								// 0093  0174
	virtual void* CMatSystemSurface::NeedKBInput(void);								// 0094  0178
	virtual void* CMatSystemSurface::HasCursorPosFunctions(void);								// 0095  017C
	virtual void* CMatSystemSurface::SurfaceGetCursorPos(int &, int &);								// 0096  0180
	virtual void* CMatSystemSurface::SurfaceSetCursorPos(int, int);								// 0097  0184
	virtual void* CMatSystemSurface::DrawTexturedLine(vgui::Vertex_t  const&, vgui::Vertex_t  const&);								// 0098  0188
	virtual void* CMatSystemSurface::DrawOutlinedCircle(int, int, int, int);								// 0099  018C
	virtual void* CMatSystemSurface::DrawTexturedPolyLine(vgui::Vertex_t  const*, int);								// 0100  0190
	virtual void* CMatSystemSurface::DrawTexturedSubRect(int, int, int, int, float, float, float, float);								// 0101  0194
	virtual void* CMatSystemSurface::DrawTexturedPolygon(int, vgui::Vertex_t *, bool);								// 0102  0198
	virtual void* CMatSystemSurface::GetTitle(unsigned int);								// 0103  019C
	virtual void* CMatSystemSurface::IsCursorLocked(void)const;								// 0104  01A0
	virtual void* CMatSystemSurface::SetWorkspaceInsets(int, int, int, int);								// 0105  01A4
	virtual void* CMatSystemSurface::DrawGetUnicodeCharRenderInfo(wchar_t, vgui::CharRenderInfo &);								// 0106  01A8
	virtual void* CMatSystemSurface::DrawRenderCharFromInfo(vgui::CharRenderInfo  const&);								// 0107  01AC
	virtual void* CMatSystemSurface::DrawSetAlphaMultiplier(float);								// 0108  01B0
	virtual void* CMatSystemSurface::DrawGetAlphaMultiplier(void);								// 0109  01B4
	virtual void* CMatSystemSurface::SetAllowHTMLJavaScript(bool);								// 0110  01B8
	virtual void* CMatSystemSurface::OnScreenSizeChanged(int, int);								// 0111  01BC
	virtual void* CMatSystemSurface::CreateCursorFromFile(char  const*, char  const*);								// 0112  01C0
	virtual void* CMatSystemSurface::DrawGetTextureMatInfoFactory(int);								// 0113  01C4
	virtual void* CMatSystemSurface::PaintTraverseEx(unsigned int, bool);								// 0114  01C8
	virtual void* CMatSystemSurface::GetZPos(void)const;								// 0115  01CC
	virtual void* CMatSystemSurface::SetPanelForInput(unsigned int);								// 0116  01D0
	virtual void* CMatSystemSurface::DrawFilledRectFastFade(int, int, int, int, int, int, unsigned int, unsigned int, bool);								// 0117  01D4
	virtual void* CMatSystemSurface::DrawFilledRectFade(int, int, int, int, unsigned int, unsigned int, bool);								// 0118  01D8
	virtual void* CMatSystemSurface::DrawSetTextureRGBAEx(int, unsigned char  const*, int, int, ImageFormat);								// 0119  01DC
	virtual void* CMatSystemSurface::DrawSetTextScale(float, float);								// 0120  01E0
	virtual void* CMatSystemSurface::SetBitmapFontGlyphSet(unsigned long, char  const*, float, float, int);								// 0121  01E4
	virtual void* CMatSystemSurface::AddBitmapFontFile(char  const*);								// 0122  01E8
	virtual void* CMatSystemSurface::SetBitmapFontName(char  const*, char  const*);								// 0123  01EC
	virtual void* CMatSystemSurface::GetBitmapFontName(char  const*);								// 0124  01F0
	virtual void* CMatSystemSurface::ClearTemporaryFontCache(void);								// 0125  01F4
	virtual void* CMatSystemSurface::GetIconImageForFullPath(char  const*);								// 0126  01F8
	virtual void* CMatSystemSurface::DrawUnicodeString(wchar_t  const*, vgui::FontDrawType_t);								// 0127  01FC
	virtual void* CMatSystemSurface::PrecacheFontCharacters(unsigned long, wchar_t  const*);								// 0128  0200
	virtual void* CMatSystemSurface::GetResolutionKey(void)const;								// 0129  0204
	virtual void* CMatSystemSurface::GetFontName(unsigned long);								// 0130  0208
	virtual void* CMatSystemSurface::GetFontFamilyName(unsigned long);								// 0131  020C
	virtual void* CMatSystemSurface::GetKernedCharWidth(unsigned long, wchar_t, wchar_t, wchar_t, float &, float &);								// 0132  0210
	virtual void* CMatSystemSurface::ForceScreenSizeOverride(bool, int, int);								// 0133  0214
	virtual void* CMatSystemSurface::ForceScreenPosOffset(bool, int, int);								// 0134  0218
	virtual void* CMatSystemSurface::OffsetAbsPos(int &, int &);								// 0135  021C
	virtual void* CMatSystemSurface::ResetFontCaches(void);								// 0136  0220
	virtual void* CMatSystemSurface::GetTextureNumFrames(int);								// 0137  0224
	virtual void* CMatSystemSurface::DrawSetTextureFrame(int, int, unsigned int *);								// 0138  0228
	virtual void* CMatSystemSurface::IsScreenSizeOverrideActive(void);								// 0139  022C
	virtual void* CMatSystemSurface::IsScreenPosOverrideActive(void);								// 0140  0230
	virtual void* CMatSystemSurface::DestroyTextureID(int);								// 0141  0234
	virtual void* CMatSystemSurface::DrawUpdateRegionTextureRGBA(int, int, int, unsigned char  const*, int, int, ImageFormat);								// 0142  0238
	virtual void* CMatSystemSurface::BHTMLWindowNeedsPaint(vgui::IHTML *);								// 0143  023C
	virtual void* CMatSystemSurface::GetWebkitHTMLUserAgentString(void);								// 0144  0240
	virtual void* CMatSystemSurface::AccessChromeHTMLController(void);								// 0145  0244
	virtual void* CMatSystemSurface::SetFullscreenViewport(int, int, int, int);								// 0146  0248
	virtual void* CMatSystemSurface::GetFullscreenViewport(int &, int &, int &, int &);								// 0147  024C
	virtual void* CMatSystemSurface::PushFullscreenViewport(void);								// 0148  0250
	virtual void* CMatSystemSurface::PopFullscreenViewport(void);								// 0149  0254
	virtual void* CMatSystemSurface::SetSoftwareCursor(bool);								// 0150  0258
	virtual void* CMatSystemSurface::PaintSoftwareCursor(void);								// 0151  025C
	virtual void* CMatSystemSurface::GMOD_ClearFontCache(void);								// 0152  0260
	virtual void* CMatSystemSurface::GMOD_GetTextSize(unsigned long, wchar_t  const*, int &, int &);								// 0153  0264
	virtual void* CMatSystemSurface::AttachToWindow(void *, bool);								// 0154  0268
	virtual void* CMatSystemSurface::EnableWindowsMessages(bool);								// 0155  026C
	virtual void* CMatSystemSurface::Begin3DPaint(int, int, int, int, bool);								// 0156  0270
	virtual void* CMatSystemSurface::End3DPaint(void);								// 0157  0274
	virtual void* CMatSystemSurface::DisableClipping(bool);								// 0158  0278
	virtual void* CMatSystemSurface::GetClippingRect(int &, int &, int &, int &, bool &);								// 0159  027C
	virtual void* CMatSystemSurface::SetClippingRect(int, int, int, int);								// 0160  0280
	virtual void* CMatSystemSurface::SetMouseCallbacks(void(*)(int &, int &), void(*)(int, int));								// 0161  0284
	virtual void* CMatSystemSurface::InstallPlaySoundFunc(void(*)(char  const*));								// 0162  0288
	virtual void* CMatSystemSurface::DrawColoredCircle(int, int, float, int, int, int, int);								// 0163  028C
	virtual void* CMatSystemSurface::DrawColoredText(unsigned long, int, int, int, int, int, int, char  const*, ...);								// 0164  0290
	virtual void* CMatSystemSurface::DrawColoredTextRect(unsigned long, int, int, int, int, int, int, int, int, char  const*, ...);								// 0165  0294
	virtual void* CMatSystemSurface::DrawTextHeight(unsigned long, int, int &, char  const*, ...);								// 0166  0298
	virtual void* CMatSystemSurface::DrawTextLen(unsigned long, char  const*, ...);								// 0167  029C
	virtual void* CMatSystemSurface::DrawPanelIn3DSpace(unsigned int, VMatrix  const&, int, int, float, float);								// 0168  02A0
	virtual void* CMatSystemSurface::DrawSetTextureMaterial(int, IMaterial*);								// 0169  02A4
	virtual void* CMatSystemSurface::HandleInputEvent(InputEvent_t  const&);								// 0170  02A8
	virtual void* CMatSystemSurface::Set3DPaintTempRenderTarget(char  const*);								// 0171  02AC
	virtual void* CMatSystemSurface::Reset3DPaintTempRenderTarget(void);								// 0172  02B0
	virtual void* CMatSystemSurface::DrawGetTextureMaterial(int);								// 0173  02B4
	/*virtual void* CMatSystemSurface::~CMatSystemSurface();								// 0174  02B8
	virtual void* CMatSystemSurface::~CMatSystemSurface();								// 0175  02BC*/
	virtual void* CMatSystemSurface::InEngine(void);								// 0176  02C0
	virtual void* CMatSystemSurface::IsInThink(unsigned int);								// 0177  02C4

};

int ScrW, ScrH;

unsigned long g_fontGUI;
IVModelInfo*							g_pModel;
ICvar*									g_pICvar;
IVEngineClient*							g_pEngine;
IBaseClientDLL*							g_pClient;
CMatSystemSurface*						g_pSurface;
CInput*									g_pInput;
IClientEntityList*						g_pEntList;
IEngineTrace*							g_pTrace;
vgui::IPanel*							g_pPanel;
CGlobalVarsBase*						g_pGlobals;
IBaseClientDLL*							g_pcClientClass;


bool DataCompare(const char* base, const char* pattern)
{
	for (; *pattern; ++base, ++pattern)
		if (*pattern != '?' && *base != *pattern)
			return 0;

	return *pattern == 0;
}
unsigned long FindPatternBase(unsigned long address, unsigned long size, const char* pattern)
{
	for (unsigned long i = 0; i < size; i++)
		if (DataCompare((const char*)(address + i), pattern))
			return address + i;

	return NULL;
}
unsigned long FindPattern(const char* dll, const char* pattern)
{
	return FindPatternBase((unsigned long)GetModuleHandleA(dll), (unsigned long)-1, pattern);
}
#define RADPI 57.295779513082f // 180 / pi

ConVar* g_pNameCvar;

namespace math
{
	inline void AngleMatrix(const Vector &angles, matrix3x4_t &matrix)
	{
		float sp, sy, sr, cp, cy, cr;

		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.y), &sy, &cy);
		SinCos(DEG2RAD(angles.z), &sr, &cr);

		matrix[0][0] = cp * cy;
		matrix[1][0] = cp * sy;
		matrix[2][0] = -sp;

		float crcy = cr * cy;
		float crsy = cr * sy;
		float srcy = sr * cy;
		float srsy = sr * sy;

		matrix[0][1] = sp * srcy - crsy;
		matrix[1][1] = sp * srsy + crcy;
		matrix[2][1] = sr * cp;

		matrix[0][2] = sp * crcy + srsy;
		matrix[1][2] = sp * crsy - srcy;
		matrix[2][2] = cr * cp;

		matrix[0][3] = 0.f;
		matrix[1][3] = 0.f;
		matrix[2][3] = 0.f;
	}
	inline void VectorRotate2(const Vector &i, const matrix3x4_t &matrix, Vector &o)
	{
		o.x = i.Dot(Vector(matrix[0][0], matrix[0][1], matrix[0][2]));
		o.y = i.Dot(Vector(matrix[1][0], matrix[1][1], matrix[1][2]));
		o.z = i.Dot(Vector(matrix[2][0], matrix[2][1], matrix[2][2]));
	}
	inline void VectorRotating(const Vector &i, const Vector &angles, Vector &o)
	{
		static matrix3x4_t matrix;

		AngleMatrix(angles, matrix);
		VectorRotate2(i, matrix, o);
	}
	float __stdcall Lerp(float flFraction, float flStart, float flEnd)
	{
		return (1 - flFraction) * flStart + flFraction * flEnd;
	}
	float __stdcall Distance2D(float x1, float y1, float x2, float y2)
	{
		return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}
	bool __stdcall WorldToScreen(Vector &vOrigin, Vector &vScreen) // &vOrigin
	{
		IVEngineClient* pEngine = g_pEngine;
		const VMatrix& worldToScreen = pEngine->WorldToScreenMatrix(); // Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix	

		float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3]; // Calculate the angle in compareson to the player's camera.
		vScreen.z = 0; // Screen doesn't have a 3rd dimension.
		if (w > 0.01) // If the object is within view.
		{
			float fl1DBw = 1 / w; // Divide 1 by the angle.
			vScreen.x = (ScrW / 2) + (0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) * ScrW + 0.5); //Get the X dimension and push it in to the Vector.
			vScreen.y = (ScrH / 2) - (0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) * ScrH + 0.5); //Get the Y dimension and push it in to the Vector.
			return true;
		}
		return false;
	}
	float __stdcall NormalizeAngle(float angle)
	{
		while (angle > 180.f)
		{
			angle -= 360.f;
		}

		while (angle < -180.f)
		{
			angle += 360.f;
		}

		return angle;
	}
	float __stdcall Clamp(float x, float a, float b)
	{
		/*int iReturn = 0;
		iReturn = x;

		if (iReturn < a)
		iReturn = a;
		if (iReturn > b)
		iReturn = b;

		return iReturn;// x < a ? a : (x > b ? b : x);*/
		return x < a ? a : (x > b ? b : x);
	}
	void _stdcall NormalizeVector(Vector &vIn, Vector &vOut)
	{
		float flLen = vIn.Length();

		if (flLen == 0)
		{
			vOut.Init(0, 0, 1);
			return;
		}

		flLen = 1 / flLen;

		vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
	} // Credits: VecHook
	float __stdcall RSqrtFast(float x)
	{
		return 1.f / sqrtf(x);
	}
	void __stdcall CalcAngle(Vector &src, Vector &dst, QAngle &out)
	{
		double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
		out[0] = (atan2f(delta[2], hyp) * RADPI);
		out[1] = (atanf(delta[1] / delta[0]) * RADPI);
		out[2] = 0.0f;
		if (delta[0] >= 0.0) { out[1] += 180.0f; }
	} // Credits: dude719
	void __stdcall NormalizeAngles(QAngle &angle)
	{
		for (int axis = 0; axis < 3; ++axis)
		{
			while (angle[axis] > 180.f)
			{
				angle[axis] -= 360.f;
			}

			while (angle[axis] < -180.f)
			{
				angle[axis] += 360.f;
			}
		}
	} // Credits: dude719
	const float RAD_TO_DEG_f = 57.295779513082320876798154814105f;
	const float M_RADPI = 57.295779513082f;
	float GetFov(QAngle angle, Vector src, Vector dst)
	{
		QAngle ang, aim;
		float fov;
		double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
		ang[0] = (float)(atan(delta[2] / hyp) * M_RADPI);
		ang[1] = (float)(atan(delta[1] / delta[0]) * M_RADPI);
		ang[2] = 0.0f;
		if (delta[0] >= 0.0) { ang[1] += 180.0f; }
		float pitch, yaw, tmp;
		pitch = (float)(angle[0] * M_PI / 180);
		yaw = (float)(angle[1] * M_PI / 180);
		tmp = (float)cos(pitch);
		aim[0] = (float)(-tmp * -cos(yaw));
		aim[1] = (float)(sin(yaw)*tmp);
		aim[2] = (float)-sin(pitch);
		pitch = (float)(ang[0] * M_PI / 180);
		yaw = (float)(ang[1] * M_PI / 180);
		tmp = (float)cos(pitch);
		ang[0] = (float)(-tmp * -cos(yaw));
		ang[1] = (float)(sin(yaw)*tmp);
		ang[2] = (float)-sin(pitch);
		float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		float mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];
		fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI);
		return fov;
	}
};