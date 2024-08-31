#pragma once

#include "SDK.h"

//Original CBaseAPI class by P47TR!CK

class CBaseAPI
{
private:
	bool bDataCompare( const BYTE*, const BYTE*, const char* );
	char szDirectory [ 255 ];

public:
	DWORD dwFindPattern( DWORD, DWORD, BYTE*, char*);
	HMODULE GetModuleHandleSafe( const char* pszModuleName );
	void LogToFile( const char * pszMessage, ... );
	DWORD GetClientSignature ( char* chPattern, char* chMask );
	DWORD GetEngineSignature ( char* chPattern, char* chMask );
	void ErrorBox ( char* error );
	void BaseUponModule( HMODULE hmModule );
	char* GetDirectoryFile( char *szFile );
};

