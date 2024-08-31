#pragma once
#include "SDK.h"
#include "IEngineTrace.h"
extern IBaseClientDLL *Client;
extern EngineClientNew *Engine;
extern IClientEntityList *ClientEntList;
extern CInputNew *Input;
extern CreateInterfaceFn					ClientFactory;
extern ISurfaceNew *Surface;
extern vgui::IPanel					*VPanel;
extern IStudioRender *StudioRender;
extern IVDebugOverlay *DebugOverlay;
extern IEngineTrace *Trace;
extern ICvar *Cvar;
extern IVModelInfo2 *ModelInfo;
extern CGlobalVarsBaseNew *Globals;
extern IVModelRender *ModelRender;
class CInterface
{
public:

	void* GetPointer(CreateInterfaceFn Factory, const char *pszInterface)
	{
		char szPossibleInterface[1024];
		void *m_pInterface = NULL;
		m_pInterface = (void*)Factory(szPossibleInterface, 0);
		if (m_pInterface)
			return m_pInterface;
		for (int i = 1; i < 100; i++)
		{
			if (i < 10)
				sprintf(szPossibleInterface, "%s00%i", pszInterface, i);
			if (i > 9)
				sprintf(szPossibleInterface, "%s0%i", pszInterface, i);
			m_pInterface = (void*)Factory(szPossibleInterface, 0);
			if (m_pInterface != NULL)
			{
				using namespace std;
				cout << "Found: " << szPossibleInterface << endl;
				break;
			}
		}
		return(m_pInterface);
	}

	void GetInterfaces();

};
extern CInterface intf;