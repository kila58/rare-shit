#pragma once

#define GAME_DLL
#define CLIENT_DLL
// Some libraries
#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <d3dx9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma warning( disable : 4819 )
#pragma warning( disable : 4244 ) // Possible loss of data
#pragma warning( disable : 4091 ) // typedef warning
#pragma warning( disable : 4805 )

// Libraries
#pragma comment(lib, "tier0.lib")
#pragma comment(lib, "tier1.lib")
#pragma comment(lib, "tier2.lib")
#pragma comment(lib, "tier3.lib")
#pragma comment(lib, "mathlib.lib")
#pragma comment(lib, "vstdlib.lib")

#include "public\\tier0\\wchartypes.h"
#include "public/cdll_int.h"
#include "public/iprediction.h"
#include "public/bone_setup.h"
#include "public/icliententitylist.h"
#include "public/ienginevgui.h"
#include "public/IGameUIFuncs.h"
#include "public/dlight.h"
#include "public/r_efx.h" 
#include "public/igameevents.h"
#include "public/view_shared.h"
#include "public/inetchannelinfo.h"
#include "public/iachievementmgr.h"
#include "public/steam/steam_api.h"
#include "public/steam/isteamuserstats.h"
#include "game/client/imessagechars.h"
#include "game/client/iclientmode.h"
#include "game/client/cliententitylist.h"
#include "game/client/cdll_client_int.h"
#include "game/client/cbase.h"
#include "game/client/c_baseanimating.h"
#include "game/client/c_basecombatweapon.h"
#include "game/client/c_baseplayer.h"
#include "game/client/enginesprite.h"
#include "game/client/input.h"
#include "game/client/c_playerresource.h"
#include "game/client/iviewrender.h"
#include "game/client/viewrender.h"
#include "game/client/game_controls/commandmenu.h"
#include "game/client/hudelement.h"
#include "public/engine/ivmodelrender.h"
#include "public/engine/ivdebugoverlay.h"
#include "public/engine/ivmodelinfo.h"
#include "public/engine/IEngineTrace.h"
#include "public/engine/IEngineSound.h"
#include "public/materialsystem/imaterialsystemstub.h"
#include "public/materialsystem/itexture.h"
#include "public/materialsystem/IMaterialVar.h"
#include "public/tier1/checksum_md5.h"
#include "public/matsys_controls/matsyscontrols.h"
#include "public/vgui/IClientPanel.h"
#include "public/vgui/IPanel.h"
#include "public/vgui/ISurface.h"
#include "public/vgui/ILocalize.h"
#include "public/collisionutils.h"
#include "public/vstdlib/random.h"
#include "public/vgui_controls/Panel.h"
#include "public/VGuiMatSurface/IMatSystemSurface.h"
#include "public/mathlib/vector.h"
#include "game/shared/usermessages.h"
#include "game/shared/basecombatweapon_shared.h"
#include "game/shared/takedamageinfo.h"
#include "game/shared/igamemovement.h"
#include "in_buttons.h"
#include "icvar.h"
//thanks kirby
template< typename Function > Function getvfunc(PVOID Base, DWORD Index)
{

	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];
	return (Function)(dwAddress);
}
class CInputNew
{
public:
	CUserCmd* GetUserCmd(int sequence_number)
	{
		typedef CUserCmd*(__thiscall* OriginalFn)(void*, int, int);
		return getvfunc<OriginalFn>(this, 8)(this, -1, sequence_number);
	}

	char     __pad0[0xAC];

	CUserCmd*    m_pCommand;
	CInput::CVerifiedUserCmd*   m_pVerified;
};
enum CSGO_Weapon_ID
{
	weapon_none,
	weapon_deagle,
	weapon_elite,
	weapon_fiveseven,
	weapon_glock,
	weapon_p228,
	weapon_usp,
	weapon_ak47,
	weapon_aug,
	weapon_awp,
	weapon_famas,
	weapon_g3sg1,
	weapon_galil,
	weapon_galilar,
	weapon_m249,
	weapon_m3,
	weapon_m4a1,
	weapon_mac10,
	weapon_mp5navy,
	weapon_p90,
	weapon_scout,
	weapon_sg550,
	weapon_sg552,
	weapon_tmp,
	weapon_ump45,
	weapon_xm1014,
	weapon_bizon,
	weapon_mag7,
	weapon_negev,
	weapon_sawedoff,
	weapon_tec9,
	weapon_taser,
	weapon_hkp2000,
	weapon_mp7,
	weapon_mp9,
	weapon_nova,
	weapon_p250,
	weapon_scar17,
	weapon_scar20,
	weapon_sg556,
	weapon_ssg08,
	weapon_knifegg,
	weapon_knife,
	weapon_flashbang,
	weapon_hegrenade,
	weapon_smokegrenade,
	weapon_molotov,
	weapon_decoy,
	weapon_incgrenade,
	weapon_c4
};

class IVModelInfo2
{
public:
	//CModelInfo::GetModelRenderBounds(model_t const*,Vector &,Vector &)
	void GetModelMaterials(const model_t *model, int count, IMaterial** ppMaterial)
	{
		typedef void(__thiscall* origfn)(void*, const model_t*, int, IMaterial**);
		return getvfunc<origfn>(this, 15)(this, model, count, ppMaterial);
	}
	void GetModelRenderBounds(model_t const* a, Vector &b, Vector &c)
	{
		typedef void(__thiscall* OriginalFn)(void*, model_t const*, Vector&, Vector&);
		return getvfunc<OriginalFn>(this, 5)(this, a, b, c);
	}
	const char* GetModelName(DWORD* model)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, DWORD*);
		return getvfunc<OriginalFn>(this, 57)(this, model);
	}
	studiohdr_t	*GetStudiomodel(const model_t *mod)
	{
		typedef studiohdr_t*(__thiscall* OriginalFn)(PVOID, const model_t*);
		return getvfunc<OriginalFn>(this, 31)(this, mod);
	}

};
class ISurfaceNew
{
public:
	// 13	CMatSystemSurface::DrawSetColor(int,int,int,int)
	// 14	CMatSystemSurface::DrawSetColor(Color)
	// 15	CMatSystemSurface::DrawFilledRect(int,int,int,int)
	void DrawPolyLine(int *px, int *py, int numPoints){
		typedef void(__thiscall* origfn)(void*, int*, int*, int);
		//19
		getvfunc<origfn>(this, 19)(this, px, py, numPoints);
	}
	void DrawOutlinedCircle(int x, int y, int radius, int segments)
	{
		typedef void(__thiscall* origfn)(void*, int, int, int, int);
		getvfunc<origfn>(this, 102)(this, x, y, radius, segments);
	}
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 18)(this, x0, y0, x1, y1);
	}
	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 13)(this, r, g, b, a);
	}
	void DrawSetColor(Color colorcode)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Color);
		getvfunc<OriginalFn>(this, 13)(this, colorcode);
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 15)(this, x0, y0, x1, y1);
	}
	// 17	CMatSystemSurface::DrawOutlinedRect(int,int,int,int)
	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 17)(this, x0, y0, x1, y1);
	}
	// 22	CMatSystemSurface::DrawSetTextFont(unsigned long)
	// 23	CMatSystemSurface::DrawSetTextColor(int,int,int,int)
	// 23	CMatSystemSurface::DrawSetTextColor(Color)
	void DrawSetTextFont(unsigned long font)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, unsigned long);
		getvfunc<OriginalFn>(this, 22)(this, font);
	}
	void DrawSetTextColor(Color colorcode)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Color);
		getvfunc<OriginalFn>(this, 23)(this, colorcode);
	}
	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc<OriginalFn>(this, 23)(this, r, g, b, a);
	}
	// 25	CMatSystemSurface::DrawSetTextPos(int,int)
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int);
		getvfunc<OriginalFn>(this, 25)(this, x, y);
	}
	// 27	CMatSystemSurface::DrawPrintText(wchar_t  const*,int,FontDrawType_t)
	void DrawPrintText(const wchar_t *text, int textLen)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const wchar_t *, int, int);
		return getvfunc<OriginalFn>(this, 27)(this, text, textLen, 0);
	}
	// 70	CMatSystemSurface::CreateFont(void)
	// 71	CMatSystemSurface::SetFontGlyphSet(unsigned long,char  const*,int,int,int,int,int,int,int)
	unsigned long CreateFont()
	{
		typedef unsigned long(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 70)(this);
	}

	bool SetFontGlyphSet(unsigned long &font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
		return getvfunc<OriginalFn>(this, 71)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
};
class EngineClientNew
{
public:
	// 5	CEngineClient::GetScreenSize(int &,int &)
	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int&, int&);
		return getvfunc<OriginalFn>(this, 5)(this, width, height);
	}
	// 8	CEngineClient::GetPlayerInfo(int,player_info_s *)
	bool GetPlayerInfo(int ent_num, player_info_t *pinfo)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, int, player_info_t *);
		return getvfunc<OriginalFn>(this, 8)(this, ent_num, pinfo);
	}
	//	78	CEngineClient::GetNetChannelInfo
	INetChannelInfo	*GetNetChannelInfo()
	{
		typedef INetChannelInfo*(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 78)(this);
	}
	// 11	CEngineClient::Con_IsVisible(void)
	bool Con_IsVisible(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 11)(this);
	}
	// 12	CEngineClient::GetLocalPlayer(void)
	int GetLocalPlayer(void)
	{
		typedef int(__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 12)(this);
	}
	// 14	CEngineClient::Time(void)
	float Time(void)
	{
		typedef float(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 14)(this);
	}
	int GetMaxClients()
	{
		typedef float(__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 20)(this);
	}
	// 26	CEngineClient::IsInGame(void)
	// 27	CEngineClient::IsConnected(void)
	// 28	CEngineClient::IsDrawingLoadingImage(void)
	bool IsInGame(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 26)(this);
	}
	bool IsConnected(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 27)(this);
	}
	bool IsDrawingLoadingImage(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 28)(this);
	}
	// 37	CEngineClient::WorldToScreenMatrix(void)
	const matrix3x4_t& WorldToScreenMatrix(void)
	{
		typedef const matrix3x4_t& (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 37)(this);
	}
	// 89	CEngineClient::IsTakingScreenshot(void)
	bool IsTakingScreenshot(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 92)(this);
	}
	// Not recommended to use this
	// 110	CEngineClient::ClientCmd_Unrestricted(char  const*)
	void ClientCmd_Unrestricted(const char* chCommandString)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char *);
		return getvfunc<OriginalFn>(this, 113)(this, chCommandString);
	}
	// Safe, but was hugely restricted
	// 105	CEngineClient::ExecuteClientCmd(char  const*)
	void ExecuteClientCmd(const char* chCommandString)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char *);
		return getvfunc<OriginalFn>(this, 108)(this, chCommandString);
	}
	void GetViewAngles(Vector& va)
	{
		typedef void(__thiscall* OriginalFn)(void*, Vector&);
		return getvfunc<OriginalFn>(this, 18)(this, va);
	}
	//	19	CEngineClient::SetViewAngles
	void SetViewAngles(Vector& va)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Vector&);
		return getvfunc<OriginalFn>(this, 19)(this, va);
	}
};
#define WEP_GETSPREAD_VTBLE (1912 / 4) //4th xref from fx_firebullets call.
class CBaseCombatWeaponNew
{
public:

	float GetInaccuracy()
	{
		typedef float(__thiscall* oGetSpread)(PVOID);
		return getvfunc< oGetSpread>(this, WEP_GETSPREAD_VTBLE)(this);
	}

	float GetSpread()
	{
		typedef float(__thiscall* oGetInac)(PVOID);
		return getvfunc< oGetInac>(this, WEP_GETSPREAD_VTBLE + 1)(this);
	}

	void UpdateAccuracyPenalty()
	{
		typedef void(__thiscall* oUpdateAccuracyPenalty)(PVOID);
		return getvfunc< oUpdateAccuracyPenalty>(this, WEP_GETSPREAD_VTBLE + 2)(this);
	}
};
class CGlobalVarsBaseNew
{
public:
	float realtime;
	int framecount;
	float absoluteframetime;
	float unknown;
	float curtime;
	float frametime;
	int maxclients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
};
class CBaseEntityNew
{
public:
	void PhysicsSimulate()
	{
		typedef void(__thiscall* fn)(void*);
		getvfunc<fn>(this, 200)(this);
	}
	int GetRank();
	int GetWins();
	int m_ArmorValue();
	bool m_bHasHelmet();
	Vector& OBBMins();
	Vector& OBBMaxs();
	void SetFlash(bool on)
	{
		if (on)
		{
			*reinterpret_cast<float*>((DWORD)this + 0x1DA4) = 0.f;
			*reinterpret_cast<float*>((DWORD)this + 0x1DA8) = 0.f;
		}
		else
		{
			*reinterpret_cast<float*>((DWORD)this + 0x1DA4) = 255.f;
			*reinterpret_cast<float*>((DWORD)this + 0x1DA8) = 1.f;
		}
	}
	CBaseCombatWeapon *GetWeapon();
	int entindex()
	{
		typedef int(__thiscall* origfn)(void*);
		return getvfunc<origfn>(this, 83)(this);
	}
	float GetMaxSpeed()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x160c);
	}
	float TickBase()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x17cc);
	}
	bool HasDefuser()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0x23b0);
	}
	int GetHP()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xFC);
	}
	int GetFlags()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x100);
	}
	int CrosshairID()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x2400);
	}
	float* flashmaxalphta()
	{
		return *reinterpret_cast<float**>((DWORD)this + 0x1DA4);
	}
	Vector GetEyePosition()
	{
		Vector vecViewOffset = *reinterpret_cast<Vector*>((DWORD)this + 0x104);
		return GetAbsOrigin() + vecViewOffset;
	}
	Vector& GetAbsOrigin()
	{
		typedef Vector& (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 10)(this);
	}
	Vector& GetAbsAngles()
	{
		typedef Vector& (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 11)(this);
	}
	ClientClass* GetClientClass()
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
	}
	bool IsDefusing()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x1c08);
	}
	bool IsDormant()
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 9)(pNetworkable);
	}
	bool isAlive()
	{
		BYTE lifestate = *(BYTE*)((DWORD)this + 0x25B);
		return (lifestate == LIFE_ALIVE);
	}
	int GetIndex()
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 10)(pNetworkable);
	}
	bool SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		PVOID pRenderable = (PVOID)(this + 0x4);
		typedef bool(__thiscall* OriginalFn)(PVOID, matrix3x4_t*, int, int, float);
		return getvfunc<OriginalFn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
	const model_t* GetModel()
	{
		void* pRenderable = (void*)(this + 0x4);
		typedef model_t* (__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 60)(this);
	}
	int GetSpotted()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x935);
	}
	Vector GetVelocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x110);
	}
	Vector GetPunch()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x13E8);
	}
	int GetTeamNum()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xF0);
	}

};
