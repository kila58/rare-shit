#include "client.h"
#include "Menu.h"

void Bhop(UserCmd* cmd)
{
	if (variables::Misc::BunnyHop)
	if (!(cl.me->m_fFlags() & 1))
		cmd->buttons &= ~2;
}






