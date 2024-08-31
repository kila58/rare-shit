#include "hooks.h"


UserCmd *__stdcall HookedGetUserCmd(int sequence_number)
{
	static UserCmd* pCommands = *(UserCmd **)((DWORD)cl.input + 0xC4);
	UserCmd *cmd = &pCommands[sequence_number % 90];
	if (cmd != NULL)
	{
		cmd->seed = PseudoRandom(cmd->index = 142) & 0x7FFFFFFF;
	}
	return cmd;
}