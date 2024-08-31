

#ifndef _CVMTHOOK_H_
#define _CVMTHOOK_H_
//===================================================================================
#include <Windows.h>
//===================================================================================
class fisherman
{
public:
	dword dwhook(dword** ppclass, dword dwnewfunc, int ivfunc)
	{
		dword** ppvtable = ppclass;
		dword* poldvtable = *ppclass;
		int ivmtsize = iget_count(*ppclass);
		dword* pnewvmt = new dword[ivmtsize];
		memcpy(pnewvmt, poldvtable, sizeof(dword) * ivmtsize);
		*ppclass = pnewvmt;

		if (pnewvmt && poldvtable && ivfunc <= ivmtsize && ivfunc >= 0)
		{
			pnewvmt[ivfunc] = dwnewfunc;
			return poldvtable[ivfunc];
		}

		return 0;
	}
private:
	int iget_count(dword* pvmt)
	{
		int icount;
		for (icount = 0; pvmt[icount]; icount++)
		{
			if (((FARPROC)pvmt[icount]) == NULL)
			{
				break;
			}
		}
		return icount;
	}
	//PDWORD*    m_ppdwClassBase;
	//PDWORD    m_pdwNewVMT, m_pdwOldVMT;
	int   m_dwVMTSize;
};
//===================================================================================
#endif