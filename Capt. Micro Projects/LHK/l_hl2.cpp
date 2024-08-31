#include "l_hl2.h"

void l_hl2_register(lua_State *l)
{
	LUA_REG(l, HL2_IVEngineClient_Init);
	LUA_REG(l, HL2_IVEngineClient_ConCmd);
}

void l_hl2_globals(lua_State *l)
{
	
}

#define inline_hash(i,hsh,dat,len) \
	if (dat != 0 && (len) != 0) \
	{ \
		for(i=0,hsh=0xDE4DEA75; i < (len); dat++,i++) \
			hsh ^= ((i&1)==0) ? ((hsh<<7)^(*dat)*(hsh>>3)) \
			: (~((hsh<<11)+((*dat)^(hsh>>5)))); \
	}

DWORD WINAPI IVEngineClient_CodeCave(LPVOID param)
{
	HL2INJDAT *fn = (HL2INJDAT*)param;
	if (fn == 0) return 1;

	HMODULE client = fn->LoadLibraryA("client.dll");
	if (client == 0) return 2;

	CreateInterfaceFn _engine = (CreateInterfaceFn)
		fn->GetProcAddress(client, "CreateInterfaceFn");
	if (_engine == 0) return 3;

	IVEngineClient *engine = (IVEngineClient*)_engine(
		VENGINE_CLIENT_INTERFACE_VERSION, 0);
	if (engine == 0) return 4;

	BOOL running = 1;
	DWORD i = 0, lasthash = 0, newhash = 0;
	DWORD hashdatalen = sizeof(HL2INJPKT);

	while (running > 0)
	{
		if (fn->PKT == 0) continue;
		//check for new command packet
		inline_hash(i, newhash, (BYTE*)fn->PKT, hashdatalen);
		if (lasthash != newhash) //found new packet
		{
			switch (fn->PKT->dwCommandCode) //execute the packet
			{
				case 0x00010000: //change team
					engine->ChangeTeam((const char*)fn->PKT->bData);
					fn->PKT->dwReturnCode = 0;
					break;
				case 0x00020000: //checkpoint (notify test scripts we are at a specific spot in code)
					engine->CheckPoint((const char*)fn->PKT->bData);
					fn->PKT->dwReturnCode = 0;
					break;
				case 0x00030000: //client console command
					engine->ClientCmd((const char*)fn->PKT->bData);
					fn->PKT->dwReturnCode = 0;
					break;
				case 0x00040000: //unrestricted client console command
					engine->ClientCmd_Unrestricted((const char*)fn->PKT->bData);
					fn->PKT->dwReturnCode = 0;
					break;
				case 0x00050000: //check if console is visible
					fn->PKT->dwReturnCode = (DWORD)engine->Con_IsVisible();
					break;
				case 0x00060000: //print string to console
					engine->Con_NPrintf(0, (const char*)fn->PKT->bData);
					fn->PKT->dwReturnCode = 0;
					break;
				case 0x00070000: //execute client command
					engine->ExecuteClientCmd((const char*)fn->PKT->bData);
					fn->PKT->dwReturnCode = 0;
					break;
				case 0x00080000: //check if player is in game
					fn->PKT->dwReturnCode = (DWORD)engine->IsInGame();
					break;
				case 0x000F0000: //stop injection thread
					running = 0;
					fn->PKT->dwReturnCode = 0;
					break;
			}
			lasthash = newhash;
		}
	}

	return 0;
}

LUA_FUNC(HL2_IVEngineClient_Init)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));

	HL2INJDAT param;
	ZeroMemory(&param, sizeof(HL2INJDAT));

	HMODULE k32 = LoadLibraryA("kernel32.dll");
	param.LoadLibraryA = (_LoadLibraryA)GetProcAddress(k32, "LoadLibraryA");
	param.GetProcAddress = (_GetProcAddress)GetProcAddress(k32, "GetProcAddress");
	param.Sleep = (_Sleep)GetProcAddress(k32, "Sleep");
	param.PKT = 0;

	HL2INJPKT initpkt;
	ZeroMemory(&initpkt, sizeof(HL2INJDAT));
	initpkt.dwCommandCode = 0x00060000;
	lstrcpyA((char*)&initpkt.bData, "HL2_IVEngineClient_CodeCave Loaded!\n");

	if (param.LoadLibraryA == 0) { lua_pushinteger(l, 1); return 1; }
	if (param.GetProcAddress == 0) { lua_pushinteger(l, 2); return 1; }
	if (param.Sleep == 0) { lua_pushinteger(l, 3); return 1; }

	DWORD dwBytesWritten = 0;
	
	//allocate packet buffer and copy inital packet
	LPVOID rPkt = VirtualAllocEx(h, 0, sizeof(HL2INJPKT), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (rPkt == 0) { lua_pushinteger(l, 4); return 1; }
	WriteProcessMemory(h, rPkt, &initpkt, sizeof(HL2INJPKT), &dwBytesWritten);
	if (dwBytesWritten != sizeof(HL2INJDAT)) {
		lua_pushinteger(l, 5); lua_pushinteger(l, dwBytesWritten);
		return 1;
	}
	param.PKT = (HL2INJPKT*)rPkt; //uncomment to make packets work

	//allocte inject data and copy
	LPVOID rParam = VirtualAllocEx(h, 0, sizeof(HL2INJDAT), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (rParam == 0) { lua_pushinteger(l, 6); return 1; }
	WriteProcessMemory(h, rParam, &param, sizeof(HL2INJDAT), &dwBytesWritten);
	if (dwBytesWritten != sizeof(HL2INJDAT)) {
		lua_pushinteger(l, 7); lua_pushinteger(l, dwBytesWritten);
		return 1;
	}

	//Create remote process
	HANDLE hThread = CreateRemoteThread(h, 0, 0, IVEngineClient_CodeCave, rParam, 0, 0);

	lua_pushinteger(l, (DWORD)rParam);
	lua_pushinteger(l, (DWORD)rPkt);
	return 2;
}

LUA_FUNC(HL2_IVEngineClient_ConCmd)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	char *concmd = (char*)lua_tostring(l, 2);

	HL2INJPKT initpkt;
	ZeroMemory(&initpkt, sizeof(HL2INJDAT));
	initpkt.dwCommandCode = 0x00030000; //Client console command
	lstrcpyA((char*)&initpkt.bData, concmd);

	//allocate packet buffer and copy inital packet
	DWORD dwBytesWritten = 0;
	LPVOID rPkt = VirtualAllocEx(h, 0, sizeof(HL2INJPKT), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (rPkt == 0) { lua_pushinteger(l, 4); return 1; }
	WriteProcessMemory(h, rPkt, &initpkt, sizeof(HL2INJPKT), &dwBytesWritten);
	if (dwBytesWritten != sizeof(HL2INJDAT)) { lua_pushinteger(l, 1); return 1; }

	return 0;
}
