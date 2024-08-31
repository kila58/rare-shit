#include "Entrypoint.h"

void _FakeLag(void *baseptr){
	byte *sendPacket = (byte *)(*(char **)baseptr - 0x1);

	static int queued = 0;

	if (variables::Misc::Fakelag)

		if (queued >= 0)
		{
			queued++;

			// queue up 15 cmds
			if ((queued < 15) /*&& !backup_firedLastTick*/)
			{
				*sendPacket = 1;
			}
			else
			{
				// queue up cmd*
				*sendPacket = 0;
			}
		}
		else
		{
			// queue up cmd
			*sendPacket = 1;
		}

	// finalize warp and reset
	if ((queued == 15) /*|| backup_firedLastTick*/)
	{
		queued = 0;
	}
};

