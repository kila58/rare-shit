#include "SDK.h"
#include "Panels.h"
#include "CDrawManager.h"
#include "VMT Hook.h"
#include "CGlobalVars.h"
#include "Player ESP.h"
#include "Player Manager.h"
#include "Color Manager.h"
#include "PaintTraverse.h"
#include "Menu.h"

PaintTraverseFn OriginalPaintTraverse;

inline int rand_range(int min, int max)
{
	return rand() % (max - min + 1) + min;
}


CVMTHookManager* g_pPanelHook;


