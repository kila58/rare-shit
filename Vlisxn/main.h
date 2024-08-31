#pragma once

#define WIN32_LEAN_AND_MEAN
#pragma warning( disable : 4305 )
#pragma warning( disable : 4244 )

#include <Windows.h>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>

template<typename t> t getvFunc( void *table, int index ) {
	return (*(t **)table)[ index ];
}

#include "vmt.h"
#include "vector.h"
#include "color.h"

#include "Vars.h"
Vars *vars = new Vars();

#include "sdk.h"
#include "md5.h"

#include "engine.h"
Engine *engine = new Engine();

#include "netvars.h"
Netvars *netvars = new Netvars();

#include "move.h"
GameMovement *gameMovement = new GameMovement();

#include "entity.h"

#include "cheat.h"
Cheat *cheat = new Cheat();

#include "drawing.h"
Drawing *draw = new Drawing();

#include "menu.h"
Menu *menu = new Menu();

// garbage
#include "esp.h"
#include "aimbot.h"