#include "l_lhkhelpdrv.h"

HANDLE hLhkHelpDrv = INVALID_HANDLE_VALUE;

void l_lhkhelpdrv_register(lua_State *l)
{
	hLhkHelpDrv = INVALID_HANDLE_VALUE;

	LUA_REG(l, DrvOpen);
	LUA_REG(l, DrvClose);
	LUA_REG(l, DrvAuth);
}

void l_lhkhelpdrv_globals(lua_State *l)
{
	
}

LUA_FUNC(DrvOpen)
{
	hLhkHelpDrv = CreateFile("\\\\.\\lhkHelpDrv", 
		0, FILE_SHARE_READ | FILE_SHARE_WRITE,
		0, OPEN_EXISTING, 0, 0);
	if (hLhkHelpDrv == INVALID_HANDLE_VALUE)
		MessageBoxA(0,
		"Failed to open lhkHelpDrv!\nDriver extensions disabled!",
		"LHK Error!", MB_OK);

	lua_pushboolean(l, (hLhkHelpDrv == INVALID_HANDLE_VALUE) ? 0 : 1);
	return 1;
}

LUA_FUNC(DrvClose)
{
	CloseHandle(hLhkHelpDrv);
	return 0;
}

LUA_FUNC(DrvAuth)
{
	ULONG uDrvAuthedUser = 0;
	DWORD dwBytesReturned = 0;

	char *authString = (char*)lua_tostring(l, 1);
	if (lstrlenA(authString) > 512) { lua_pushnil(l); return 1; }

	DeviceIoControl(hLhkHelpDrv,
		IOCTL_AUTH,
		authString, lstrlenA(authString),
		&uDrvAuthedUser, 4,
		&dwBytesReturned, 0);

	if (uDrvAuthedUser == 0)
		MessageBoxA(0,
		"Failed to authorize user!\nlhkHelpDrv ioctl disabled!\nReload driver and retry authorization.",
		"LHK Error!", MB_OK);

	lua_pushinteger(l, (int)uDrvAuthedUser);
	return 1;
}
