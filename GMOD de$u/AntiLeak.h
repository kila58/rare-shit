#include <Windows.h>
#include "Entrypoint.h"
#include <iostream>
#include <math.h>


LPCSTR af68a868d48f8532215892800b58e1 = "https://dl.dropboxusercontent.com/u/20298158/gaymod/ownd.txt";

int d25487045c3192e13d2f32f345162a81 = rand() % 999999999 + 99999;
std::string e1c5bfeb4d616495fd53c4fbc8f96edd = std::to_string(d25487045c3192e13d2f32f345162a81);
std::string aa59b3aadabfb53149c2b849f1bf146 = e1c5bfeb4d616495fd53c4fbc8f96edd + ".txt";
LPCSTR c93744ed3234aac750f7fb66362abf74 = aa59b3aadabfb53149c2b849f1bf146.c_str();

LPSTR GetUID(){
	TCHAR buf[255] = { 0 };
	DWORD dwBufSize = sizeof(buf);
	HKEY hKey = 0;
	DWORD dwType = REG_SZ;
	LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Cryptography", 0, KEY_WOW64_64KEY | KEY_QUERY_VALUE, &hKey);
	if (lResult)     return NULL;
	DWORD dwSize = 520;
	LPSTR lpszResult = new CHAR[dwSize];
	lpszResult[0] = 0;
	lResult = RegQueryValueEx(hKey, "MachineGuid", 0, &dwType, (LPBYTE)lpszResult, &dwSize);
	if (lResult)
	{
		delete[] lpszResult;
		lpszResult = NULL;
	}
	RegCloseKey(hKey);
	return lpszResult;
}

bool chkHd = false;
void adbg() {
	Sleep(rand() % 2500 + 1500);
	//if( IsDebuggerPresent() ) ExitProcess( 0 );
	LPSTR lpUID = GetUID();
	if (!lpUID) ExitProcess(0);
	HRESULT result = URLDownloadToFile(NULL, af68a868d48f8532215892800b58e1, c93744ed3234aac750f7fb66362abf74, 0, NULL);
	if (FAILED(result)) ExitProcess(0);
	FILE * pFile = fopen(c93744ed3234aac750f7fb66362abf74, "r");
	if (!pFile) ExitProcess(0);
	char buffer[100];
	bool found = false;
	while (fgets(buffer, 100, pFile))
	{
		char * p = strchr(buffer, '\n');
		if (p)*p = 0;
		if (stricmp(buffer, lpUID) == 0)
		{
			Msg("Welcome to eHac: %s!\n", lpUID);
			chkHd = true;
			found = true;
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitHook, 0, 0, 0);
			af68a868d48f8532215892800b58e1 = "%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S";
			TerminateThread(adbg, 0);
			break;
		}
	}
	fclose(pFile);
	if (!found)
	{
		CHAR szPath[MAX_PATH];
		if (GetTempPathA(MAX_PATH, szPath))
		{
			strcat(szPath, "Please Register.txt");
			pFile = fopen(szPath, "w");
			char * text = "Please copy the UID to register this product\n\n\t";
			fwrite(text, 1, strlen(text), pFile);
			fwrite(lpUID, 1, strlen(lpUID), pFile);
			text = "\n\nThank you for using this product.";
			fwrite(text, 1, strlen(text), pFile);
			fclose(pFile);
			ShellExecuteA(NULL, "open", szPath, NULL, NULL, SW_SHOW);
			Sleep(1000);
			DeleteFileA(szPath);
		}
		TerminateThread(adbg, 0);
		//Sleep( 500 );
		ExitProcess(0);
	}
	af68a868d48f8532215892800b58e1 = "%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S";
	DeleteFile(c93744ed3234aac750f7fb66362abf74);
	//ExitProcess(0);
	delete[] lpUID;
}

