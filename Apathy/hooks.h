#pragma once

#include "Entrypoint.h"


typedef void (__thiscall* PaintTraverseFn)(void*,int,bool,bool);


extern PaintTraverseFn PaintTraverse;

bool HookedCreateMove(float,UserCmd*);
void HookedRunCommand(Entity*,UserCmd*,void*);
void HookedPaintTraverse(int,bool,bool);