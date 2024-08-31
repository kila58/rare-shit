#ifndef _l_lhkhelpdrv_h_
#define _l_lhkhelpdrv_h_

#include "winlite.h"
#include <WinIoCtl.h>

/*FILE_DEVICE_LHK I/O*/
#define FILE_DEVICE_LHK 64719
#define IOCTL_AUTH CTL_CODE(FILE_DEVICE_LHK, 2050, METHOD_NEITHER, FILE_READ_DATA|FILE_WRITE_DATA)
/*FILE_DEVICE_LHK I/O*/

void l_lhkhelpdrv_register(lua_State *l);
void l_lhkhelpdrv_globals(lua_State *l);

LUA_FUNC(DrvOpen);
LUA_FUNC(DrvClose);
LUA_FUNC(DrvAuth);
LUA_FUNC(DrvEmulateKeyUp);
LUA_FUNC(DrvEmulateKeyDown);
LUA_FUNC(DrvEmulateMouseMove);
LUA_FUNC(DrvEmulateMouseUp);
LUA_FUNC(DrvEmulateMouseDown);

#endif
