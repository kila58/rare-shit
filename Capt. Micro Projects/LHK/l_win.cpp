#include "l_win.h"

void l_win_register(lua_State *l)
{
	LUA_REG(l, WriteConsole);
	LUA_REG(l, SetConCursorPos);
	LUA_REG(l, SetConTextAttribute);
	LUA_REG(l, CleanExit);
	LUA_REG(l, Sleep);
	LUA_REG(l, CloseHandle);
	LUA_REG(l, IsKeyDown);
	LUA_REG(l, GetTickCount);
	LUA_REG(l, FindWindow);
	LUA_REG(l, PostMessage);
	LUA_REG(l, SendMessage);
	LUA_REG(l, GetProcessId);
	LUA_REG(l, OpenProcess);
	LUA_REG(l, TerminateProcess);
	LUA_REG(l, GetBaseAddress);
	LUA_REG(l, SigScan);
	LUA_REG(l, AllocMem);
	LUA_REG(l, FreeMem);
	LUA_REG(l, ProtectMem);
	LUA_REG(l, QueryMem);
	LUA_REG(l, ReadByte);
	LUA_REG(l, ReadShort);
	LUA_REG(l, ReadInt);
	LUA_REG(l, ReadLong);
	LUA_REG(l, ReadFloat);
	LUA_REG(l, ReadStr);
	LUA_REG(l, WriteByte);
	LUA_REG(l, WriteShort);
	LUA_REG(l, WriteInt);
	LUA_REG(l, WriteLong);
	LUA_REG(l, WriteFloat);
	LUA_REG(l, WriteStr);
	LUA_REG(l, GetINIInt);
	LUA_REG(l, GetINIFloat);
	LUA_REG(l, GetINIStr);
	LUA_REG(l, SetINIInt);
	LUA_REG(l, SetINIFloat);
	LUA_REG(l, SetINIStr);

	LUA_REG(l, DrawInvalidateRect);
	LUA_REG(l, DrawCreateBrush);
	LUA_REG(l, DrawBox);
	LUA_REG(l, DrawGetTextColor);
	LUA_REG(l, DrawSetTextColor);
	LUA_REG(l, DrawText);

	LUA_REG(l, SetDebugPrivileges);
}

void l_win_globals(lua_State *l)
{
	lua_pushinteger(l, 0);
	lua_setglobal(l, "WINNULL");

	if (VistaOrHigher() == 0) lua_pushinteger(l, 0x000F0000L | 0x00100000L | 0xFFF);
	else lua_pushinteger(l, 0x000F0000L | 0x00100000L | 0xFFFF);
	lua_setglobal(l, "PROCESS_ALL_ACCESS"); //diff tokens on < vista... wtf

	lua_pushinteger(l, 0x0080);
	lua_setglobal(l, "PROCESS_CREATE_PROCESS");
	lua_pushinteger(l, 0x0002);
	lua_setglobal(l, "PROCESS_CREATE_THREAD");
	lua_pushinteger(l, 0x0040);
	lua_setglobal(l, "PROCESS_DUP_HANDLE");
	lua_pushinteger(l, 0x0400);
	lua_setglobal(l, "PROCESS_QUERY_INFORMATION");
	lua_pushinteger(l, 0x0200);
	lua_setglobal(l, "PROCESS_SET_INFORMATION");
	lua_pushinteger(l, 0x0100);
	lua_setglobal(l, "PROCESS_SET_QUOTA");
	lua_pushinteger(l, 0x0800);
	lua_setglobal(l, "PROCESS_SUSPEND_RESUME");
	lua_pushinteger(l, 0x0001);
	lua_setglobal(l, "PROCESS_TERMINATE");
	lua_pushinteger(l, 0x0008);
	lua_setglobal(l, "PROCESS_VM_OPERATION");
	lua_pushinteger(l, 0x0010);
	lua_setglobal(l, "PROCESS_VM_READ");
	lua_pushinteger(l, 0x0020);
	lua_setglobal(l, "PROCESS_VM_WRITE");
	lua_pushinteger(l, 0x00100000L);
	lua_setglobal(l, "SYNCHRONIZE");

	lua_pushinteger(l, 0xFFFF);
	lua_setglobal(l, "HWND_BROADCAST");

	lua_pushinteger(l, 0x0020);
	lua_setglobal(l, "WM_SETCURSOR");

	lua_pushinteger(l, 0x0312);
	lua_setglobal(l, "WM_HOTKEY");
	lua_pushinteger(l, 0x0032);
	lua_setglobal(l, "WM_SETHOTKEY");
	lua_pushinteger(l, 0x0033);
	lua_setglobal(l, "WM_GETHOTKEY");

	lua_pushinteger(l, 0x01);
	lua_setglobal(l, "HOTKEYF_SHIFT");
	lua_pushinteger(l, 0x02);
	lua_setglobal(l, "HOTKEYF_CONTROL");
	lua_pushinteger(l, 0x04);
	lua_setglobal(l, "HOTKEYF_ALT");
	lua_pushinteger(l, 0x08);
	lua_setglobal(l, "HOTKEYF_EXT");

	lua_pushinteger(l, 0x0006);
	lua_setglobal(l, "WM_ACTIVATE");
	lua_pushinteger(l, 0x0102);
	lua_setglobal(l, "WM_CHAR");
	lua_pushinteger(l, 0x0103);
	lua_setglobal(l, "WM_DEADCHAR");
	lua_pushinteger(l, 0x0100);
	lua_setglobal(l, "WM_KEYDOWN");
	lua_pushinteger(l, 0x0101);
	lua_setglobal(l, "WM_KEYUP");
	lua_pushinteger(l, 0x0008);
	lua_setglobal(l, "WM_KILLFOCUS");
	lua_pushinteger(l, 0x0007);
	lua_setglobal(l, "WM_SETFOCUS");
	lua_pushinteger(l, 0x0107);
	lua_setglobal(l, "WM_SYSDEADCHAR");
	lua_pushinteger(l, 0x0104);
	lua_setglobal(l, "WM_SYSKEYDOWN");
	lua_pushinteger(l, 0x0105);
	lua_setglobal(l, "WM_SYSKEYUP");
	lua_pushinteger(l, 0x0109);
	lua_setglobal(l, "WM_UNICHAR");

	lua_pushinteger(l, 0x0201);
	lua_setglobal(l, "WM_LBUTTONDOWN");
	lua_pushinteger(l, 0x0202);
	lua_setglobal(l, "WM_LBUTTONUP");
	lua_pushinteger(l, 0x0204);
	lua_setglobal(l, "WM_MBUTTONDOWN");
	lua_pushinteger(l, 0x0205);
	lua_setglobal(l, "WM_MBUTTONUP");
	lua_pushinteger(l, 0x0207);
	lua_setglobal(l, "WM_MBUTTONDOWN");
	lua_pushinteger(l, 0x0208);
	lua_setglobal(l, "WM_MBUTTONUP");

	lua_pushinteger(l, 0x0001);
	lua_setglobal(l, "MK_LBUTTON");
	lua_pushinteger(l, 0x0010);
	lua_setglobal(l, "MK_MBUTTON");
	lua_pushinteger(l, 0x0002);
	lua_setglobal(l, "MK_RBUTTON");
	
	lua_pushinteger(l, 0x00);
	lua_setglobal(l, "WA_INACTIVE");
	lua_pushinteger(l, 0x01);
	lua_setglobal(l, "WA_ACTIVE");
	lua_pushinteger(l, 0x02);
	lua_setglobal(l, "WA_CLICKACTIVE");

	lua_pushinteger(l, 0xFFFF);
	lua_setglobal(l, "UNICODE_NOCHAR");
	
	lua_pushinteger(l, 0x1000);
	lua_setglobal(l, "MEM_COMMIT");
	lua_pushinteger(l, 0x2000);
	lua_setglobal(l, "MEM_RESERVE");
	lua_pushinteger(l, 0x80000);
	lua_setglobal(l, "MEM_RESET");
	lua_pushinteger(l, 0x20000000);
	lua_setglobal(l, "MEM_LARGE_PAGES");
	lua_pushinteger(l, 0x400000);
	lua_setglobal(l, "MEM_PHYSICAL");
	lua_pushinteger(l, 0x100000);
	lua_setglobal(l, "MEM_TOP_DOWN");

	lua_pushinteger(l, 0x10);
	lua_setglobal(l, "PAGE_EXECUTE");
	lua_pushinteger(l, 0x20);
	lua_setglobal(l, "PAGE_EXECUTE_READ");
	lua_pushinteger(l, 0x40);
	lua_setglobal(l, "PAGE_EXECUTE_READWRITE");
	lua_pushinteger(l, 0x80);
	lua_setglobal(l, "PAGE_EXECUTE_WRITECOPY");
	lua_pushinteger(l, 0x01);
	lua_setglobal(l, "PAGE_NOACCESS");
	lua_pushinteger(l, 0x02);
	lua_setglobal(l, "PAGE_READONLY");
	lua_pushinteger(l, 0x04);
	lua_setglobal(l, "PAGE_READWRITE");
	lua_pushinteger(l, 0x08);
	lua_setglobal(l, "PAGE_WRITECOPY");
	lua_pushinteger(l, 0x100);
	lua_setglobal(l, "PAGE_GAURD");
	lua_pushinteger(l, 0x200);
	lua_setglobal(l, "PAGE_NOCACHE");
	lua_pushinteger(l, 0x400);
	lua_setglobal(l, "PAGE_WRITECOMBINE");
}

BOOL VistaOrHigher()
{
	void *peb;
	_asm
	{
		push EAX
			xor EAX, EAX
			mov EAX, fs:[0x30]
		mov [peb], EAX
			POP EAX
	}
	ULONG OSMinor = *((BYTE*)peb + 0xA4);
	ULONG OSMajor = *((BYTE*)peb + 0xA8);
	ULONG OSPlatform = *((BYTE*)peb + 0xB0);
	BOOL vistaorhigher = 0;
	if (OSPlatform == 2 && OSMajor == 6)
		vistaorhigher = 1;
	return vistaorhigher;
}

DWORD RemoteGMH(HANDLE proc, char *module)
{
	//Write module name to process
	void *rModule = VirtualAllocEx(proc, 0, lstrlenA(module), MEM_COMMIT, PAGE_READWRITE);
	if (rModule == 0) { printf("VirtualAllocEx failed\n"); return 0; }
	WriteProcessMemory(proc, rModule, (void*)module, lstrlenA(module), 0);

	//Get module handle in process
	HANDLE rModThread = CreateRemoteThread(proc, 0, 0, (LPTHREAD_START_ROUTINE)
		GetProcAddress(GetModuleHandle("kernel32.dll"), "GetModuleHandleA"), rModule, 0, 0);
	DWORD rModResult = WaitForSingleObject(rModThread, INFINITE);

	DWORD rModHandle = 0;
	GetExitCodeThread(rModThread, &rModHandle);
	VirtualFreeEx(proc, (void*)rModule, lstrlenA(module), MEM_RELEASE);
	if (rModHandle == 0) { printf("Remote thread exit code is 0\n"); return 0; }

	return rModHandle;
}

DWORD RemoteGMH2(HANDLE proc, char *module)
{
	HANDLE snapshot = INVALID_HANDLE_VALUE;
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetProcessId(proc));
	if (snapshot == INVALID_HANDLE_VALUE) { printf("CreateToolhelp32Snapshot failed\n"); return 0; }

	MODULEENTRY32 me32;
	me32.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(snapshot, &me32)) { printf("Module32First failed\n"); return 0; }

	do {
		if (lstrcmpiA(me32.szModule, module) == 0)
			return (DWORD)me32.modBaseAddr;
	} while (Module32Next(snapshot, &me32));

	return 0;
}

BOOL WritePrivateProfileIntA(LPCSTR lpAppName, LPCSTR lpKeyName, INT nValue, LPCSTR lpFileName)
{
	char TempString[256]; memset(TempString, 0, 256);
	sprintf_s(TempString, 256, " %d", nValue);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, TempString, lpFileName);
}

BOOL WritePrivateProfileFloatA(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT fValue, LPCSTR lpFileName)
{
	char TempString[256]; memset(TempString, 0, 256);
	sprintf_s(TempString, 256, " %.3f", fValue); //max 4 decimal places
	return WritePrivateProfileStringA(lpAppName, lpKeyName, TempString, lpFileName);
}

FLOAT GetPrivateProfileFloatA(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT fDefault, LPCSTR lpFileName)
{
	char TempString[256]; memset(TempString, 0, 256);
	GetPrivateProfileStringA(lpAppName, lpKeyName, "FAILURE", TempString, 256, lpFileName);
	if (strcmp(TempString, "FAILURE") == 0) return fDefault;
	return (FLOAT)atof(TempString);
}

LUA_FUNC(WriteConsole)
{
	if (lua_gettop(l) == 0) return 0;
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int numargs = lua_gettop(l), i = 1;
	for (i = 0; i < numargs; i++)
	{
		char *str = (char*)lua_tostring(l, i + 1);
		WriteFile(hstdout, str, lstrlenA(str), 0, 0);
	}

	return 0;
}

LUA_FUNC(SetConCursorPos)
{
	SHORT X = (SHORT)lua_tointeger(l, 1);
	SHORT Y = (SHORT)lua_tointeger(l, 2);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord; coord.X = X; coord.Y = Y;
	SetConsoleCursorPosition(hstdout, coord);
	return 0;
}

LUA_FUNC(SetConTextAttribute)
{
	UCHAR attribs = (UCHAR)lua_tointeger(l, 1);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hstdout, attribs);
	return 0;
}

LUA_FUNC(CleanExit)
{
	DWORD returnCode = (DWORD)lua_tointeger(l, 1);
	lua_close(l);
	ExitProcess(returnCode);
	//*((DWORD*)0xCCADBEEF) = 0x903F903F;
	return 0;
}

LUA_FUNC(Sleep)
{
	DWORD ms = (DWORD)lua_tointeger(l, 1);
	Sleep(ms);
	return 0;
}

LUA_FUNC(CloseHandle)
{
	HANDLE handle = (void*)((DWORD)lua_tointeger(l, 1));
	BOOL success = CloseHandle(handle);
	lua_pushboolean(l, success);
	return 1;
}

LUA_FUNC(IsKeyDown)
{
	DWORD key = (DWORD)lua_tointeger(l, 1);
	BOOL keydown = 0;
	if (GetAsyncKeyState(key) & 0x8000) keydown = 1;
	lua_pushboolean(l, keydown);
	return 1;
}

LUA_FUNC(GetTickCount)
{
	lua_pushinteger(l, GetTickCount());
	return 1;
}

LUA_FUNC(FindWindow)
{
	char *title = (char*)lua_tostring(l, 1);
	HWND hwnd = FindWindowA(NULL, title);
	lua_pushinteger(l, (DWORD)hwnd);
	return 1;
}

LUA_FUNC(PostMessage)
{
	HWND h = (HWND)lua_tointeger(l, 1);
	UINT msg = (UINT)lua_tointeger(l, 2);
	UINT wparam = (UINT)lua_tointeger(l, 3);
	UINT lparam = (UINT)lua_tointeger(l, 4);
	DWORD dwProcId = 0;
	BOOL retval = PostMessageA(h, msg, wparam, lparam);
	lua_pushboolean(l, retval);
	return 1;
}

LUA_FUNC(SendMessage)
{
	HWND h = (HWND)lua_tointeger(l, 1);
	UINT msg = (UINT)lua_tointeger(l, 2);
	UINT wparam = (UINT)lua_tointeger(l, 3);
	UINT lparam = (UINT)lua_tointeger(l, 4);
	DWORD dwProcId = 0;
	BOOL retval = SendMessageA(h, msg, wparam, lparam);
	lua_pushboolean(l, retval);
	return 1;
}

LUA_FUNC(GetProcessId)
{
	HWND h = (HWND)lua_tointeger(l, 1);
	DWORD dwProcId = 0;
	GetWindowThreadProcessId(h, &dwProcId);
	lua_pushinteger(l, dwProcId);
	return 1;
}

LUA_FUNC(OpenProcess)
{
	DWORD dwAccess = (DWORD)lua_tointeger(l, 1);
	DWORD dwPID = (DWORD)lua_tointeger(l, 2);
	HANDLE h = OpenProcess(dwAccess, FALSE, dwPID);
	lua_pushinteger(l, (DWORD)h);
	return 1;
}

LUA_FUNC(TerminateProcess)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	DWORD dwExitCode = (DWORD)lua_tointeger(l, 2);
	BOOL success = TerminateThread(h, dwExitCode);
	lua_pushinteger(l, success);
	return 1;
}

LUA_FUNC(GetBaseAddress)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	char *modulename = (char*)lua_tostring(l, 2);
	DWORD dwBaseAddress = 0;
	dwBaseAddress = RemoteGMH2(h, modulename);
	lua_pushinteger(l, dwBaseAddress);
	return 1;
}

DWORD _DataCompare(BYTE *data, BYTE *sig, DWORD siglen)
{
	DWORD i = 0;
	for(; i < siglen; i++)
		if ((sig[i] != '?') && (sig[i] != data[i]))
			return 0;
	return (i == siglen);
}
DWORD _FindPattern(DWORD addr, DWORD len, BYTE *sig, DWORD siglen)
{
	DWORD i = 0;
	for (; i < len; i++)
		if (_DataCompare((BYTE*)(addr+i), sig, siglen))
			return addr + i;
	return 0;
}
LUA_FUNC(SigScan)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	DWORD dwAddress = (DWORD)lua_tostring(l, 2);
	DWORD dwMaxScan = (DWORD)lua_tostring(l, 3);
	BYTE *bSig = (BYTE*)lua_tostring(l, 4);
	DWORD dwSigLen = (DWORD)lua_tointeger(l, 5);

	//Get address & size of dll
	if (dwAddress == 0) { lua_pushinteger(l, 1); return 1; }
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQueryEx(h, (void*)dwAddress, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
	DWORD dwLen = mbi.RegionSize;
	if (dwMaxScan > 0) { if (dwMaxScan <= dwLen) dwLen = dwMaxScan; }
	if (mbi.RegionSize == 0) { lua_pushinteger(l, 2); return 1; }

	BYTE *buffer = (BYTE*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0x1000);
	if (buffer == 0) { lua_pushinteger(l, 3); return 1; }

	//Scan every page
	DWORD dwDelta = 0, dwStartAddr = dwAddress;
	do
	{
		ReadProcessMemory(h, (void*)dwAddress, (void*)buffer, 0x1000, 0);
		dwDelta = _FindPattern((DWORD)buffer, 0x1000, bSig, dwSigLen);
		if (dwDelta != 0)
		{
			HeapFree(GetProcessHeap(), 0, buffer);
			dwDelta += dwAddress;
			lua_pushinteger(l, dwDelta);
			return 1;
		}
		dwAddress += 0x1000;
	} while (dwAddress < (dwStartAddr+dwLen));

	HeapFree(GetProcessHeap(), 0, buffer);
	lua_pushinteger(l, 4);
	return 1;
}

LUA_FUNC(AllocMem)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (LPVOID)((DWORD)lua_tointeger(l, 2));
	DWORD dwSize = (DWORD)lua_tointeger(l, 3);
	DWORD dwType = (DWORD)lua_tointeger(l, 4);
	DWORD dwProt = (DWORD)lua_tointeger(l, 5);
	LPVOID dwMemAddr = VirtualAllocEx(h, dwAddr, dwSize, dwType, dwProt);
	lua_pushinteger(l, (DWORD)dwMemAddr);
	return 1;
}

LUA_FUNC(FreeMem)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (LPVOID)((DWORD)lua_tointeger(l, 2));
	DWORD dwSize = (DWORD)lua_tointeger(l, 3);
	DWORD dwType = (DWORD)lua_tointeger(l, 4);
	BOOL success = VirtualFreeEx(h, dwAddr, dwSize, dwType);
	lua_pushinteger(l, success);
	return 1;
}

LUA_FUNC(ProtectMem)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (LPVOID)((DWORD)lua_tointeger(l, 2));
	DWORD dwSize = (DWORD)lua_tointeger(l, 3);
	DWORD dwNewProt = (DWORD)lua_tointeger(l, 4);
	DWORD dwOldProt = 0;
	VirtualProtectEx(h, dwAddr, dwSize, dwNewProt, &dwOldProt);
	lua_pushinteger(l, dwOldProt);
	return 1;
}

LUA_FUNC(QueryMem)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (LPVOID)((DWORD)lua_tointeger(l, 2));
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQueryEx(h, dwAddr, &mbi, sizeof(mbi));
	lua_pushinteger(l, (DWORD)mbi.BaseAddress);
	lua_pushinteger(l, (DWORD)mbi.AllocationBase);
	lua_pushinteger(l, mbi.AllocationProtect);
	lua_pushinteger(l, (DWORD)mbi.RegionSize);
	lua_pushinteger(l, mbi.State);
	lua_pushinteger(l, mbi.Protect);
	lua_pushinteger(l, mbi.Type);
	return 7;
}

LUA_FUNC(ReadByte)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	DWORD dwBytesRead = 0; BYTE buffer;
	ReadProcessMemory(h, (void*)dwAddr, &buffer, 1, &dwBytesRead);
	lua_pushinteger(l, buffer);
	return 1;
}

LUA_FUNC(ReadShort)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	DWORD dwBytesRead = 0; SHORT buffer;
	ReadProcessMemory(h, (void*)dwAddr, &buffer, 2, &dwBytesRead);
	lua_pushinteger(l, buffer);
	return 1;
}

LUA_FUNC(ReadInt)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	DWORD dwBytesRead = 0; INT buffer;
	ReadProcessMemory(h, (void*)dwAddr, &buffer, 4, &dwBytesRead);
	lua_pushinteger(l, buffer);
	return 1;
}

LUA_FUNC(ReadLong)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	DWORD dwBytesRead = 0; LONG buffer;
	ReadProcessMemory(h, (void*)dwAddr, &buffer, 4, &dwBytesRead);
	lua_pushinteger(l, buffer);
	return 1;
}

LUA_FUNC(ReadFloat)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	DWORD dwBytesRead = 0; FLOAT buffer;
	ReadProcessMemory(h, (void*)dwAddr, &buffer, 4, &dwBytesRead);
	lua_pushnumber(l, buffer);
	return 1;
}

LUA_FUNC(ReadStr)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	DWORD dwSize = lua_tointeger(l, 3);

	char buffer[1024];
	DWORD clr = 0; for (; clr < 1024; clr++) buffer[clr] = 0;

	if (dwSize != 0) {
		ReadProcessMemory(h, (void*)dwAddr, &buffer, dwSize, 0);
	} else {
		DWORD i = 0; BYTE bChk = 0;
		ReadProcessMemory(h, dwAddr, &bChk, 1, 0);
		while (bChk != 0) {
			if (i >= 64) break; //to be safe
			buffer[i] = (char)bChk;
			i++;
			ReadProcessMemory(h, (void*)((BYTE*)dwAddr+i), &bChk, 1, 0);
		}
	}

	lua_pushstring(l, buffer);
	return 1;
}

LUA_FUNC(WriteByte)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	BYTE buffer = (BYTE)lua_tointeger(l, 3);
	DWORD dwBytesWritten = 0;
	WriteProcessMemory(h, (void*)dwAddr, &buffer, 1, &dwBytesWritten);
	return 0;
}

LUA_FUNC(WriteShort)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	SHORT buffer = (SHORT)lua_tointeger(l, 3);
	DWORD dwBytesWritten = 0;
	WriteProcessMemory(h, (void*)dwAddr, &buffer, 2, &dwBytesWritten);
	return 0;
}

LUA_FUNC(WriteInt)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	INT buffer = (INT)lua_tointeger(l, 3);
	DWORD dwBytesWritten = 0;
	WriteProcessMemory(h, (void*)dwAddr, &buffer, 4, &dwBytesWritten);
	return 0;
}

LUA_FUNC(WriteLong)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	LONG buffer = (LONG)lua_tointeger(l, 3);
	DWORD dwBytesWritten = 0;
	WriteProcessMemory(h, (void*)dwAddr, &buffer, 4, &dwBytesWritten);
	return 0;
}

LUA_FUNC(WriteFloat)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	FLOAT buffer = (FLOAT)lua_tonumber(l, 3);
	DWORD dwBytesWritten = 0;
	WriteProcessMemory(h, (void*)dwAddr, &buffer, 4, &dwBytesWritten);
	return 0;
}

LUA_FUNC(WriteStr)
{
	HANDLE h = (void*)((DWORD)lua_tointeger(l, 1));
	LPVOID dwAddr = (void*)((DWORD)lua_tointeger(l, 2));
	char *buffer = (char*)lua_tostring(l, 3);
	DWORD dwSize = lstrlenA(buffer);
	DWORD dwBytesWritten = 0;
	WriteProcessMemory(h, (void*)dwAddr, &buffer, dwSize, &dwBytesWritten);
	return 0;
}

LUA_FUNC(GetINIInt)
{
	char *lpAppName = (char*)lua_tostring(l, 1);
	char *lpKeyName = (char*)lua_tostring(l, 2);
	char *lpFileName = (char*)lua_tostring(l, 3);
	UINT nValue = GetPrivateProfileIntA(lpAppName, lpKeyName, 0xFFFFFFFF, lpFileName);
	lua_pushinteger(l, (INT)nValue);
	return 1;
}

LUA_FUNC(GetINIFloat)
{
	char *lpAppName = (char*)lua_tostring(l, 1);
	char *lpKeyName = (char*)lua_tostring(l, 2);
	char *lpFileName = (char*)lua_tostring(l, 3);
	FLOAT  fValue = GetPrivateProfileFloatA(lpAppName, lpKeyName, 0x7FC00000, lpFileName);
	lua_pushnumber(l, fValue);
	return 1;
}

LUA_FUNC(GetINIStr)
{
	char *lpAppName = (char*)lua_tostring(l, 1);
	char *lpKeyName = (char*)lua_tostring(l, 2);
	char *lpFileName = (char*)lua_tostring(l, 3);
	char TempString[256]; memset(TempString, 0, 256);
	GetPrivateProfileStringA(lpAppName, lpKeyName, "FAILURE!", TempString, 256, lpFileName);
	lua_pushstring(l, TempString);
	return 1;
}

LUA_FUNC(SetINIInt)
{
	char *lpAppName = (char*)lua_tostring(l, 1);
	char *lpKeyName = (char*)lua_tostring(l, 2);
	char *lpFileName = (char*)lua_tostring(l, 3);
	INT nValue = (INT)lua_tointeger(l, 4);
	WritePrivateProfileIntA(lpAppName, lpKeyName, nValue, lpFileName);
	return 0;
}

LUA_FUNC(SetINIFloat)
{
	char *lpAppName = (char*)lua_tostring(l, 1);
	char *lpKeyName = (char*)lua_tostring(l, 2);
	char *lpFileName = (char*)lua_tostring(l, 3);
	FLOAT fValue = (FLOAT)lua_tonumber(l, 4);
	WritePrivateProfileFloatA(lpAppName, lpKeyName, fValue, lpFileName);
	return 0;
}

LUA_FUNC(SetINIStr)
{
	char *lpAppName = (char*)lua_tostring(l, 1);
	char *lpKeyName = (char*)lua_tostring(l, 2);
	char *lpFileName = (char*)lua_tostring(l, 3);
	char *lpValue = (char*)lua_tostring(l, 4);
	WritePrivateProfileStringA(lpAppName, lpKeyName, lpValue, lpFileName);
	return 0;
}

LUA_FUNC(DrawInvalidateRect)
{
	HWND h = (HWND)lua_tointeger(l, 1);
	INT x = (INT)lua_tointeger(l, 2);
	INT y = (INT)lua_tointeger(l, 3);
	INT width = (INT)lua_tointeger(l, 4);
	INT height = (INT)lua_tointeger(l, 5);

	HDC hdc = GetWindowDC(h);
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;
	InvalidateRect(h, &rect, TRUE);

	return 0;
}

LUA_FUNC(DrawCreateBrush)
{
	DWORD r = (DWORD)lua_tointeger(l, 1) & 0xFF;
	DWORD g = (DWORD)lua_tointeger(l, 2) & 0xFF;
	DWORD b = (DWORD)lua_tointeger(l, 3) & 0xFF;

	HBRUSH hbrush = CreateSolidBrush(RGB(r, g, b));

	lua_pushinteger(l, (INT)hbrush);
	return 1;
}

LUA_FUNC(DrawBox)
{
	HWND h = (HWND)lua_tointeger(l, 1);
	INT x = (INT)lua_tointeger(l, 2);
	INT y = (INT)lua_tointeger(l, 3);
	INT width = (INT)lua_tointeger(l, 4);
	INT height = (INT)lua_tointeger(l, 5);
	HBRUSH hbrush = (HBRUSH)lua_tointeger(l, 6);
	
	HDC hdc = GetWindowDC(h);
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;
	FrameRect(hdc, &rect, hbrush);

	return 0;
}

LUA_FUNC(DrawGetTextColor)
{
	HWND h = (HWND)lua_tointeger(l, 1);

	HDC hdc = GetWindowDC(h);

	lua_pushinteger(l, GetTextColor(hdc));
	return 1;
}

LUA_FUNC(DrawSetTextColor)
{
	HWND h = (HWND)lua_tointeger(l, 1);

	HDC hdc = GetWindowDC(h);
	if (lua_gettop(l) == 2)
	{
		COLORREF color = (COLORREF)lua_tointeger(l, 2);
		SetTextColor(hdc, color);
	}
	else
	{
		DWORD r = (DWORD)lua_tointeger(l, 2) & 0xFF;
		DWORD g = (DWORD)lua_tointeger(l, 3) & 0xFF;
		DWORD b = (DWORD)lua_tointeger(l, 4) & 0xFF;
		SetTextColor(hdc, RGB(r, g, b));
	}

	return 0;
}

LUA_FUNC(DrawText)
{
	HWND h = (HWND)lua_tointeger(l, 1);
	char *text = (char*)lua_tostring(l, 2);
	UINT fmt = (UINT)lua_tointeger(l, 3);
	INT x = (INT)lua_tointeger(l, 4);
	INT y = (INT)lua_tointeger(l, 5);
	INT width = (INT)lua_tointeger(l, 6);
	INT height = (INT)lua_tointeger(l, 7);

	if (fmt == 0) fmt = DT_SINGLELINE | DT_TOP | DT_LEFT | DT_NOCLIP;

	HDC hdc = GetWindowDC(h);
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;
	DrawText(hdc, text, strlen(text), &rect, fmt);

	return 0;
}

LUA_FUNC(SetDebugPrivileges)
{
	TOKEN_PRIVILEGES Debug_Privileges;

	//STEP 1
	if (!LookupPrivilegeValue (NULL, // Privieleges for the local system
		SE_DEBUG_NAME, // define the name of the privilege 
		&Debug_Privileges.Privileges[0].Luid)) // will get the LUID value into this variable
	{	//if function failed, cannot proceed to the next step
		return GetLastError(); //terminate the outer function
	}

	//STEP 2
	DWORD err = 0; // define error holder, used to store the error code in case of failure
	HANDLE hToken = 0; //  instantiate a token handle 
	if (!OpenProcessToken (GetCurrentProcess (), // current process ID handle
		TOKEN_ADJUST_PRIVILEGES, //set the desired access
		&hToken)) // handle to the token will be held here 
	{	// if function failed, cannot proceed to the next step
		err = GetLastError();  
		if (hToken) // if handle is still valid
			CloseHandle (hToken); // destroy it
		return err; //terminate the outer function
	}

	//STEP3
	Debug_Privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // set to enable privilege
	Debug_Privileges.PrivilegeCount = 1; // working with only one privilege

	if (!AdjustTokenPrivileges (hToken, // access token handle
		FALSE, // do not disable privileges
		&Debug_Privileges, // pointer to the token structure
		0,  // no need for a buffer 
		NULL, // previous state not set
		NULL)) //  no need for a buffer
	{
		err = GetLastError();
		if (hToken) // if handle is still valid
			CloseHandle (hToken); // destroy it
		return err; //terminate the outer function
	}

	return err; 
}
