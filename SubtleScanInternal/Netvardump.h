#pragma once
#include "Main.h"
#ifndef NETVARDUMP
#define NETVARDUMP
class CNetVarDump
{
public:
	void DumpTable(RecvTable* table, int level);
};
extern CNetVarDump gNetVarDump;
#endif