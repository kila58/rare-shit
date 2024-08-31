#include "Netvardump.h"

CNetVarDump gNetVarDump;
CLog gLog;
void CNetVarDump::DumpTable(RecvTable* table, int level)
{
	if (!table)
		return;
	char buffer[1024];
	sprintf(buffer, "");
	for (int j = 0; j < level; j++)
	{
		sprintf(buffer, "%s-", buffer);
	}
	sprintf(buffer, "%s%s", buffer, table->GetName());
	gLog.WriteLog(buffer);
	level += 2;
	for (int i = 0; i < table->GetNumProps(); ++i)
	{
		RecvProp *prop = table->GetProp(i);
		if (!prop)
			continue;
		if (isdigit(prop->GetName()[0]))
			continue;
		if (prop->GetDataTable())
		{
			DumpTable(prop->GetDataTable(), level + 1);
		}
		sprintf(buffer, "");
		for (int i = 0; i < level; i++)
		{
			sprintf(buffer, "%s-", buffer);
		}
		sprintf(buffer, "%s|%s : 0x%x", buffer, prop->GetName(), prop->GetOffset());
		gLog.WriteLog(buffer);
	}
	if (level == 2)
		gLog.WriteLog("");
}