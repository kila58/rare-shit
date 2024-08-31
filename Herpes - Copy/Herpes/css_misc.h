/*******************************************************
KELSE
********************************************************/
void Nosky()
{
}

int speedCmd = 2;

void SpeedHack(void *__ebp, int factor) {
	byte *sendPacket = (byte *) (*(char **) __ebp - 0x1);
	DWORD *retnAddr = (DWORD *) (*(char **) __ebp + 0x1);

	if (speedCmd > 1)
	{
		speedCmd -= 1;
		*sendPacket = 0;
		*retnAddr -= 0x5;
	}
	else
	{
		speedCmd = factor;
		*sendPacket = 1;
	}
}