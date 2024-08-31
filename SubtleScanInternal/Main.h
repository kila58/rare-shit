#pragma once
#include "SDK.h"
#define M_RADPI 57.295779513082
using namespace std;
//Include other shit down here

#define MakePtr(cast, ptr, addValue) (cast)( (DWORD)(ptr) + (DWORD)(addValue))
typedef void(__thiscall* PTfn)(void*, unsigned int, bool, bool);
typedef void(__stdcall* CreateMoveFn)(int, float, bool);
typedef void(__thiscall* FrameStageNotifyFn)(void*, ClientFrameStage_t);
typedef void* (__stdcall* DrawModelExecuteFn)(IMatRenderContext * ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
#include "Interfacem.h"
#include "VMT.h"
#include "PaintTraverse.h"
#include "CDrawManager.h"
#include "Menu.h"
#include "CVARS.h"
#include "CreateMove.h"
#include "CAimbot.h"
#include "Netvardump.h"
#include "netvars.h"
#include "Console.h"
#include "D3DModels.h"
#include "Random.h"
class CLog
{
public:
	void WriteLog(const char* string)
	{
		FILE* file = fopen("C:\\LOGFILE.txt", "a");
		fprintf(file, "%s\n", string);
		fclose(file);
	}
	char* xstring(DWORD a, ...)
	{

	}
};
extern CLog gLog;