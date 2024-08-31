#ifndef __NETVARS_H__
#define __NETVARS_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "const.h"
#include "SDK.h"

namespace ValveSDK
{
	class CNetVars
	{
	private:
		ClientClass*				m_pFirstClass;
		std::vector< RecvTable* >	m_vpTables;

	private:
		RecvTable*					GetRecvTable( std::string strTableName );
		int							GetRecvProp( std::string strTableName, std::string strPropName, RecvProp** ppRecvProp = NULL );
		int							GetRecvProp( RecvTable* pRecvTable, std::string strPropName, RecvProp** ppRecvProp = NULL );
		void						DumpTable( RecvTable* pRecvTable );

	public:
		CNetVars( ClientClass* pFirstClass );
		bool						Setup( void );
		bool						HookNetVar( std::string strTableName, std::string strNetVar, RecvVarProxyFn fn );
		DWORD						GetOffset(const char* strTableName, const char* strNetVar);
		void						DumpNetVars( void );
		void						SetFirstClientClass( ClientClass* pFirstClass );
	};
}

extern ValveSDK::CNetVars* g_pNetVars;

#endif