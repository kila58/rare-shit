/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

#ifndef __CVMTHOOK_H__
#define __CVMTHOOK_H__

#pragma once

#include <Windows.h>

// in any case this is oub's hooking class *ANY* case
class CVMTHook
{
public:
	CVMTHook()
	{
		memset(this, 0, sizeof(CVMTHook));
	}

	CVMTHook(DWORD** _ClassBase)
	{
		ClassBase = _ClassBase;
		OldVMT = *_ClassBase;
		VMTSize = GetVMTSize(*_ClassBase);
		NewVMT = new DWORD[VMTSize];
		memcpy(NewVMT, OldVMT, sizeof(DWORD) * VMTSize);
		*_ClassBase = NewVMT;
	}

	void UnHook()
	{
		if (ClassBase)
		{
			*ClassBase = OldVMT;
		}
	}

	void ReHook()
	{
		if (ClassBase)
		{
			*ClassBase = NewVMT;
		}
	}

	DWORD GetMethodAddress(unsigned int Index)
	{
		if (Index >= 0 && Index <= VMTSize && OldVMT != NULL)
		{
			return OldVMT[Index];
		}

		return NULL;
	}

	DWORD* GetOldVMT()
	{
		return OldVMT;
	}

	DWORD HookMethod(DWORD NewFunction, int Index)
	{
		if (NewVMT && OldVMT && Index <= (int) VMTSize)
		{
			NewVMT[Index] = NewFunction;
			return OldVMT[Index];
		}

		return NULL;
	}
private:
	DWORD GetVMTSize(DWORD* VMT)
	{
		DWORD Index = 0;

		for (Index = 0; VMT[Index]; Index++)
		if (IsBadCodePtr((FARPROC) VMT[Index]))
			break;

		return Index;
	}

	DWORD** ClassBase;
	DWORD* NewVMT;
	DWORD* OldVMT;
	DWORD VMTSize;
};


/*
class CVMTHook
{
public:
	DWORD Hook ( DWORD new_Function, PDWORD pClass, int index )
	{
		m_NewFunction = new_Function;
		m_FunctionIndex = index;
		m_ClassTable = *( PDWORD* )pClass;
		m_OriginalFunction = m_ClassTable[ m_FunctionIndex ];
		m_FunctionPointer = &m_ClassTable[ m_FunctionIndex ];
		ReHook();
		return FunctionAddress();
	}

	void UnHook ( void )
	{
		MEMORY_BASIC_INFORMATION mbi;
		VirtualQuery( ( LPVOID )m_FunctionPointer, &mbi, sizeof( mbi ) );
		VirtualProtect( ( LPVOID )mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect );
		m_ClassTable[ m_FunctionIndex ] = m_OriginalFunction;
		VirtualProtect( ( LPVOID )mbi.BaseAddress, mbi.RegionSize, mbi.Protect, NULL );
		FlushInstructionCache( GetCurrentProcess(), ( LPCVOID )m_FunctionPointer, sizeof( DWORD ) );
	}

	void ReHook ( void )
	{
		MEMORY_BASIC_INFORMATION mbi;
		VirtualQuery( ( LPVOID )m_FunctionPointer, &mbi, sizeof( mbi ) );
		VirtualProtect( ( LPVOID )mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect );
		m_ClassTable[ m_FunctionIndex ] = m_NewFunction; // this is detected i think
		VirtualProtect( ( LPVOID )mbi.BaseAddress, mbi.RegionSize, mbi.Protect, NULL );
		FlushInstructionCache( GetCurrentProcess(), ( LPCVOID )m_FunctionPointer, sizeof( DWORD ) );
	}

	DWORD FunctionAddress ( void )
	{
		return m_OriginalFunction;
	}

private:
	// Member variables
	int m_FunctionIndex;
	PDWORD m_ClassTable;
	PDWORD m_FunctionPointer;
	DWORD m_NewFunction;
	DWORD m_OriginalFunction;
};
*/
#endif // __CVMTHOOK_H__