#include "Main.h"
CInterface intf;
PTfn orgPaintTraverse;
CVars gCvars;
FrameStageNotifyFn orgFrameStageNotify;
CreateMoveFn orgCreateMove;

int CBaseEntityNew::m_ArmorValue()
{
	static DWORD offset = netVars->GetOffset("DT_BasePlayer", "m_ArmorValue");
	return *reinterpret_cast<int*>((DWORD)this + offset);
}
bool CBaseEntityNew::m_bHasHelmet()
{
	static DWORD offset = netVars->GetOffset("DT_BasePlayer", "m_bHasHelmet");
	return *reinterpret_cast<bool*>((DWORD)this + offset);
}
Vector& CBaseEntityNew::OBBMins()
{
	return *reinterpret_cast<Vector*>((DWORD)this + 0x8 + 0x314);
}
Vector& CBaseEntityNew::OBBMaxs()
{
	return *reinterpret_cast<Vector*>((DWORD)this + 0x14 + 0x314);
}
int CBaseEntityNew::GetRank()
{
	static DWORD offset = netVars->GetOffset("DT_CSPlayerResource", "m_iCompetitiveRanking");
	DWORD IGameResources = 0x2e5d9cc; //string ref "#player" mov edi, POINTER
	return *reinterpret_cast<int*>((DWORD)GetModuleHandleA("client") + IGameResources + offset + this->GetIndex() * 4);
}
int CBaseEntityNew::GetWins()
{
	static DWORD offset = netVars->GetOffset("DT_CSPlayerResource", "m_iCompetitiveWins");
	DWORD IGameResources = 0x2e5d9cc;
	return *reinterpret_cast<int*>((DWORD)GetModuleHandleA("client") + IGameResources + offset + this->GetIndex() * 4);
}
void ShowConsole()
{
	BOOL f1 = AllocConsole();
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL)
	{
		HMENU hMenu = GetSystemMenu(hwnd, FALSE);
		if (hMenu != NULL)
		{
			BOOL f2 = DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
		}
	}
	BOOL f3 = SetConsoleTitle("[pHook]: Developer Console");
	FILE *t1 = freopen("CONIN$", "r", stdin);
	FILE *t2 = freopen("CONOUT$", "w", stdout);
	FILE *t3 = freopen("CONOUT$", "w", stderr);
}
void __fastcall hkPaintTraverse(void* thisptr, void*, unsigned int panel, bool b, bool c)
{
	orgPaintTraverse(thisptr, panel, b, b);
	gPaintTraverse.Invoke(panel);
}
void __fastcall hkFrameStageNotify(void* thisptr, void*, ClientFrameStage_t curStage)
{
	Vector *pPunchAngle = nullptr;
	Vector *PunchAngle = nullptr;
	Vector vPunchAngle;
	Vector vpunchAngle;
	if (curStage == FRAME_RENDER_START)
	{
		CBaseEntityNew* me = (CBaseEntityNew*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
		if (me && gCvars.novisrecoil)
		{
			/*m_local + m_viewPunchAngle*/
			pPunchAngle = (Vector*)(me + 0x13DC);
			/*m_local + m_aimPunchAngle*/
			PunchAngle = (Vector*)(me + 0x13E8);
			if (pPunchAngle && PunchAngle)
			{
				vPunchAngle = *pPunchAngle;
				pPunchAngle->Init();
				vpunchAngle = *PunchAngle;
				PunchAngle->Init();
			}
		}
	}
	orgFrameStageNotify(thisptr,curStage);
	if (pPunchAngle)
		*pPunchAngle = vPunchAngle;
	if (PunchAngle)
		*PunchAngle = vpunchAngle;
}
void RunPrediction(CUserCmd* cmd, CBaseEntityNew* me)
{
	int oldcount = Globals->tickcount;
	int oldTick = cmd->tick_count;
	int oldcmdnum = cmd->command_number;
	int oldbuttons = cmd->buttons;
	C_BasePlayer *local = (CBasePlayer*)me;
	C_CommandContext *ctx = local->GetCommandContext();
	if (!ctx)
		return;
	if (!Globals->tickcount)
		return;
	bool needproc = ctx->needsprocessing;
	CUserCmd* oCmd = &ctx->cmd;
	int onum = ctx->command_number;
	ctx->needsprocessing = true;
	ctx->cmd = *cmd;
	ctx->command_number = cmd->command_number;
	Globals->tickcount = oldcount - 5;
	me->PhysicsSimulate();
	Globals->tickcount = oldcount;
	ctx->needsprocessing = needproc;
	ctx->command_number = onum;
	ctx->cmd = *oCmd;

	cmd->tick_count = oldTick;
	cmd->command_number = oldcmdnum;
	cmd->buttons = oldbuttons;
}
void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active, BYTE &bSendPacket)
{
	orgCreateMove(sequence_number, input_sample_frametime, active);
	CUserCmd* cmd = Input->GetUserCmd(sequence_number);
	CBaseEntityNew* me = (CBaseEntityNew*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
	RunPrediction(cmd, me);
	gCreateMove.Invoke(cmd,  bSendPacket);
	CInput::CVerifiedUserCmd *verified = *(CInput::CVerifiedUserCmd**)((DWORD)Input + 0xF0);
	CInput::CVerifiedUserCmd *verifiedcmd = &verified[sequence_number % 150];
	if (verifiedcmd)
	{
		verifiedcmd->m_cmd = *cmd;
		verifiedcmd->m_crc = CRC32_ProcessSingleBuffer(cmd, sizeof(cmd));
	}

}
bool bDataCompare(const BYTE *pData, const BYTE *bMask, const char *szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
	if (*szMask == 'x' && *pData != *bMask)
		return false;
	return (*szMask) == NULL;
}

DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char *szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
	if (bDataCompare((BYTE*)(dwAddress + i), bMask, szMask))
		return (DWORD)(dwAddress + i);
	return 0;
}
typedef long(__stdcall* DIPFn)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT PrimitiveCount);
typedef long(__stdcall* EndSceneFn)(LPDIRECT3DDEVICE9);
typedef long(__stdcall *PresentFn)(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
DIPFn orgDIP;
EndSceneFn orgEndScene;
PresentFn orgPresent;


LPDIRECT3DTEXTURE9 texRed, texBlue, texYellow, texOrange;
HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
		return E_FAIL;

	WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;

	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}
void FixAA(const CRecvProxyData *Data, void *Struct, void *Out)
{

	float Pitch = Data->m_Value.m_Float;

	if (Pitch == 90)
		Pitch = 270;
	else if (Pitch == -90)
		Pitch = 90;

	*(float*)Out = Pitch;

}
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	//rgb(230, 126, 34)
	GenerateTexture(pDevice, &texOrange, D3DCOLOR_XRGB(230, 126, 34));
	GenerateTexture(pDevice, &texRed, D3DCOLOR_XRGB(255, 0, 0));
	GenerateTexture(pDevice, &texBlue, D3DCOLOR_XRGB(0, 0, 255));
	GenerateTexture(pDevice, &texYellow, D3DCOLOR_XRGB(255,255,0));
	return orgEndScene(pDevice);
}

long __stdcall hkDIP(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT PrimitiveCount)
{
	CBaseEntityNew* me = (CBaseEntityNew*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
	LPDIRECT3DVERTEXBUFFER9 sdata;
	uint Stride = 0;
	uint offset = 0;
	if (pDevice->GetStreamSource(0, &sdata, &offset,&Stride) == S_OK)
		sdata->Release();
	
	if ((nohands2) && gCvars.nohands)
		return D3D_OK;
	if (gCvars.chams)
	{
		if ((ct_dx) && me->GetTeamNum() == 2)
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, false);
			pDevice->SetTexture(0, texYellow);
			orgDIP(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, true);
			pDevice->SetTexture(0, texBlue);
		}
		if (allweapons || grenades)
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, false);
			pDevice->SetTexture(0, texOrange);
		}
		if ((t_dx) && me->GetTeamNum() == 3)
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, false);
			pDevice->SetTexture(0, texRed);
			orgDIP(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, true);
			pDevice->SetTexture(0, texBlue);
		}		
	}
	
		
	
	return orgDIP(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, PrimitiveCount);
}
long __stdcall hkPresent(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	return orgPresent(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
CNetworkedVariableManager *netVars;
void OutputNetvars()
{
	netVars = new CNetworkedVariableManager();
	//DT_CSPlayer
	netVars->PrintOffset("DT_BaseEntity", "m_vecOrigin");
	netVars->PrintOffset("DT_CSPlayer", "m_bSpotted");
	netVars->PrintOffset("DT_CSPlayer", "m_Local");
	netVars->PrintOffset("DT_CSPlayer", "m_vecViewOffset[0]");
	netVars->PrintOffset("DT_CSPlayer", "m_vecVelocity[0]");
	netVars->PrintOffset("DT_CSPlayer", "m_iFOV");
	netVars->PrintOffset("DT_CSPlayer", "m_fFlags");
	netVars->PrintOffset("DT_CSPlayer", "m_bHasDefuser");
	netVars->PrintOffset("DT_CSPlayer", "m_bIsDefusing");
	netVars->PrintOffset("DT_CSPlayerResource", "m_iCompetitiveRanking");
	netVars->PrintOffset("DT_CSPlayerResource", "m_iCompetitiveWins");
}
CVMTHookManager *ModelRenderHook = new CVMTHookManager();
DrawModelExecuteFn orgDrawModelExecute;
/*void __stdcall hkDrawModelExecute(IMatRenderContext * ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld){
	ModelRenderHook->UnHook();
	if (pInfo.pModel)
	{
		string pszModelName = ModelInfo->GetModelName(pInfo.pModel);
		if (pszModelName.find("models/player") != string::npos && gCvars.chams)
		{
			IMaterial *mats[MAXSTUDIOSKINS];
			studiohdr_t* hdr = ModelInfo->GetStudiomodel(pInfo.pModel);
			Color col, col2;
			CBaseEntityNew* modelent = (CBaseEntityNew*)ClientEntList->GetClientEntity(pInfo.entity_index);
			if (modelent)
			{
				CBaseEntityNew* me = (CBaseEntityNew*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
				if (me)
				{
					if (modelent->isAlive() && modelent->GetTeamNum() != me->GetTeamNum())
					{
						ModelInfo->GetModelMaterials(pInfo.pModel, hdr->numtextures, mats);
						for (int i = 0; i < hdr->numtextures; i++)
						{
							IMaterial* mat = mats[i];
							if (!mat)
								continue;
							mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
							mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, true);
							mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, true);
							col = colRed;
							ModelRender->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
							mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
							mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, false);
							mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, false);
						}
					}
					else
					{
						ModelInfo->GetModelMaterials(pInfo.pModel, hdr->numtextures, mats);
						for (int i = 0; i < hdr->numtextures; i++)
						{
							IMaterial* mat = mats[i];
							if (!mat)
								continue;
							mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
							mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, false);
							mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, false);
						}
					}
				}
			}
		}
	}
	ModelRender->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
	ModelRender->ForcedMaterialOverride(NULL);
	ModelRenderHook->ReHook();
}*/
void InitD3D()
{	
	DWORD addy = 0x1B6E48;
	CVMTHookManager* d3d = new CVMTHookManager();
	if (d3d->bInitialize((PDWORD*)(*(DWORD*)((DWORD)GetModuleHandle("shaderapidx9") + addy))))
	{
		//Present 17
		//SetRenderState // 57
		orgDIP = (DIPFn)d3d->dwHookMethod((DWORD)hkDIP, 82);
		orgEndScene = (EndSceneFn)d3d->dwHookMethod((DWORD)hkEndScene, 42);
		//orgPresent = (PresentFn)d3d->dwHookMethod((DWORD)hkPresent, 17);
	}
}
#define C g_pCVarConsole
void StartConsole()
{
	C->AddVar("nohands", "Removes hands from drawing", true);
	C->AddVar("spinbot", "Smooth spinbot", false); 
	C->AddVar("aimbot_fov", "fov for aimbot lockon", 270.f);
	C->Echo("Welcome to pHook");
	C->Echo("DEL to toggle console");
	C->Echo("INSERT to toggle menu");
}
//Credits to Daniel
CUserCmd* __fastcall hkGetUserCmd(void* thisptr, void*, int nSlot, int sqnum)
{
	//0xAC or 0xE4
	static CUserCmd* pCommands = *(CUserCmd**)((DWORD)Input + 0xE4);
	CUserCmd *pCmd = &pCommands[sqnum % 150];
	pCmd->command_number = 142;
	pCmd->random_seed = MD5_PseudoRandom(142) & 0x7FFFFFF;

	return pCmd;
}
byte editedsendpacket;

void __stdcall testfunc(byte bSendPacket, int sequence_number, float input_sample_frametime, bool active)
{
	hkCreateMove(sequence_number, input_sample_frametime, active, bSendPacket);
	editedsendpacket = bSendPacket;
}
__declspec(naked) void hkCreateMoveThunk(int seqnr, float ttime, int active)
{
	
	/*BYTE *bSendPacket;
	//I know my casts are wrong but this is just theory
	__asm
	{
		//moves ebx to the top of the stack
		push ebx
			//gets bl
			lea ecx, [esp]
			//bSendPacket = bl
			mov bSendPacket, ecx
			//maybe pop ebx
	}
	actualcreatemove // call me with inline asm
		__asm pop ebx;*/
	__asm
	{
		//__stdcall testfunc(byte bSendPacket,int sequence_number, float input_sample_frametime, bool active)
		push ebp
			mov ebp, esp
			mov eax, [ebp + 0x4]
			add eax, 0x1f
			mov[ebp + 0x4], eax
			push active
			push ttime
			push seqnr
			push bl
			call testfunc
			mov bl, editedsendpacket
		pop ebp
		retn 0xC
	}
	/*__asm
	{
		push ebp
			mov ebp, esp

			mov eax, [ebp + 0x4]
			add eax, 0x1f
			mov[ebp + 0x4], eax

			// Save ebx on the stack so we can get its address


			push ebx

			// Push address of ebx (and thus bSendPacket) on the stack as an argument
			lea ecx, [esp]
			push ecx

			//push CL_Moves return address onto the stack
			lea eax, [ebp + 0x70]
			push eax

			// Push the rest of the CreateMove arguments on the stack
			mov eax, active
			push eax
			mov eax, ttime
			push eax
			mov eax, seqnr
			push eax

			// Call the actual C++ code that will handle the CreateMove callback
			call hkCreateMove

			// Restore ebx with whatever value you assigned to bSendPacket in your callback
			pop ebx

			pop ebp
			retn 0xC
	}*/
	
	
}
CBaseCombatWeapon* CBaseEntityNew::GetWeapon()
{
	EHANDLE handle = *reinterpret_cast<EHANDLE*>((DWORD)this + 0x12c0);
	return (CBaseCombatWeapon*)ClientEntList->GetClientEntityFromHandle(handle);
}
void InitThread()
{
	
	//FILE* file = fopen("C:\\LOGFILE.txt", "w");
	//fclose(file);
	ShowConsole();
	intf.GetInterfaces();
	cout << "1\n";
	//CVMTHookManager* clientmode = new CVMTHookManager((PDWORD*)(*(DWORD*)((DWORD)GetModuleHandle("client") + 0x4A7D06C)));
	//clientmode->dwHookMethod((DWORD)&hkClientModeCreateMove, 24);
	CVMTHookManager* VPanelh = new CVMTHookManager((PDWORD*)VPanel);
	orgPaintTraverse = (PTfn)VPanelh->dwHookMethod((DWORD)hkPaintTraverse, 41);
	cout << "2\n";
	CVMTHookManager* clienthook = new CVMTHookManager((PDWORD*)Client);
	orgFrameStageNotify = (FrameStageNotifyFn)clienthook->dwHookMethod((DWORD)hkFrameStageNotify, 36);
	cout << "3\n";
	orgCreateMove = (CreateMoveFn)clienthook->dwHookMethod((DWORD)hkCreateMoveThunk, 21);
	cout << "4\n";
	ModelRenderHook->bInitialize((PDWORD*)ModelRender);
	//orgDrawModelExecute = (DrawModelExecuteFn)ModelRenderHook->dwHookMethod((DWORD)hkDrawModelExecute, 21);
	//TODO: Fix, not in the mood to.
	//CVMTHookManager* inputhook = new CVMTHookManager((PDWORD*)Input);
	//inputhook->dwHookMethod((DWORD)hkGetUserCmd, 8);
	
	//DWORD d3ddevice = reinterpret_cast<DWORD>(GetModuleHandle("shaderapidx9.dll")) + 0x1B6E48; /*Call before CreateVertexBuffer http://www.unknowncheats.me/forum/804779-post6.html */
	//CVMTHookManager* D3DHook = new CVMTHookManager((PDWORD*)d3ddevice);
	//DWORD addy = D3DHook->dwGetMethodAddress(82);
	//cout << "0x" << hex << addy << endl;
	//orgDIP = (DIPFn)D3DHook->dwHookMethod((DWORD)hkDIP, 82);
	gDrawManager.Initialize();
	//InitD3D();
	cout << "pHook loaded!\nby snorflake\n";
	/*for (ClientClass *clazz = Client->GetAllClasses(); clazz != null; clazz = clazz->m_pNext)
	{
		RecvTable* table = clazz->m_pRecvTable;
		gNetVarDump.DumpTable(table, 0);
	}*/
	cout << "NETVAR DUMP: C:\\LOGFILE.txt\n";
	cout << "5\n";
	OutputNetvars();
	cout << "6\n";
	//StartConsole();
	netVars->HookProp("DT_CSPlayer", "m_angEyeAngles[0]", FixAA);
	
}
bool WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID)
{
	DisableThreadLibraryCalls(inst);
	if (reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitThread, 0, 0, 0);
	}
	return true;
}	