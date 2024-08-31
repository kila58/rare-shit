
class PRotator;
class Spreadz;
class CEntList;
class CTrigger;
class CGlobalVarsBase;
class CInput;
class CHLClient;
class EngineClient;
class IPanel;
class CPrediction;
class ISurface;
class CNetChannelInfo;
class CVMTHookManager;
class CViewSetup;
class IEngineTrace;
class IVModelInfo;
class CPlayerVariables;
class CDrawManager;
class CControlVariables;
class ClientHook;
class CColorManager;
class CFileManager;
class CBaseAPI;
class CPlayerESP;
class CMenu;
class COptions;
class CEnable;

namespace ArgonLXFramework
{
	class  ArgonLX
	{
	public:
		ArgonLX::ArgonLX();
	public:
		CEntList*              pEntList;
		CGlobalVarsBase*       pGlobals;
		CInput*                pInput;
		CHLClient*             pClient;
		EngineClient*          pEngine;
		IPanel*                pPanel;
		CPrediction*           pPrediction;
		ISurface*              pSurface;
		CNetChannelInfo*       pNet;
		CVMTHookManager*       pPanelHook;
		CViewSetup*            pViewSetup;
		IEngineTrace*          pEngineTrace;
		IVModelInfo*           pModelInfo;

	public:
		PRotator*				PAim;
		Spreadz*               PSpreadz;
		CTrigger*               PTrigger;
		CPlayerVariables*       pPlayerVariables;
		CDrawManager*           pDrawManager;
		CControlVariables*      pCvar;
		ClientHook*             pClientHook;
		CColorManager*          pColorManager;
		CFileManager*           pFileManager;
		CBaseAPI*               pBaseAPI;
		CEnable*                pEnable;
		CMenu*                  pMenu;
		COptions*               pOptions;
		CPlayerESP*             pPlayerESP;
	};
};

extern	ArgonLXFramework::ArgonLX ALX;

