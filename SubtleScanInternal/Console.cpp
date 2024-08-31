#include "Console.h"

#define CONSOLE_X        200
#define CONSOLE_Y        100
#define CONSOLE_WIDTH    700
#define CONSOLE_HEIGHT    900
#define FONT_HEIGHT        14
#define CONSOLE_MAX        42

using namespace Console;

CConVar::CConVar(void)
{

}

CConVar::CConVar(std::string szVarName, std::string szVarDescription, bool active)
{
	Setup(szVarName, szVarDescription, active);
}

CConVar::CConVar(std::string szVarName, std::string szVarDescription, float flValue)
{
	Setup(szVarName, szVarDescription, flValue);
}

CConVar::CConVar(std::string szVarName, std::string szVarDescription, int iValue)
{
	Setup(szVarName, szVarDescription, iValue);
}

bool CConVar::GetBool(void)
{
	return (m_flValue >= 1.f) ? true : false;
}

float CConVar::GetFloat(void)
{
	return m_flValue;
}

int CConVar::GetInt(void)
{
	return int(m_flValue);
}

std::string CConVar::GetVarName(void)
{
	return m_szVarName;
}

std::string CConVar::GetDescription(void)
{
	return m_szVarDescription;
}

std::string CConVar::GetInfoString(int stringType)
{
	char szInfoString[256];

	if (stringType == TYPE_NONE || stringType == TYPE_FLOAT || stringType == TYPE_INVALID)
		sprintf_s(szInfoString, "%s = %.2f", m_szVarName.c_str(), m_flValue);
	else if (stringType == TYPE_INT)
		sprintf_s(szInfoString, "%s = %d", m_szVarName.c_str(), GetInt());
	else if (stringType == TYPE_BOOL)
		sprintf_s(szInfoString, "%s is %s", m_szVarName.c_str(), GetBool() ? "enabled" : "disabled");

	return szInfoString;
}

void CConVar::Set(bool active)
{
	Set(active ? 1.f : 0.f);
}

void CConVar::Set(float flValue)
{
	m_flValue = flValue;
}

void CConVar::Set(int iValue)
{
	Set(float(iValue));
}

void CConVar::Setup(std::string szVarName, std::string szVarDescription, bool active)
{
	m_szVarName = szVarName;
	m_szVarDescription = szVarDescription;
	Set(active);
}

void CConVar::Setup(std::string szVarName, std::string szVarDescription, float flValue)
{
	m_szVarName = szVarName;
	m_szVarDescription = szVarDescription;
	Set(flValue);
}

void CConVar::Setup(std::string szVarName, std::string szVarDescription, int iValue)
{
	m_szVarName = szVarName;
	m_szVarDescription = szVarDescription;
	Set(iValue);
}

bool CConVarConsole::IsVar(std::string szVarName)
{
	if (szVarName.empty())
		return false;

	return (GetConVarIndexByName(szVarName) != -1);
}

UINT CConVarConsole::GetConVarIndexByName(std::string szVarName)
{
	if (szVarName.empty())
		return -1;

	for (UINT i = 0; i < m_vpConVars.size(); i++)
	if (!m_vpConVars.at(i)->GetVarName().compare(szVarName))
		return i;

	return -1;
}

void CConVarConsole::EchoCommand(const char* pszString, ...)
{
	va_list args;
	va_start(args, pszString);
	char szBuffer[256];
	vsprintf_s(szBuffer, pszString, args);
	va_end(args);

	char szCommand[258];
	sprintf_s(szCommand, "] %s", szBuffer);
	Echo(szCommand);
}

void CConVarConsole::HandleCommand(std::string szInput)
{
	if (szInput.empty())
		return;

	std::vector< std::string > vszArgs;
	HandleInput(szInput, vszArgs);

	if (vszArgs.size() < 1)
		return;

	if (!vszArgs.at(0).compare("clear"))
	{
		m_vszOutput.clear();
		return;
	}

	EchoCommand(szInput.c_str());
	std::transform(vszArgs.at(0).begin(), vszArgs.at(0).end(), vszArgs.at(0).begin(), ::tolower);

	if (!vszArgs.at(0).compare("echo"))
	{
		if (vszArgs.size() > 1)
			Echo(szInput.substr(szInput.find(vszArgs.at(1)), szInput.length()).c_str());

		return;
	}
	else if (!vszArgs.at(0).compare("help"))
	{
		if (vszArgs.size() == 1)
		{
			for (UINT i = 0; i < m_vpConVars.size(); i++)
			{
				CConVar* pConVar = m_vpConVars.at(i);
				Echo("%s = %.2f - %s", pConVar->GetVarName().c_str(), pConVar->GetFloat(), pConVar->GetDescription().c_str());
			}
		}
		else
		{
			std::transform(vszArgs.at(1).begin(), vszArgs.at(1).end(), vszArgs.at(1).begin(), ::tolower);
			if (IsVar(vszArgs.at(1)))
			{
				CConVar* pConVar = GetVar(vszArgs.at(1));
				Echo("%s = %.2f - %s", pConVar->GetVarName().c_str(), pConVar->GetFloat(), pConVar->GetDescription().c_str());
			}
			else Echo("Unknown command: %s", vszArgs.at(0).c_str());
		}
		return;
	}
	else if (IsVar(vszArgs.at(0)))
	{
		CConVar* pConVar = GetVar(vszArgs.at(0));

		if (vszArgs.size() == 1)
			Echo(pConVar->GetInfoString().c_str());
		else
		{
			// In case of a digit number (int/float)
			if (isdigit(vszArgs.at(1).c_str()[0]))
			{
				float flValue = 0.f;
				// The dot inside the strig says us that the number is a comma number
				// so we are using the float functions
				if (vszArgs.at(1).find(".") != std::string::npos)
				{
					flValue = std::strtof(vszArgs.at(1).c_str(), NULL);
					pConVar->Set(flValue);

					Echo("Set %s to %.2f", pConVar->GetVarName().c_str(), pConVar->GetFloat());

				}
				else // Otherwise we know that the number is a default number
				{ // and we can use the int functions
					flValue = (float)std::atoi(vszArgs.at(1).c_str());
					pConVar->Set(flValue);

					Echo("Set %s to %d", pConVar->GetVarName().c_str(), pConVar->GetInt());
				}
				return;
			}
			else if (vszArgs.size() > 1 && !vszArgs.at(1).empty())
			{
				std::transform(vszArgs.at(1).begin(), vszArgs.at(1).end(), vszArgs.at(1).begin(), ::tolower);
				bool bIsTrue = !vszArgs.at(1).compare("true") ? true : false;
				bool bIsFalse = !vszArgs.at(1).compare("false") ? true : false;

				if (bIsFalse || bIsTrue)
				{
					if (bIsFalse)
						pConVar->Set(false);
					else pConVar->Set(true);

					Echo("%s %s", bIsTrue ? "Enabled" : "Disabled", pConVar->GetVarName().c_str());
				}
				else Echo("Unknown argument: %s", vszArgs.at(1).c_str());
			}
		}
	}
	else Echo("Unknown command: %s", vszArgs.at(0).c_str());

	return;
}

void CConVarConsole::HandleInput(std::string szInput, std::vector< std::string >& vszBuffer)
{
	std::size_t nPos = 0;
	while (true)
	{
		nPos = szInput.find_first_of(" \n\0");
		if (nPos != std::string::npos)
		{
			vszBuffer.push_back(szInput.substr(0, nPos));
			szInput.erase(0, nPos + 1);
		}
		else
		{
			if (!szInput.empty())
				vszBuffer.push_back(szInput);

			break;
		}
	}
}

CConVarConsole::CConVarConsole(void)
{
	SetActive(true);
}

CConVarConsole::~CConVarConsole(void)
{
	for (UINT i = 0; i < m_vpConVars.size(); i++)
	{
		CConVar* pConVar = m_vpConVars.at(i);
		if (pConVar)
		{
			delete pConVar;
			pConVar = nullptr;
		}
	}

	m_vpConVars.clear();
}

bool CConVarConsole::GetBool(std::string szVarName)
{
	CConVar* pConVar = GetVar(szVarName);
	if (!pConVar)
		return false;

	return pConVar->GetBool();
}

bool CConVarConsole::IsActive(void)
{
	return m_bActive;
}

CConVar* CConVarConsole::GetVar(std::string szVarName)
{
	UINT iIndex = GetConVarIndexByName(szVarName);
	if (iIndex == -1)
		return nullptr;

	return m_vpConVars.at(iIndex);
}

float CConVarConsole::GetFloat(std::string szVarName)
{
	CConVar* pConVar = GetVar(szVarName);
	if (!pConVar)
		return 0.f;

	return pConVar->GetFloat();
}

int CConVarConsole::GetInt(std::string szVarName)
{
	CConVar* pConVar = GetVar(szVarName);
	if (!pConVar)
		return 0;

	return pConVar->GetInt();
}

void CConVarConsole::AddVar(std::string szVarName, std::string szVarDescription, bool active)
{
	AddVar(szVarName, szVarDescription, active ? 1.f : 0.f);
}

void CConVarConsole::AddVar(std::string szVarName, std::string szVarDescription, float flValue)
{
	if (szVarName.empty() || szVarDescription.empty())
		return;

	m_vpConVars.push_back(new CConVar(szVarName, szVarDescription, flValue));
}

void CConVarConsole::AddVar(std::string szVarName, std::string szVarDescription, int iValue)
{
	AddVar(szVarName, szVarDescription, float(iValue));
}

void CConVarConsole::Echo(const char* pszString, ...)
{
	va_list args;
	va_start(args, pszString);
	char szBuffer[256];
	vsprintf_s(szBuffer, pszString, args);
	va_end(args);

	m_vszOutput.push_back(szBuffer);
}

void CConVarConsole::HandleInput(void)
{
	if (GetAsyncKeyState(VK_DELETE) & 1)
		SetActive(!IsActive());

	if (m_bActive)
	{
		for (int iKey = 0; iKey < KEY_MAX; iKey++)
		{
			// Remove the last character inside the string
			if (IsKeyPressed(KEY_BACKSPACE))
			{
				std::size_t nLength = m_szCurrentString.length();
				if (nLength > 0)
				{
					m_szCurrentString.erase(nLength - 1);
					m_nCurrentPos--;
				}
			}

			// Push the current string into the output vector and set the currrent pos to 0
			if (IsKeyPressed(KEY_ENTER))
			{
				if (!m_szCurrentString.empty())
				{
					HandleCommand(m_szCurrentString.c_str());
					m_nCurrentPos = 0;
					m_szCurrentString.clear();
					break;
				}
			}

			// Handle input characters
			if (IsKeyPressed(iKey) && m_szCurrentString.length() <= 114)
			{
				// Check if the shift definition is needed
				if (IsKeyDown(KEY_SHIFT))
				{
					m_szCurrentString.append(m_KeyStroke[iKey].m_szShiftDefinition);
					m_nCurrentPos++;
				} // Check if the alt definition is needed
				else if (IsKeyDown(KEY_ALTGR))
				{
					m_szCurrentString.append(m_KeyStroke[iKey].m_szAltDefinition);
					m_nCurrentPos++;
				}
				else
				{ // Otherwise use the normal definition
					m_szCurrentString.append(m_KeyStroke[iKey].m_szDefinition);
					m_nCurrentPos++;
				}
			}
		}
	}
}
#define DM gDrawManager
void CConVarConsole::Render(void)
{
	if (!IsActive())
		return;

	int x = CONSOLE_X;
	int y = CONSOLE_Y;
	int w = CONSOLE_WIDTH;
	int h = CONSOLE_HEIGHT;

	// Background
	//Direct3D9::pRender->RectOutlined(x, y, w, h, D3DCOLOR_ARGB(230, 40, 40, 40), D3DCOLOR_ARGB(255, 0, 0, 0), 1);
	DM.DrawRect(x, y, w, h, Color(40, 40, 40, 230));
	x += 15;
	y += 2;
	// Console title
	//Direct3D9::pRender->String(x, y, D3DCOLOR_ARGB(255, 255, 0, 0), Direct3D9::GetFont("Verdana"), "Hack Console");
	DM.DrawString(false, false, x, y, Color(255, 0, 0, 255), "pHook console");
	x -= 10;
	y += 20;
	w -= 10;
	h -= 52;
	// History background
	//Direct3D9::pRender->RectOutlined(x, y, w, h, D3DCOLOR_ARGB(230, 15, 15, 15), D3DCOLOR_ARGB(255, 0, 0, 0), 1);
	DM.DrawRect(x, y, w, h, Color(15,15,15,240));
	x += 5;
	y += 5;
	// History
	int iHistoryY = y;
	if (m_vszOutput.size() < CONSOLE_MAX ? true : false)
	{
		for (UINT i = 0; i < m_vszOutput.size(); i++)
		{
			iHistoryY += 2;
			//Direct3D9::pRender->String(x, iHistoryY + (i * 12), D3DCOLOR_ARGB(255, 255, 255, 255), Direct3D9::GetFont("Verdana"), m_vszOutput.at(i).c_str());
			DM.DrawString(false, false, x, iHistoryY + (i * 18), Color(255, 255, 255, 255), m_vszOutput.at(i).c_str());
		}
	}
	else
	{
		for (UINT i = 0; i < CONSOLE_MAX; i++)
		{
			iHistoryY += 2;
			//Direct3D9::pRender->String(x, iHistoryY + (i * 12), D3DCOLOR_ARGB(255, 255, 255, 255), Direct3D9::GetFont("Verdana"), m_vszOutput.at(i + m_vszOutput.size() - CONSOLE_MAX).c_str());
			DM.DrawString(false, false, x, iHistoryY + (i * 18), Color(255, 255, 255, 255), m_vszOutput.at(i + m_vszOutput.size() - CONSOLE_MAX).c_str());

		}
	}
	x -= 5;
	y += 850; // CONSOLE_HEIGHT - 50
	h = 20;
	// Input background
	//Direct3D9::pRender->RectOutlined(x, y, w, h, D3DCOLOR_ARGB(230, 15, 15, 15), D3DCOLOR_ARGB(255, 0, 0, 0), 1);
	//660
	DM.DrawRect(x, y, w, h, Color(15, 15, 15, 230));
	x += 5;
	y += 3;
	// Input
	//Direct3D9::pRender->String(x, y, D3DCOLOR_ARGB(255, 255, 255, 255), Direct3D9::GetFont("Verdana"), m_szCurrentString.c_str());
	DM.DrawString(false, false, x, y, Color(255, 255, 255, 255), m_szCurrentString.c_str());
}

void CConVarConsole::SetActive(bool active)
{
	m_bActive = active;
}

Console::CConVarConsole* g_pCVarConsole = new Console::CConVarConsole();