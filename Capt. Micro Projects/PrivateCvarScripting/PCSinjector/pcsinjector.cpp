#include "pcsinjector.h"

void WriteConsole(char *str)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWriteen = 0;
	WriteFile(hstdout, str, lstrlenA(str), &dwBytesWriteen, NULL);
}

int CALLBACK WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	PROCESSENTRY32 me;
	DWORD dwSelIdx = 0, dwMaxIdx = 0, dwProcId = 0, dwBytesWritten = 0;
	COORD pos; pos.X = 0; pos.Y = 0;

	AllocConsole();

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		WriteConsole("Failed to create snapshot\n");
		FreeConsole();
		return 1;
	}
	else
	{
		me.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(hSnapshot, &me))
		{
			WriteConsole("Failed to get first proccess\n");
			CloseHandle(hSnapshot);
		}
		else
		{
			pos.X = 0; pos.Y = 3;
			do
			{
				if (lstrlenA(me.szExeFile) <= 8)
				{
					pos.Y++;
				}
			}
			while (Process32Next(hSnapshot, &me));
			dwMaxIdx = pos.Y - 3 - 1;
		}
	}

	/*wait for user to select process*/
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (!GetAsyncKeyState(VK_SPACE))
	{
		Sleep(150);
		//clear screen
		pos.X = 0; pos.Y = 0;
		SetConsoleCursorPosition(hstdout, pos);
		CONSOLE_SCREEN_BUFFER_INFO sbi;
		GetConsoleScreenBufferInfo(hstdout, &sbi);
		FillConsoleOutputCharacter(hstdout, ' ', sbi.dwSize.X * sbi.dwSize.Y, pos, &dwBytesWritten);
		//draw process selection screen
		WriteConsole("Select Process (only processes with exe names less than 8 chars are listed)\n");
		WriteConsole("*** Press ");
		SetConsoleTextAttribute(hstdout, BACKGROUND_GREEN);
		WriteConsole("SPACE");
		SetConsoleTextAttribute(hstdout, sbi.wAttributes);
		WriteConsole(" to inject into process ***\n");
		WriteConsole("==[ exe name ]=================================================================\n");
		if (hSnapshot != INVALID_HANDLE_VALUE)
		{
			me.dwSize = sizeof(PROCESSENTRY32);
			if (!Process32First(hSnapshot, &me))
			{
				WriteConsole("Failed to get first proccess\n");
				CloseHandle(hSnapshot);
			}
			else
			{
				pos.X = 2; pos.Y = 3;
				do
				{
					if (lstrlenA(me.szExeFile) <= 8)
					{
						SetConsoleCursorPosition(hstdout, pos);
						if ((pos.Y - 3) == dwSelIdx) {
							SetConsoleTextAttribute(hstdout, BACKGROUND_GREEN);
							dwProcId = me.th32ProcessID;
						}
						WriteConsole(me.szExeFile);
						if ((pos.Y - 3) == dwSelIdx) {
							SetConsoleTextAttribute(hstdout, sbi.wAttributes);
						}
						pos.Y++;
					}
				}
				while (Process32Next(hSnapshot, &me));
			}
		}
		//key detection
		while ((!GetAsyncKeyState(VK_UP)) && (!GetAsyncKeyState(VK_DOWN)) && (!GetAsyncKeyState(VK_SPACE)));
		if ((dwSelIdx >= 1) && (GetAsyncKeyState(VK_UP))) dwSelIdx--;
		if ((dwSelIdx < dwMaxIdx) && (GetAsyncKeyState(VK_DOWN))) dwSelIdx++;
	}
	CloseHandle(hSnapshot);
	/*wait for user to select process*/

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, dwProcId);
	if (hProc == 0)
	{
		WriteConsole("    Failed to open process...");
		Sleep(5000);
		return 1;
	}

	char *szModule = (char*)GlobalAlloc(GMEM_ZEROINIT, MAX_PATH);
	ExpandEnvironmentStringsA("%SystemDrive%\\PCS\\PCS.dll", szModule, MAX_PATH);

	//copy lua5.1.dll to exe path
	DWORD dwTempMax = MAX_PATH;
	char *szTemp = (char*)GlobalAlloc(GMEM_ZEROINIT, dwTempMax);
	QueryFullProcessImageName(hProc, 0, szTemp, &dwTempMax);
	char *szTempPtr = szTemp + lstrlenA(szTemp) - 1;
	while (*szTempPtr != '\\') szTempPtr--;
	*(szTempPtr+1) = 0; //stip exe name
	lstrcatA(szTemp, "lua5.1.dll");
	char *szLua51 = (char*)GlobalAlloc(GMEM_ZEROINIT, MAX_PATH);
	ExpandEnvironmentStringsA("%SystemDrive%\\PCS\\lua5.1.dll", szLua51, MAX_PATH);
	WriteConsole("    Copying lua5.1.dll...");
	CopyFileA(szLua51, szTemp, FALSE);
	GlobalFree(szLua51);
	GlobalFree(szTemp);
	
	WriteConsole("    Injecting...");

	//Write module name to process
	void *rModule = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT, PAGE_READWRITE);
	if (rModule == 0)
	{
		WriteConsole("    Failed to allocate memory...");
		Sleep(5000);
		return 1;
	}
	WriteProcessMemory(hProc, rModule, (void*)szModule, MAX_PATH, 0);

	//Get module handle in process
	HANDLE rModThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)
		GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA"), rModule, 0, 0);
	DWORD rModResult = WaitForSingleObject(rModThread, INFINITE);

	//Retrieve remote module address
	HMODULE rModHandle = 0;
	GetExitCodeThread(rModThread, (DWORD*)&rModHandle);
	if ((rModHandle == 0) || (rModHandle == INVALID_HANDLE_VALUE))
	{
		WriteConsole("    Failed to inject.");
		Sleep(5000);
	}

	//Free module name in process
	VirtualFreeEx(hProc, (void*)rModule, MAX_PATH, MEM_RELEASE);

	CloseHandle(hProc);
	return 0;
}
