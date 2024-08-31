#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#include <Windows.h>
#include <iostream>

class CFileManager
{
public:
	void Initialize(const char* szFileName); 
	void ReadInteger(char* szSection, char* szKey, int& iValue);
	void ReadFloat(const char* szSection, const char* szKey, float& fltValue);
	void ReadBoolean(char* szSection, char* szKey, bool& bolValue);
	void ReadString(char* szSection, char* szKey, char* szValue);
	void WriteInteger(char* szSection, char* szKey, int iValue); 
	void WriteFloat(const char* szSection, const char* szKey, float fltValue); 
	void WriteBoolean(char* szSection, char* szKey, bool bolValue); 
	void WriteString(char* szSection, char* szKey, char* szValue);
private:
	char m_szFileName[255];
};


#endif