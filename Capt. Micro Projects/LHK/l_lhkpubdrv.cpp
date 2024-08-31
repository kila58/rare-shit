#include "l_lhkpubdrv.h"

HANDLE hkLHK = INVALID_HANDLE_VALUE;

void l_lhkpubdrv_register(lua_State *l)
{
	hkLHK = INVALID_HANDLE_VALUE;

	LUA_REG(l, DrvOpen);
	LUA_REG(l, DrvClose);

	LUA_REG(l, DrvSetProc);
	LUA_REG(l, DrvUnsetProc);

	LUA_REG(l, DrvReadByte);
	LUA_REG(l, DrvReadShort);
	LUA_REG(l, DrvReadInt);
	LUA_REG(l, DrvReadFloat);

	LUA_REG(l, DrvWriteByte);
	LUA_REG(l, DrvWriteShort);
	LUA_REG(l, DrvWriteInt);
	LUA_REG(l, DrvWriteFloat);

	LUA_REG(l, DrvSigScan);
	LUA_REG(l, DrvPopImageData);
}

void l_lhkpubdrv_globals(lua_State *l)
{

}

void l_lhkpubdrv_unregister(lua_State *l)
{
	
}

LUA_FUNC(DrvOpen)
{
	hkLHK = CreateFile("\\\\.\\kLHK", 
		0, FILE_SHARE_READ | FILE_SHARE_WRITE,
		0, OPEN_EXISTING, 0, 0);
	if (hkLHK == INVALID_HANDLE_VALUE)
		MessageBoxA(0,
		"Failed to open kLHK!\nDriver extension disabled!",
		"LHK Error!", MB_OK);

	lua_pushboolean(l, (hkLHK == INVALID_HANDLE_VALUE) ? 0 : 1);
	return 1;
}

LUA_FUNC(DrvClose)
{
	CloseHandle(hkLHK);
	return 0;
}

LUA_FUNC(DrvSetProc)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	char *procname = (char*)lua_tostring(l, 1);
	DWORD success = FALSE, dwBytesRead = 0;
	
	DeviceIoControl(hkLHK, IOCTL_SET_PROC,
		procname, lstrlenA(procname),
		&success, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushboolean(l, success);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvUnsetProc)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	DWORD success = FALSE, dwBytesRead = 0;

	DeviceIoControl(hkLHK, IOCTL_SET_PROC,
		0, 0,
		&success, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushboolean(l, success);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvReadByte)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	DWORD dwAddr = (DWORD)lua_tointeger(l, 1);
	DWORD readvalue = 0, dwBytesRead = 0;

	DeviceIoControl(hkLHK, IOCTL_READ_DWORD,
		0, 0,
		&readvalue, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushinteger(l, readvalue & 0xFF);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvReadShort)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	DWORD dwAddr = (DWORD)lua_tointeger(l, 1);
	DWORD readvalue = 0, dwBytesRead = 0;

	DeviceIoControl(hkLHK, IOCTL_READ_DWORD,
		&dwAddr, 4,
		&readvalue, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushinteger(l, readvalue & 0xFFFF);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvReadInt)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	DWORD dwAddr = (DWORD)lua_tointeger(l, 1);
	DWORD readvalue = 0, dwBytesRead = 0;

	DeviceIoControl(hkLHK, IOCTL_READ_DWORD,
		&dwAddr, 4,
		&readvalue, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushinteger(l, readvalue);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvReadFloat)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	DWORD dwAddr = (DWORD)lua_tointeger(l, 1);
	DWORD readvalue = 0, dwBytesRead = 0;

	DeviceIoControl(hkLHK, IOCTL_READ_DWORD,
		&dwAddr, 4,
		&readvalue, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		FLOAT number = *(FLOAT*)&readvalue;
		lua_pushnumber(l, number);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvWriteByte)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	DWORD dwAddr = (DWORD)lua_tointeger(l, 1);
	DWORD dwValue = (DWORD)lua_tointeger(l, 2);
	DWORD success = FALSE, dwBytesRead = 0;
	dwValue &= 0xFF;

	LARGE_INTEGER writedata;
	writedata.u.LowPart = dwAddr;
	writedata.u.HighPart = dwValue;

	DeviceIoControl(hkLHK, IOCTL_WRITE_DWORD,
		&writedata, sizeof(LARGE_INTEGER),
		&success, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushboolean(l, success);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvWriteShort)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	DWORD dwAddr = (DWORD)lua_tointeger(l, 1);
	DWORD dwValue = (DWORD)lua_tointeger(l, 2);
	DWORD success = FALSE, dwBytesRead = 0;
	dwValue &= 0xFFFF;

	LARGE_INTEGER writedata;
	writedata.u.LowPart = dwAddr;
	writedata.u.HighPart = dwValue;

	DeviceIoControl(hkLHK, IOCTL_WRITE_DWORD,
		&writedata, sizeof(LARGE_INTEGER),
		&success, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushboolean(l, success);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvWriteInt)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	DWORD dwAddr = (DWORD)lua_tointeger(l, 1);
	DWORD dwValue = (DWORD)lua_tointeger(l, 2);
	DWORD success = FALSE, dwBytesRead = 0;

	LARGE_INTEGER writedata;
	writedata.u.LowPart = dwAddr;
	writedata.u.HighPart = dwValue;

	DeviceIoControl(hkLHK, IOCTL_WRITE_DWORD,
		&writedata, sizeof(LARGE_INTEGER),
		&success, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushboolean(l, success);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvWriteFloat)
{
	if (hkLHK == INVALID_HANDLE_VALUE) return 0;

	DWORD dwAddr = (DWORD)lua_tointeger(l, 1);
	FLOAT dwValue = (FLOAT)lua_tonumber(l, 2);
	DWORD success = FALSE, dwBytesRead = 0;

	LARGE_INTEGER writedata;
	writedata.u.LowPart = dwAddr;
	writedata.u.HighPart = *(DWORD*)&dwValue;

	DeviceIoControl(hkLHK, IOCTL_WRITE_DWORD,
		&writedata, sizeof(LARGE_INTEGER),
		&success, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushboolean(l, success);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvSigScan)
{
	DWORD dwAddress = (DWORD)lua_tostring(l, 1);
	DWORD dwMaxScan = (DWORD)lua_tostring(l, 2);
	UCHAR *bSig = (UCHAR*)lua_tostring(l, 3);
	DWORD dwSigLen = (DWORD)lua_tointeger(l, 4);

	DrvSigScanData scandata;
	scandata.dwStartAddress = dwAddress;
	scandata.dwMaxScanLength = dwMaxScan;
	scandata.dwSignatureLength = (dwSigLen >= DrvMaxSigLength) ? DrvMaxSigLength-1 : dwSigLen;
	memcpy(scandata.bSignature, bSig, scandata.dwSignatureLength);
	DWORD dwScanResult = 0, dwBytesRead = 0;

	DeviceIoControl(hkLHK, IOCTL_SIGSCAN,
		&scandata, sizeof(DrvSigScanData),
		&dwScanResult, 4,
		&dwBytesRead, 0);
	if (dwBytesRead == 4)
	{
		lua_pushinteger(l, dwScanResult);
		return 1;
	}

	lua_pushnil(l);
	return 1;
}

LUA_FUNC(DrvPopImageData)
{
	DrvImageList imageinfo;
	DWORD dwBytesRead = 0;
	
	DeviceIoControl(hkLHK, IOCTL_POPIMAGEDATA,
		0, 0,
		&imageinfo, sizeof(DrvImageList),
		&dwBytesRead, 0);
	if (dwBytesRead == sizeof(DrvImageList))
	{
		lua_pushstring(l, imageinfo.FullImageName);
		lua_pushinteger(l, (DWORD)imageinfo.ProcessId);
		lua_pushinteger(l, (DWORD)imageinfo.ImageInfo.ImageBase);
		lua_pushinteger(l, imageinfo.ImageInfo.ImageSize);
		lua_pushinteger(l, imageinfo.ImageInfo.ImageSelector);
		lua_pushinteger(l, imageinfo.ImageInfo.ImageSectionNumber);
		lua_pushinteger(l, imageinfo.ImageInfo.ImageAddressingMode);
		lua_pushinteger(l, imageinfo.ImageInfo.ImageMappedToAllPids);
		lua_pushinteger(l, imageinfo.ImageInfo.SystemModeImage);
		lua_pushinteger(l, imageinfo.ImageInfo.Reserved);
		return 10;
	}

	lua_pushnil(l);
	return 1;
}