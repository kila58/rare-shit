#ifndef __CONSOLE_CONSOLE_H__
#define __CONSOLE_CONSOLE_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "Main.h"
#include "ButtonCode.h"

namespace Console
{
	class CConVar
	{
	public:
		enum eStringType
		{
			TYPE_NONE = 0,
			TYPE_BOOL,
			TYPE_FLOAT,
			TYPE_INT,
			TYPE_INVALID,
		};

	private:
		float        m_flValue;
		std::string    m_szVarName;
		std::string m_szVarDescription;

	public:
		CConVar(void);
		CConVar(std::string szVarName, std::string szVarDescription, bool active);
		CConVar(std::string szVarName, std::string szVarDescription, float flValue);
		CConVar(std::string szVarName, std::string szVarDescription, int iValue);
		bool        GetBool(void);
		float        GetFloat(void);
		int            GetInt(void);
		std::string GetVarName(void);
		std::string GetDescription(void);
		std::string GetInfoString(int stringType = TYPE_FLOAT);
		void        Set(bool active);
		void        Set(float flValue);
		void        Set(int iValue);
		void        Setup(std::string szVarName, std::string szVarDescription, bool active);
		void        Setup(std::string szVarName, std::string szVarDescription, float flValue);
		void        Setup(std::string szVarName, std::string szVarDescription, int iValue);
	};

	class CConVarConsole
	{
	public:
		bool                        m_bActive;
		std::size_t                    m_nCurrentPos = 0;
		std::string                    m_szCurrentString;
		std::vector< std::string >    m_vszOutput;
		std::vector< CConVar* >        m_vpConVars;

	private:
		bool        GetBoolFromString(std::string szString);
		bool        IsVar(std::string szVarName);
		UINT        GetConVarIndexByName(std::string szVarName);
		void        EchoCommand(const char* pszString, ...);
		void        HandleCommand(std::string szInput);
		void        HandleInput(std::string szInput, std::vector< std::string >& vszBuffer);

	public:
		CConVarConsole(void);
		~CConVarConsole(void);
		bool        GetBool(std::string szVarName);
		bool        IsActive(void);
		CConVar*    GetVar(std::string szVarName);
		float        GetFloat(std::string szVarName);
		int            GetInt(std::string szVarName);
		void        AddVar(std::string szVarName, std::string szVarDescription, bool active);
		void        AddVar(std::string szVarName, std::string szVarDescription, float flValue);
		void        AddVar(std::string szVarName, std::string szVarDescription, int iValue);
		void        Echo(const char* pszString, ...);
		void        HandleInput(void);
		void        Render(void);
		void        SetActive(bool active);
	};
}

extern Console::CConVarConsole* g_pCVarConsole;

#endif  