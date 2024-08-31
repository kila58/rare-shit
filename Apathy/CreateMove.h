#include "hooks.h"
#include "Aimbot.h"
#include "speed.h"
#include "Bhop.h"



PaintTraverseFn PaintTraverse;


bool HookedCreateMove(float frametime, UserCmd* cmd)
{
	//cl.local = cl.engine->GetLocalPlayer();
	cl.me = cl.ents->GetEntity(cl.local);
	cl.wep = cl.ents->GetEntity(cl.me->Weapon(), true);
	void* baseptr;
	_asm MOV baseptr, EBP;
	baseptr = ***(void****)baseptr;
	CL_Speed(baseptr);
	cl.shootpos = cl.me->LocalOrigin() + cl.me->ViewOffset();
	DoMain(cmd);
	Bhop(cmd);
	cmd->ang.Clamp();
	return false;
}
