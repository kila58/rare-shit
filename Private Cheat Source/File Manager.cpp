#include "File Manager.h" // Base Header

void CFileManager::Initialize(const char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}
//===================================================================================
void CFileManager::ReadInteger(char* szSection, char* szKey, int& iValue)
{
	iValue = GetPrivateProfileInt(szSection,  szKey, iValue, m_szFileName); 
}
//===================================================================================
void CFileManager::ReadFloat(const char* szSection, const char* szKey, float& fltValue)
{
	char szResult[255];
	char sz[255];
	float fltResult;
	sprintf(sz, "%f",fltValue);
	GetPrivateProfileString(szSection,  szKey, sz, szResult, 255, m_szFileName); 
	fltValue = atof(szResult);
}
//===================================================================================
void CFileManager::ReadBoolean(char* szSection, char* szKey, bool& bolValue)
{
	char szResult[255];
	char sz[255];
	bool bolResult;
	sprintf(sz, "%s", bolValue? "true" : "false");
	GetPrivateProfileString(szSection, szKey, sz, szResult, 255, m_szFileName); 
	bolValue = (strcmp(szResult, "True") == 0 || strcmp(szResult, "true") == 0) ? true : false;
}
//===================================================================================
void CFileManager::ReadString(char* szSection, char* szKey, char* szValue)
{
	char* szResult = new char[255];
	memset(szResult, 0x00, 255);
	GetPrivateProfileString(szSection,  szKey, szValue, szResult, 255, m_szFileName); 
	szValue = szResult;
}
//===================================================================================
void CFileManager::WriteInteger(char* szSection, char* szKey, int iValue)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}
//===================================================================================
void CFileManager::WriteFloat(const char* szSection, const char* szKey, float fltValue)
{
	char szValue[255];
	sprintf(szValue, "%f", fltValue);
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}
//===================================================================================
void CFileManager::WriteBoolean(char* szSection, char* szKey, bool bolValue)
{
	char szValue[255];
	sprintf(szValue, "%s", bolValue ? "true" : "false");
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}
//===================================================================================
void CFileManager::WriteString(char* szSection, char* szKey, char* szValue)
{
	WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}
//===================================================================================

