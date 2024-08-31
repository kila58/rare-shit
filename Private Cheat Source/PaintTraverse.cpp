#include "PaintTraverse.h" // Base Header

#include "Control Variables.h" // gCvars
#include "Player ESP.h" // gPlayerESP
#include "Color Manager.h" // gColorManager
#include "Player Manager.h" // gPlayers
#include "Panels.h" // gScreenSize
#include "CDrawManager.h"
#include "Extra Functions.h"
#include "Menu.h"

#define WHITE            Color(255, 255, 255, 255)
#define RED                Color(255, 000, 000, 255)
#define GREEN            Color(000, 255, 000, 255)
#define BLUE            Color(000, 000, 255, 255) 
#define BLACK            Color(000, 000, 000, 255)
#define mBLACK            Color(100, 000, 000, 205)
#define PURPLE            Color(164, 44, 226, 255) 
#define GREY            Color(239, 255, 255, 255) 
#define YELLOW            Color(255, 255, 000, 255) 
#define ORANGE            Color(255, 153, 90, 255) 
#define CYAN            Color(0, 226, 255, 255) 

int CenterX = GetSystemMetrics(0) / 2 - 1;//Gets screen X resolution then cutting it in half to get the center.
int CenterY = GetSystemMetrics(1) / 2 - 1;//Gets screen Y resolution then cutting it in half to get the center.

int CenterX2 = GetSystemMetrics(0) / 2;//Gets screen X resolution then cutting it in half to get the center.
int CenterY2 = GetSystemMetrics(1) / 2;//Gets screen Y resolution then cutting it in half to get the center.

CPaintTraverse PaintTraverseClass;



void MagicCross()
{
	CSetupPlayer __pLocalBaseEntity = gPlayers[me];

	CBaseEntity* pLocalBaseEntity = __pLocalBaseEntity.BaseEnt();
	CBaseEntity* pLocal = ALX.pEntList->GetClientEntity(ALX.pEngine->GetLocalPlayer());

	INT Width, Height;
	ALX.pEngine->GetScreenSize(Width, Height);

	INT FixedWidth = Width - 5;
	INT FixedHeight = Height - 5;
	Vector Punch = pLocalBaseEntity->GetPunchAngle() * 9;
	ALX.pDrawManager->DrawString1(true, FixedWidth / 2 - Punch.y, FixedHeight / 2 + Punch.x, colWhite, "+");

}



void CPaintTraverse::Invoke()
{
	CSetupPlayer playerManagerObj = gPlayers[me];
	int playerTeam = playerManagerObj.GetTeam();

	if (GetAsyncKeyState(VK_F6) & 1)
	{
		ALX.pOptions->Panic = !ALX.pOptions->Panic;
	}

	if (!ALX.pOptions->Panic)
	{

		INT Width2, Height2;
		ALX.pEngine->GetScreenSize(Width2, Height2);

		for (int iIndex = 0; iIndex < ALX.pEntList->GetHighestEntityIndex(); iIndex++)
		{
			ALX.pPlayerESP->DrawPlayerESP(iIndex);
			ALX.pPlayerESP->DrawWorldESP(iIndex);


		}

		int centerx = ALX.pOptions->Radar_X;
		int centery = ALX.pOptions->Radar_Y;
		int size = ALX.pOptions->Radar_Size;
		size -= 10;

		if (ALX.pCvar->Radar)
		{
			ALX.pPlayerESP->DrawRadarBack();
			ALX.pMenu->MoveMenu(ALX.pOptions->Radar_X, ALX.pOptions->Radar_Y, 2 * size, 2 * size,1);
		}

		if (ALX.pCvar->Crosshair)
		{

			ALX.pDrawManager->FillRGBA(CenterX2 - 3, CenterY2, 6, 1, colWhite);//Red
			ALX.pDrawManager->FillRGBA(CenterX2, CenterY2 - 3, 1, 6, colWhite);
		}

		if (ALX.pCvar->Recoil)
		{
			MagicCross();
		}

	}
	
}