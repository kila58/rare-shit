#pragma once
#include "Main.h"
class CCreateMove
{
public:
	void Invoke(CUserCmd* cmd,  BYTE &bSendPacket);
	void CHLInvoke(int);
	void X_SpreadFix(CUserCmd* pCmd);
	
};
extern CCreateMove gCreateMove;