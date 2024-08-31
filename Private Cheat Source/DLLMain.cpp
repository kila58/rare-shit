#include "SDK.h"
#include "VMT Hook.h"
#include "Client.h"
#include "Panels.h"
#include "CGlobalVars.h"
#include "Control Variables.h"
#include "CBaseAPI.h"
#include "Player ESP.h"
#include "detours.h"
#include	<d3dx9.h>
#include	<d3d9.h>
#include	<D3dx9tex.h>
#include	<D3dx9shape.h>
#include "CDrawManager.h"
#include "Menu.h"
#include "File Manager.h"
#include "D3DModels.h"
#include	<fstream>
#include	<iostream>
#include	<algorithm>
#include	<istream>
#include	<string.h>

#include "CTriggerbot.h"
#include "pAim.h"
#include "Player Manager.h"

#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#include "Math.h"


#pragma warning(disable: 4530)


// libc
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS


#pragma comment	( lib, "d3d9.lib" )
#pragma comment	( lib, "d3dx9.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "Shlwapi.lib" )
#pragma comment ( lib, "winmm.lib" )




CreateInterface_t g_pEngineFactory = NULL;
CreateInterface_t g_ClientFactory = NULL;
CreateInterface_t g_VGUIFactory = NULL;
CreateInterface_t g_VGUI2Factory = NULL;


CreateInterfaceFn				g_SteamClientFactory = NULL;

extern CreateMoveFn OriginalCreateMove;
extern IN_KeyEventFn OriginalKeyEvent;



bool IsAlive2(CBaseEntity* pEntity)
{
	char szLifeState = *(char*)((DWORD)pEntity + 0x25B);
	return (szLifeState == 0);
}


void InCross_Triggerbot(CUserCmd* Cmd)
{
	CBaseEntity* pLocalEntity = ALX.pEntList->GetClientEntity(ALX.pEngine->GetLocalPlayer());
	if (!pLocalEntity)
		return;

	player_info_t pi;
	static int iLocked = -1;

	int CrosshairEntID = pLocalEntity->GetCrosshairID();


	for (INT i = 0; i <= ALX.pEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* pEntity = ALX.pEntList->GetClientEntity(i);

		CBaseEntity* pTrigger = ALX.pEntList->GetClientEntity(CrosshairEntID);

		if (pEntity == NULL)
			continue;

		if (pEntity->IsDormant())
			continue;

		if (!IsAlive2(pEntity))
			continue;



		if (pEntity->GetIndex() == pLocalEntity->GetIndex())
			continue;

		if (pEntity == pLocalEntity)
			continue;

		if (pTrigger->GetIndex() == pLocalEntity->GetIndex())
			return;

		if (pTrigger->GetTeamNum() == pLocalEntity->GetTeamNum())
			return;



		if (CrosshairEntID > 0 && CrosshairEntID < ALX.pEntList->GetHighestEntityIndex())
			Cmd->buttons |= IN_ATTACK;


	}
}

typedef HRESULT(__stdcall* DrawIndexedPrimitive_t)(LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
DrawIndexedPrimitive_t m_oDrawIndexPrimitive;

bool bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
	if (*szMask == 'x' && *pData != *bMask)   return 0;
	return (*szMask) == NULL;
}
DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
{
	for (DWORD i = 0; i<dwLen; i++)
	if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))  return (DWORD)(dwAddress + i);
	return 0;
}

LPDIRECT3DTEXTURE9 Red, Yellow, Green, Blue, Purple, Pink, Orange, White, Black, RGBA, RGBA2;

LPDIRECT3DPIXELSHADER9 Red2, Yellow2, Green2, Blue2, Purple2, Pink2, Orange2, White2, Black2,BlueGlass;



HRESULT CreateShader(IDirect3DPixelShader9 **pShader, IDirect3DDevice9 *Device, float red, float green, float blue, float alpha)
{
	const char *format = "ps.1.1\n\
						 					   def c0, %f, %f, %f, %f\n\
											   					   mov r0,c0";
	char buffer[100];
	sprintf(buffer, format, red, green, blue, alpha);
	LPD3DXBUFFER pCode = NULL;
	LPD3DXBUFFER pErrorMsgs = NULL;

	D3DXAssembleShader(buffer, strlen(buffer), NULL, NULL, NULL, &pCode, &pErrorMsgs);
	return Device->CreatePixelShader((DWORD *)pCode->GetBufferPointer(), pShader);
}

HRESULT GenerateTexture(IDirect3DDevice9* pDevice, IDirect3DTexture9 **ppD3Dtex, DWORD dwColor)
{
	HRESULT hr = pDevice->CreateTexture(8, 8, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, ppD3Dtex, NULL);
	if (FAILED(hr))
		return hr;

	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);

	BYTE* pDstRow = (BYTE*)d3dlr.pBits;
	DWORD* pDst32;

	for (int y = 0; y < 8; y++) {
		pDst32 = (DWORD*)pDstRow;

		for (int x = 0; x < 8; x++)
			*pDst32++ = dwColor;

		pDstRow += d3dlr.Pitch;
	}

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}

HRESULT __stdcall hkDrawIndexPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT PrimitiveCount)
{
	LPDIRECT3DVERTEXBUFFER9 Stream_Data;
	UINT Offset, Stride;

	if (pDevice->GetStreamSource(0, &Stream_Data, &Offset, &Stride) == D3D_OK)
		Stream_Data->Release();


	//texture init
	static bool done = false;
	if (!done)
	{
		GenerateTexture(pDevice, &Red, D3DCOLOR_ARGB(255, 220, 20, 60));
		GenerateTexture(pDevice, &Yellow, D3DCOLOR_ARGB(255, 255, 255, 0));
		GenerateTexture(pDevice, &Green, D3DCOLOR_ARGB(255, 154, 205, 50));

		GenerateTexture(pDevice, &Blue, D3DCOLOR_ARGB(255, 70, 130, 180));
		GenerateTexture(pDevice, &Purple, D3DCOLOR_ARGB(255, 102, 0, 153));
		GenerateTexture(pDevice, &Pink, D3DCOLOR_ARGB(255, 255, 20, 147));
		GenerateTexture(pDevice, &Orange, D3DCOLOR_ARGB(255, 255, 165, 0));
		GenerateTexture(pDevice, &Black, D3DCOLOR_ARGB(255, 0, 0, 0));
		GenerateTexture(pDevice, &White, D3DCOLOR_ARGB(255, 255, 255, 255));


		CreateShader(&Red2, pDevice, 1.0f, 0.0f, 0.0f, 1.0f);
		CreateShader(&Yellow2, pDevice, 1.0f, 1.0f, 0.0f, 1.0f);
		CreateShader(&Green2, pDevice, 0.0f, 1.0f, 0.0f, 1.0f);

		CreateShader(&Blue2, pDevice, 0.0f, 0.0f, 1.0f, 1.0f);

		CreateShader(&White2, pDevice, 1.0f, 1.0f, 1.0f, 1.0f);
		CreateShader(&BlueGlass, pDevice, 0.0f, 0.0f, 1.0f, 0.5f);
		
		done = true;
	}

	if (ALX.pCvar->hands)
	{

		if (nohands2)
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
			//pDevice->SetTexture(0, Orange);
			pDevice->SetPixelShader(Orange2);//apply new shader
			m_oDrawIndexPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			//pDevice->SetTexture(0, Blue);
			pDevice->SetPixelShader(Blue2);//apply new shader
		}
	}

	if (ALX.pCvar->nohands)
	{
		if (nohands2)
		{
			return D3D_OK;
		}
	}


	/*if (nohands2)
	{	
	   pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	
	}*/


	if (ALX.pCvar->chams)
	{

		if (t_dx)
		{


			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
			pDevice->SetTexture(0, Yellow);
			//pDevice->SetPixelShader(Red2);//apply new shader
			m_oDrawIndexPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetTexture(0, Red);
			//pDevice->SetPixelShader(Yellow2);//apply new shader


		}

		if (ct_dx)
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
			pDevice->SetTexture(0, Green);
			//pDevice->SetPixelShader(Blue2);//apply new shader
			m_oDrawIndexPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetTexture(0, Blue);
			//pDevice->SetPixelShader(Orange2);//apply new shader
		}
	}

	if (ALX.pCvar->shaderchams)
	{
		if (t_dx)
		{


			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

			//pDevice->SetTexture(0, Red);
			pDevice->SetPixelShader(Red2);//apply new shader
			m_oDrawIndexPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			//pDevice->SetTexture(0, Yellow);
			pDevice->SetPixelShader(Yellow2);//apply new shader


		}

		if (ct_dx)
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

			//pDevice->SetTexture(0, Blue);
			pDevice->SetPixelShader(Blue2);//apply new shader
			m_oDrawIndexPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);

			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	
			pDevice->SetPixelShader(Green2);//apply new shader

		}
	}



	return m_oDrawIndexPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
}

void InitD3D()
{
	while (GetModuleHandleA("d3d9.dll") == NULL)
		Sleep(100);

	DWORD dwD3D9, adr, *vTable;
	dwD3D9 = (DWORD)GetModuleHandleA("d3d9.dll");

	adr = FindPattern(dwD3D9, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	if (adr)
	{
		memcpy(&vTable, (void *)(adr + 2), 4);
     	m_oDrawIndexPrimitive = (DrawIndexedPrimitive_t)DetourFunction((PBYTE)vTable[82], (PBYTE)hkDrawIndexPrimitive);
		
	}
}



Vector GetEyePosition2(CBaseEntity* pEntity)
{
	Vector vecViewOffset = *reinterpret_cast< Vector* >(reinterpret_cast< int >(pEntity)+0x104);

	return pEntity->GetAbsOrigin() + vecViewOffset;
}



float flLastThinkTime = 0.0f;
float flSpamTimer = 0.0f;
float flSpamDelay = 1.0f;

void SpamThink()
{
	float curtime = ALX.pEngine->Time();

	flSpamTimer += curtime - flLastThinkTime;
	flLastThinkTime = curtime;

	if (flSpamTimer > flSpamDelay)
	{
		ALX.pEngine->ExecuteClientCmd("TITANIUM");

		while (flSpamTimer > flSpamDelay)
			flSpamTimer -= flSpamDelay;
	}

}



CVMTHookManager* pPredictionHook;

bool __stdcall hkInPrediction()
{
	pPredictionHook->UnHook();
	bool bResult = ALX.pPrediction->InPrediction();
	pPredictionHook->ReHook();

	static DWORD dwCalcPlayerView = NULL;


	if (!dwCalcPlayerView)

		dwCalcPlayerView = FindPattern((DWORD)GetModuleHandle("client.dll"), 0x7FFFFFFF, (PBYTE)"\x84\xC0\x75\x08\x57\x8B\xCE\xE8\x00\x00\x00\x00\x8B\x06", "xxxxxxxx????xx");

	if ((DWORD)(_ReturnAddress()) == dwCalcPlayerView)
	{


		CBaseEntity* pLocal = NULL;

        PFLOAT VAngles = NULL;
	
		__asm
		{
			MOV pLocal, ESI
				MOV VAngles, EDI

		}

		if (pLocal == NULL || VAngles == NULL)
			return bResult;


		Vector vecPunch = pLocal->PunchVisualAngle(pLocal) + (pLocal->PunchAngle(pLocal) * 2 * 0.45);

		if (ALX.pCvar->novisualrecoil)
		{
		        VAngles[3] -= vecPunch[0];
				VAngles[4] -= vecPunch[1];
				VAngles[5] -= vecPunch[2];	

		}
			bResult = true;
		

	}

	return bResult;
}



typedef void(__stdcall *CreateMove_)(int, float, bool);
CreateMove_ oMove;

typedef void(__stdcall *InPrediction_)(void);
InPrediction_ oPredict;

int ticksOfLag = 0;
int numToTrack = 0;
bool Lag = true;

ArgonLXFramework::ArgonLX ALX;
namespace ArgonLXFramework
{
	ArgonLX::ArgonLX()
	{
		ALX.PAim = new PRotator();
		ALX.PSpreadz = new Spreadz();
		ALX.PTrigger = new CTrigger();
		ALX.pPlayerVariables = new CPlayerVariables();
		ALX.pDrawManager = new CDrawManager();
		ALX.pCvar = new CControlVariables();
		ALX.pClientHook = new ClientHook();
		ALX.pFileManager = new CFileManager();
		ALX.pBaseAPI = new CBaseAPI();
		ALX.pMenu = new CMenu();
		ALX.pEnable = new CEnable();
		ALX.pOptions = new COptions();
		ALX.pPlayerESP = new CPlayerESP();
	}
}


bool HasAmmo(CBaseEntity *pEnt)
{
	C_BaseCombatWeapon* m_pWeapon = ALX.PSpreadz->GetBaseCombatActiveWeapon(pEnt);

	if (m_pWeapon != NULL)
	{
		int m_iClip11 = *(int*)((DWORD)m_pWeapon + (DWORD)0x15C0);

		if (m_iClip11 == 0)
		{
			return false;
		}
	}

	return true;
}

CVMTHookManager* pCreateMoveHook;

bool isValidWeapon(int weaponid)
{
	static int tocheck[19] = { 42, 43, 44, 45, 46, 47, 48, 49, 59,  61, 62, 63, 500, 505, 506, 507, 508, 509, 515 };
	
	for (int i = 0; i < 19; i++)
	{
		if (weaponid == tocheck[i])
			return false;
	}

	return true;
}

bool isValidWeaponRCS(int weaponid)
{
	static int tocheck[27] = { 1,2,3,4,30,31,32,36,42, 43, 44, 45, 46, 47, 48, 49, 59, 61, 62, 63, 500, 505, 506, 507, 508, 509, 515 };

	for (int i = 0; i < 27; i++)
	{
		if (weaponid == tocheck[i])
			return false;
	}

	return true;
}

bool IsScoped(int weaponid,CUserCmd* pCmd)
{
	static int tocheck[4] = { 9, 11, 38, 40 };

	for (int i = 0; i < 4; i++)
	{
		if (weaponid == tocheck[i])
		{
			if (pCmd->buttons & IN_ZOOM)
			{
				return true;
			}

			return false;
		}
	}

	return true;
}

#include "DLLMain.h"

static int iAntiAimStart = 0;
static int iAintiAim = 1;
static bool bFlip = true;
static int iFlip = 0;


void KnifebotStart(CUserCmd* pCmd)
{
	for (int iIndex = 0; iIndex < ALX.pEntList->GetHighestEntityIndex(); iIndex++)
	{
		CSetupPlayer __pLocalBaseEntity = gPlayers[me];

		CBaseEntity* pLocalBaseEntity = __pLocalBaseEntity.BaseEnt();

		if (iIndex == pLocalBaseEntity->GetIndex())
			return;
		
		CSetupPlayer __pBaseEntity = gPlayers[iIndex];

		CBaseEntity* pBaseEntity = __pBaseEntity.BaseEnt();

		if (pBaseEntity == NULL)
			return;

		if (ALX.PSpreadz->KnifeBot(pBaseEntity, pLocalBaseEntity))
		{
			pCmd->buttons |= IN_ATTACK2;
		}

	}
}

void AntiAimFunc(CUserCmd* pCmd, CBaseEntity* pLocal, C_BaseCombatWeapon *pWeapon)
{
	Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	Vector qMove, qRealView(pCmd->viewangles);
	ALX.PSpreadz->VectorAngles(&vMove, &qMove);

	
	if (isValidWeapon(pWeapon->getweaponid()))
	{
	
		
			if (ALX.PAim->m_MoveType(pLocal) == MOVETYPE_LADDER)
			{

				flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);
				pCmd->forwardmove = cos(flYaw) * flSpeed;
				pCmd->sidemove = sin(flYaw) * flSpeed;
			}
			else
			{
				if (bFlip)
				{


					pCmd->viewangles.x = 89;
					pCmd->viewangles.y = 180;
					pCmd->viewangles.x = 123;
					pCmd->viewangles.y = 180;
					pCmd->viewangles.x = 129;
					pCmd->viewangles.y = 180;
					pCmd->viewangles.x = 92;
					pCmd->viewangles.y = 180;

					ALX.pPlayerESP->NormalizeAngle(pCmd->viewangles);
					ALX.pPlayerESP->ClampAngles(pCmd->viewangles);

					flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);
					pCmd->forwardmove = cos(flYaw) * flSpeed;
					pCmd->sidemove = sin(flYaw) * flSpeed;

					bFlip = false;
				}
				else
				{
				
					pCmd->viewangles.x = 89;
					pCmd->viewangles.y = 20;
					pCmd->viewangles.x = 123;
					pCmd->viewangles.y = 20;
					pCmd->viewangles.x = 129;
					pCmd->viewangles.y = 20;
					pCmd->viewangles.x = 92;
					pCmd->viewangles.y = 20;

					ALX.pPlayerESP->NormalizeAngle(pCmd->viewangles);
					ALX.pPlayerESP->ClampAngles(pCmd->viewangles);

					flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);
					pCmd->forwardmove = cos(flYaw) * flSpeed;
					pCmd->sidemove = sin(flYaw) * flSpeed;

					bFlip = true;
				}
			}
		}

}

void __stdcall HookedCreateMove(int seqnr, float time, bool active, bool& bSendPacket)
{
	pCreateMoveHook->UnHook();
	oMove(seqnr, time, active);
	pCreateMoveHook->ReHook();

	CInput::CVerifiedUserCmd* pVerfiedCmd = *(CInput::CVerifiedUserCmd**)((DWORD)ALX.pInput + 0xF0);
	if (!pVerfiedCmd)
		return;

	CInput::CVerifiedUserCmd* pVerfied = &pVerfiedCmd[seqnr % 150];
	CUserCmd* pCmd = ALX.pInput->GetUserCmd(0, seqnr);

	if (!pCmd || !pVerfied)
		return;

	Vector view = pCmd->viewangles;
	float oldSidemove = pCmd->sidemove;
	float oldForwardmove = pCmd->forwardmove;



	CBaseEntity* pLocalEntity = ALX.pEntList->GetClientEntity(ALX.pEngine->GetLocalPlayer());
	if (!pLocalEntity)
		return;


	if (ticksOfLag < ALX.pCvar->fakelag)
	{
		bSendPacket = false;
		ticksOfLag++;
	}
	else
	{
		ticksOfLag = 0;
	}


	if (pLocalEntity->GetHealth() > 0)
	{


		C_BaseCombatWeapon *pWeapon = ALX.PSpreadz->GetBaseCombatActiveWeapon(pLocalEntity);

		if (ALX.pCvar->autopistol)
		{

			if (pCmd->buttons & IN_ATTACK)
			{
				static bool bAttack = false;
				if (bAttack)    pCmd->buttons |= IN_ATTACK;
				else
					pCmd->buttons &= ~IN_ATTACK;
				bAttack = !bAttack;
			}
		}


		if (ALX.pCvar->autostrafe_vis)
		{
			bool bKeysPressed = true;
			if (GetAsyncKeyState(0x41) || GetAsyncKeyState(0x57) || GetAsyncKeyState(0x53) || GetAsyncKeyState(0x44)) bKeysPressed = false;

			static bool bDirection = false;

			if ((GetAsyncKeyState(VK_SPACE) && (pLocalEntity->GetFlags() & FL_ONGROUND)) && bKeysPressed)
			{
				if (pLocalEntity->GetVelocity().Length() <= 50)
				{
					pCmd->forwardmove = 450.f;
				}
			}

			if (!(pLocalEntity->GetFlags() & FL_ONGROUND) && pCmd->buttons & IN_JUMP)
			{
				if (pLocalEntity->GetVelocity().Length() <= 50)
				{
					pCmd->forwardmove = 450.f;
				}
				pCmd->buttons &= ~IN_JUMP;
			}

			float flYawBhop = 0.f;
			if (pLocalEntity->GetVelocity().Length() > 50.f)
			{
				float x = 30.f, y = pLocalEntity->GetVelocity().Length(), z = 0.f, a = 0.f;

				z = x / y;
				z = fabsf(z);

				a = x * z;

				flYawBhop = a;
			}

			if ((GetAsyncKeyState(VK_SPACE) && !(pLocalEntity->GetFlags() & FL_ONGROUND)) && bKeysPressed)
			{
				if (pCmd->mousedx < 0)
				{
					pCmd->sidemove = -450.f;
				}

				if (pCmd->mousedx > 0)
				{
					pCmd->sidemove = 450.f;
				}

				if (bDirection)
				{

					pCmd->viewangles.y -= flYawBhop;

					ALX.pPlayerESP->NormalizeAngle(pCmd->viewangles);
					ALX.pPlayerESP->ClampAngles(pCmd->viewangles);
					pCmd->sidemove = -450.f;
					bDirection = false;
				}
				else
				{

					pCmd->viewangles.y += flYawBhop;


					ALX.pPlayerESP->NormalizeAngle(pCmd->viewangles);
					ALX.pPlayerESP->ClampAngles(pCmd->viewangles);

					pCmd->sidemove = 450.f;
					bDirection = true;
				}

			}
		}




		CSetupPlayer __pLocalBaseEntity = gPlayers[me];




		/*bool bEdgeAA = false;

		if (ALX.pCvar->fake_edge)
		{
		if (ALX.PAim->m_MoveType(pLocalEntity) == MOVETYPE_LADDER)
		{
		flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);
		pCmd->forwardmove = cos(flYaw) * flSpeed;
		pCmd->sidemove = sin(flYaw) * flSpeed;
		}
		else
		{
		bEdgeAA = ALX.PAim->EdgeAntiAimZ(pLocalEntity, pCmd, 360.f);
		if (bEdgeAA)
		{
		bSendPacket = true;
		pCmd->viewangles.x = 89;
		flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);
		pCmd->forwardmove = -cos(flYaw) * flSpeed;
		pCmd->sidemove = sin(flYaw) * flSpeed;
		}
		}
		}
		*/
		if (ALX.pCvar->standrcs)
		{
			static Vector vecOldPunchAngle = pLocalEntity->GetAngles();
			Vector vecPunchAngle = pLocalEntity->GetPunchAngle() *2.f;
			if (pCmd->buttons & IN_ATTACK)
			{
				if (isValidWeaponRCS(pWeapon->getweaponid()))
				{
					if (HasAmmo(pLocalEntity))
					{
						if (pLocalEntity->m_iShotsFired() > 1)
						{
							ALX.pEngine->SetViewAngles(pCmd->viewangles - (vecPunchAngle - vecOldPunchAngle));
							vecOldPunchAngle = vecPunchAngle;
						}
						else
						{
							vecOldPunchAngle = Vector(0, 0, 0);
						}
					}
				}
			}
		}
		



		if (pWeapon != NULL)
		{

			if (ALX.pCvar->AntiAim)
			{
				AntiAimFunc(pCmd, pLocalEntity, pWeapon);
			}

			//KnifebotStart(pCmd);

			if (ALX.pCvar->head_trigger)
			{
				if (ALX.PTrigger->Trigger(pCmd, pLocalEntity))
				{
					if (isValidWeapon(pWeapon->getweaponid()))
					{
						if (HasAmmo(pLocalEntity))
						{
							pCmd->buttons |= IN_ATTACK;
							if (pCmd->buttons & IN_ATTACK)
							{
								static bool bAttack = false;
								if (bAttack)    pCmd->buttons |= IN_ATTACK;
								else
									pCmd->buttons &= ~IN_ATTACK;
								bAttack = !bAttack;
							}
							else
							{
								pCmd->buttons |= IN_ATTACK;
							}
						}
					}
				}
			}


			if (ALX.pCvar->aimbot)
			{
				if (isValidWeapon(pWeapon->getweaponid()))
				{
					if (HasAmmo(pLocalEntity))
					{
						if (ALX.pCvar->aimonfire)
						{
							ALX.PAim->StealthRotation(pLocalEntity, pCmd);
						}
						else if (ALX.pCvar->aimkey)
						{
							if (GetAsyncKeyState(VK_LBUTTON))
							{
								ALX.PAim->StealthRotation(pLocalEntity, pCmd);
							}
						}
					}
				}
			}



			if (ALX.pCvar->skins)
			{
				pWeapon->SetweaponidB(507);
			}

			CSetupPlayer __pLocalBaseEntity = gPlayers[me];

			CBaseEntity* pLocalBaseEntity = __pLocalBaseEntity.BaseEnt();

			float fServerTime = pLocalBaseEntity->GetTickBase() * ALX.pGlobals->interval_per_tick;
			float fNextAttack = pWeapon->fNextAttack2();



			bool bBulletTime = true;

			if (fNextAttack > fServerTime)
				bBulletTime = false;

			if (ALX.pCvar->aimbot)
			{
				if (ALX.pCvar->silent)
				{
					if (pCmd->buttons & IN_ATTACK && bBulletTime) {
						bSendPacket = false;

					}
					else
					{

						bSendPacket = true;

						if (ALX.pCvar->silent && !ALX.pCvar->AntiAim && ALX.pCvar->fakelag <= 0)
						{
							pCmd->viewangles = view;
							pCmd->sidemove = oldSidemove;
							pCmd->forwardmove = oldForwardmove;
						}

					}
				}
			}
		}





		Vector Punch = pLocalEntity->GetPunchAngle() * 2;
		if (ALX.pCvar->norecoil && pCmd->buttons & IN_ATTACK)
		{
			pCmd->viewangles.x -= Punch.x;
			pCmd->viewangles.y -= Punch.y;

			ALX.pPlayerESP->NormalizeAngle(pCmd->viewangles);
			ALX.pPlayerESP->ClampAngles(pCmd->viewangles);
		}

		if (ALX.pCvar->nospread  && pCmd->buttons & IN_ATTACK)
		{
			ALX.PSpreadz->SpreadFactor(pCmd, pWeapon);
		}


		if (ALX.pCvar->Bunny)
		{
			static bool bLastJumped = false;
			static bool bShouldFake = false;

			if (!bLastJumped && bShouldFake)
			{
				bShouldFake = false;
				pCmd->buttons |= IN_JUMP;
			}
			else if (pCmd->buttons & IN_JUMP)
			{
				if (pLocalEntity->GetFlags() & FL_ONGROUND)
				{
					bLastJumped = true;
					bShouldFake = true;
				}
				else
				{
					pCmd->buttons &= ~IN_JUMP;
					bLastJumped = false;
				}
			}
			else
			{
				bLastJumped = false;
				bShouldFake = false;
			}
		}




		if (ALX.pCvar->autostrafe)
		{

			if ((GetAsyncKeyState(VK_SPACE) && !(pLocalEntity->GetFlags() & FL_ONGROUND)))
			{

				if (pLocalEntity->GetFlags() & FL_ONGROUND)
				{
					if (pLocalEntity->GetVelocity().Length() <= 50)
					{
						pCmd->forwardmove = 450.f;
					}
				}

				if (!(pLocalEntity->GetFlags() & FL_ONGROUND) && pCmd->buttons & IN_JUMP)
				{
					if (pLocalEntity->GetVelocity().Length() <= 50)
					{
						pCmd->forwardmove = 450.f;
					}

				}


				if (pCmd->mousedx < 0)
				{
					pCmd->sidemove = -450.f;
				}

				if (pCmd->mousedx > 0)
				{
					pCmd->sidemove = 450.f;
				}
			}
		}



		if (ALX.pCvar->autostrafe_sideways)
		{

			if ((GetAsyncKeyState(VK_SPACE) && !(pLocalEntity->GetFlags() & FL_ONGROUND)))
			{

				if (pLocalEntity->GetFlags() & FL_ONGROUND)
				{
					if (pLocalEntity->GetVelocity().Length() <= 50)
					{
						pCmd->forwardmove = 450.f;
					}
				}

				if (!(pLocalEntity->GetFlags() & FL_ONGROUND) && pCmd->buttons & IN_JUMP)
				{
					if (pLocalEntity->GetVelocity().Length() <= 50)
					{
						pCmd->forwardmove = 450.f;
					}

				}


				if (pCmd->mousedx < 0)
				{
					pCmd->sidemove = -450.f;
				}

				if (pCmd->mousedx > 0)
				{
					pCmd->sidemove = 450.f;
				}

				pCmd->viewangles.y = 90;

				//flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);
				//pCmd->forwardmove = cos(flYaw) * flSpeed;
				//pCmd->sidemove = sin(flYaw) * flSpeed;
			}
		}




	}
	

	ALX.pPlayerESP->NormalizeAngle(pCmd->viewangles);
	ALX.pPlayerESP->ClampAngles(pCmd->viewangles);

	pVerfied->m_cmd = *pCmd;
	pVerfied->m_crc = pCmd->GetChecksum();

}

__declspec(naked) void hkCreateMove(int seqnr, float time, bool active)
{


	__asm
	{
		push ebp
			mov ebp, esp

			// Save ebx on the stack so we can get its address 
			push ebx

			// Push address of ebx (and thus bSendPacket) on the stack as an argument 
			lea ecx, [esp]
			push ecx
			// Push the rest of the CreateMove arguments on the stack 
			movzx eax, active
			push eax
			mov eax, time
			push eax
			mov eax, seqnr
			push eax
	
			// Call the actual C++ code that will handle the CreateMove callback 
			call HookedCreateMove

			// Restore ebx with whatever value you assigned to bSendPacket in your callback 
			pop ebx

			pop ebp
			retn 0xC
	}
}



bool	bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
	if (*szMask == 'x' && *pData != *bMask)
		return false;

	return (*szMask) == NULL;
}

DWORD FindToPattern(DWORD dwAddress, DWORD dwSize, BYTE* pbMask, char* szMask)
{
	for (DWORD i = NULL; i < dwSize; i++)
	if (bDataCompare((BYTE*)(dwAddress + i), pbMask, szMask))
		return (DWORD)(dwAddress + i);

	return 0;
}


CScreenSize gScreenSize;

static bool bOnce = false;
unsigned long			espfont = NULL;
unsigned long esfont = NULL;
unsigned long waterfont = NULL;
unsigned long AFont = NULL;
#include "PaintTraverse.h"
typedef void(__stdcall *PaintTraverse_)(unsigned int, bool, bool);
PaintTraverse_ oPaintTraverse;
bool Menu = true;

//===================================================================================
void __stdcall Hooked_PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{

	INT Width, Height;

	ALX.pEngine->GetScreenSize(Width, Height);


	try
	{

		ALX.pPanelHook->UnHook();
		oPaintTraverse(vguiPanel, forceRepaint, allowForce);
		ALX.pPanelHook->ReHook();

		if (!bOnce)
		{
			espfont = ALX.pSurface->CreateFontA();
			//g_pSurface->SetFontGlyphSet(espfont, "Helvetica", 12, 500, 0, 0, FONTFLAG_OUTLINE);
			ALX.pSurface->SetFontGlyphSet(espfont, "blank", 12, 500, 0, 0, FONTFLAG_OUTLINE);



			esfont = ALX.pSurface->CreateFontA();
			//g_pSurface->SetFontGlyphSet(esfont, "Verdana", 20, 500, 0, 0, FONTFLAG_OUTLINE);
			ALX.pSurface->SetFontGlyphSet(esfont, "blank", 20, 500, 0, 0, FONTFLAG_OUTLINE);

			AFont = ALX.pSurface->CreateFontA();
			//g_pSurface->SetFontGlyphSet(esfont, "Verdana", 20, 500, 0, 0, FONTFLAG_OUTLINE);
			ALX.pSurface->SetFontGlyphSet(AFont, "blank", 12, 800, 0, 0,FONTFLAG_DROPSHADOW);


			waterfont = ALX.pSurface->CreateFontA();
			ALX.pSurface->SetFontGlyphSet(waterfont, "blank", 50, 500, 0, 0, FONTFLAG_NONE);

			bOnce = true;
		}

	
		PCHAR szPanelName = (PCHAR)ALX.pPanel->GetName(vguiPanel);
		if (strstr(szPanelName, "MatSystemTopPanel"))
		{
			//Draw Watermark
			//ALX.pDrawManager->DrawStringM(waterfont, true, Width / 2, Height / 9, Color(255, 255, 255, 255), "TITANIUM");
			//ALX.pDrawManager->DrawStringM(waterfont, true, Width / 2 + 75, Height / 9, Color(0, 255, 0, 255), "AN");
			//ALX.pDrawManager->DrawStringM(waterfont, true, Width / 2 + 105, Height / 9, Color(255, 255, 255, 255), "  IUM");
			//
			if (GetAsyncKeyState(VK_F1) & 1)
			{
				ALX.pCvar->MenuSwitch = !ALX.pCvar->MenuSwitch;
				ALX.pEngine->ExecuteClientCmd("cl_mouseenable 1");
				Menu = !Menu;
			}

			if (!Menu)
			{
				ALX.pEngine->ExecuteClientCmd("cl_mouseenable 0");
			}

			if (ALX.pCvar->MenuSwitch)
			{
				ALX.pMenu->Render(ALX.pOptions->Menu_X, ALX.pOptions->Menu_Y, 900, 400);
			}

			if (ALX.pEngine->IsInGame() && ALX.pEngine->IsConnected())
			{
				PaintTraverseClass.Invoke();
			}

			if (ALX.pCvar->watermark)
			{
				ALX.pDrawManager->DrawStringM(waterfont, true, Width / 2, Height / 9, Color(255, 255, 255, 255), "El0");
				ALX.pDrawManager->DrawStringM(waterfont, true, Width / 2 + 75, Height / 9, Color(0, 255, 0, 255), "$");
				ALX.pDrawManager->DrawStringM(waterfont, true, Width / 2 + 105, Height / 9, Color(255, 255, 255, 255), "m0k3");
			}


		}


	}
	catch (...)
	{
		ALX.pBaseAPI->LogToFile("Failed PaintTraverse");
		ALX.pBaseAPI->ErrorBox("Failed PaintTraverse");
	}
}

#include "BuildConfig.h"

DWORD WINAPI dwMainThread( LPVOID lpArguments )
{
	
	if (BUILD_DEBUG)
	{
		
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdout);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("Welcome to");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
		printf(" TITANIUM \n");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		printf("Beta \n");
		printf("\n");
		printf("\n");
		printf("Searching Interfaces... ");
	}
	

	if (ALX.pClient == NULL) //Prevent repeat callings.
	{
	
		
		g_ClientFactory = ( CreateInterfaceFn ) GetProcAddress( ALX.pBaseAPI->GetModuleHandleSafe( "client.dll" ), "CreateInterface" );
		g_pEngineFactory = ( CreateInterfaceFn ) GetProcAddress( ALX.pBaseAPI->GetModuleHandleSafe( "engine.dll" ), "CreateInterface" );
		g_VGUIFactory = ( CreateInterfaceFn ) GetProcAddress( ALX.pBaseAPI->GetModuleHandleSafe( "vguimatsurface.dll" ), "CreateInterface" );
		g_VGUI2Factory = ( CreateInterfaceFn ) GetProcAddress( ALX.pBaseAPI->GetModuleHandleSafe( "vgui2.dll" ), "CreateInterface" );

		//===================================================================================
		if (!ALX.pClient)
		{
			ALX.pClient = ( CHLClient* )g_ClientFactory( "VClient016", NULL);
			ALX.pBaseAPI->LogToFile( "g_pClient: [0x%.8X]", (DWORD)ALX.pClient );
			XASSERT(ALX.pClient);
		}

		//===================================================================================
	    if (!ALX.pEntList)
		{
			ALX.pEntList = ( CEntList* ) g_ClientFactory( "VClientEntityList003", NULL );
			ALX.pBaseAPI->LogToFile( "ALX.pEntList: [0x%.8X]", (DWORD)ALX.pEntList);
			XASSERT( ALX.pEntList );
		}
		//===================================================================================
		if( !ALX.pEngine )
		{
			ALX.pEngine = (EngineClient*)g_pEngineFactory("VEngineClient013", NULL);
			ALX.pBaseAPI->LogToFile( "ALX.pEngine: [0x%.8X]", (DWORD)ALX.pEngine);
			XASSERT( ALX.pEngine );
		}
		//===================================================================================
		if (!ALX.pSurface)
		{
			ALX.pSurface = ( ISurface* ) g_VGUIFactory( "VGUI_Surface031", NULL );
			ALX.pBaseAPI->LogToFile( "g_pSurface: [0x%.8X]", (DWORD)ALX.pSurface);
			XASSERT(ALX.pSurface);
		}
		
		//===================================================================================
		if( !ALX.pModelInfo )
		{
			ALX.pModelInfo = ( IVModelInfo* ) g_pEngineFactory( "VModelInfoClient004", NULL );
			ALX.pBaseAPI->LogToFile("g_pModelInfo: [0x%.8X]", (DWORD)ALX.pModelInfo);
			XASSERT(ALX.pModelInfo);
		}
		
		
		//===================================================================================
		if( !ALX.pEngineTrace )
		{
			ALX.pEngineTrace = ( IEngineTrace* ) g_pEngineFactory( "EngineTraceClient004", NULL );
			ALX.pBaseAPI->LogToFile( "ALX.pEngineTrace: [0x%.8X]", (DWORD)ALX.pEngineTrace );
			XASSERT( ALX.pEngineTrace );
		}
		//===================================================================================

		if (ALX.pClient && ALX.pEngine && ALX.pSurface && ALX.pModelInfo && ALX.pEngineTrace)
		{

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			printf("Ok!\n");
		}

		//===================================================================================
		//Setup the CHLClient hooks.
		if (ALX.pClient)
		{

			DWORD dwPredictionLoc = ALX.pBaseAPI->GetClientSignature("\xFF\x35\x00\x00\x00\x00\x8D\x86\x00\x00\x00\x00\xB9\x00\x00\x00\x00", "xx????xx????x????");
			ALX.pPrediction = *(CPrediction**)(dwPredictionLoc + 0xD);

			ALX.pGlobals = *(CGlobalVarsBase**)*(DWORD**)(FindPattern((DWORD)ALX.pBaseAPI->GetModuleHandleSafe("client.dll"), 0x7CE000, (BYTE*)"\xA1\x00\x00\x00\x00\x8B\x4D\xFC\x8B\x55\x08", "x????xxxxxx") + 1);
	
			PDWORD pdwClientVMT = *reinterpret_cast< PDWORD_PTR* >(ALX.pClient);

			ALX.pInput = *(CInput**)(pdwClientVMT[21] + 0x5F);
		

			if (BUILD_DEBUG)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

				printf("Hooking D3D...");
			}

			InitD3D();

			if (BUILD_DEBUG)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				printf("Ok!\n");
			}

			if (BUILD_DEBUG)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
				printf("Hooking Create Move...");
		
				pCreateMoveHook = new CVMTHookManager((PDWORD*)ALX.pClient);
				oMove = (CreateMove_)pCreateMoveHook->dwHookMethod((DWORD)hkCreateMove, 21);

				if (BUILD_DEBUG)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
					printf("Ok!\n");

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);


					printf("Hooking In Prediction...");
				}

				pPredictionHook = new CVMTHookManager((PDWORD*)ALX.pPrediction);
				
				pPredictionHook->dwHookMethod((DWORD)hkInPrediction, 14);

				if (BUILD_DEBUG)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
					printf("Ok!\n");
				}



			CVMTHookManager* g_pClientHook = NULL;
			g_pClientHook = new CVMTHookManager((PDWORD*)ALX.pClient);//Does the same thing as CVMTHookManager::bInitialize.
			//===================================================================================
			if (BUILD_DEBUG)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

				printf("Hooking Key Event...");
			}

			OriginalKeyEvent = (IN_KeyEventFn)g_pClientHook->dwHookMethod((DWORD)Hooked_IN_KeyEvent, 20);

			if (BUILD_DEBUG)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				printf("Ok!\n");
			}
			//===================================================================================
			OriginalCreateMove = (CreateMoveFn)g_pClientHook->dwHookMethod( ( DWORD )Hooked_CreateMove, 21 ); //Hook CreateMove and store the address of the original in OriginalCreateMove. 
			//===================================================================================
			
		}
	
		if (!ALX.pPanel)
		{
			ALX.pPanel = (IPanel*)g_VGUI2Factory("VGUI_Panel009", NULL);
			ALX.pBaseAPI->LogToFile("g_pIPanel: [0x%.8X]", (DWORD)ALX.pPanel);
			XASSERT(ALX.pPanel);

			if (ALX.pPanel)
			{
				if (BUILD_DEBUG)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("Hooking Paint Traverse...");
				}
				ALX.pPanelHook = new CVMTHookManager((PDWORD*)ALX.pPanel);
				oPaintTraverse = (PaintTraverse_)ALX.pPanelHook->dwHookMethod((DWORD)Hooked_PaintTraverse, 41);
					if (BUILD_DEBUG)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
						printf("Ok!\n");
					}
				}
			
		}

		if (ALX.pClientHook->iInited == NULL)
		{
			Hooked_Init();
			ALX.pClientHook->iInited = 1;
		}
	}
	return 0; //The thread has been completed, and we do not need to call anything once we're done. The call to Hooked_PaintTraverse is now our main thread.
}

int WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	//If you manually map, make sure you setup this function properly.
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		ALX.pBaseAPI->BaseUponModule( (HMODULE)hInstance );
		CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)dwMainThread, NULL, 0, NULL );
	
	}
	return true;
}