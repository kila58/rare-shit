#include "CreateMove.h" // Base Header
#include "Player Manager.h" // gPlayers
#include "Control Variables.h" // gCvars
#include "Extra Functions.h"

CCreateMove gCreateMove;

void CCreateMove::Invoke()
{	
	CSetupPlayer __pLocalBaseEntity = gPlayers[me];

	if( __pLocalBaseEntity.BaseEnt() == NULL )
		return;
	

}