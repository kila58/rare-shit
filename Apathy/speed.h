#include "client.h"
#include "Menu.h"

Client cl;

void CL_Speed(void* baseptr)
{
	static int speed = 0;

	if (GetAsyncKeyState('B') && speed <= variables::Misc::pSpeed)
	{
		*((byte*)baseptr + 0x4) -= 0x5;
		*((byte*)baseptr - 0x1) = 0;
		speed++;
	}
	else
	{
		*((byte*)baseptr - 0x1) = 1;
		speed = 0;
	}
}