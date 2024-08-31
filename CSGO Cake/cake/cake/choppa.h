namespace choppa
{
	bool DataCompare(const BYTE* pData, const BYTE* bMask, const char* pszMask)
	{
		for (; *pszMask; ++pszMask, ++pData, ++bMask)
			if (*pszMask == 'x' && *pData != *bMask)
				return false;
		return (*pszMask) == 0;
	}

	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * pszMask)
	{
		for (DWORD i = 0; i < dwLen; i++)
			if (DataCompare((BYTE*)(dwAddress + i), bMask, pszMask))
				return (DWORD)(dwAddress + i);

		return 0;
	}
	void traceline(const vector& vecAbsStart, const vector& vecAbsEnd, unsigned int mask, const icliententity* ignore, int collisionGroup, trace_t* ptr)
	{
		typedef int(__fastcall* TraceLineFn)(const vector&, const vector&, unsigned int, const icliententity*, int, trace_t*);

		static TraceLineFn TraceLine = (TraceLineFn)FindPattern((DWORD)GetModuleHandleA(/*client.dll*/XorStr<0xBD, 11, 0x9F8DFE42>("\xDE\xD2\xD6\xA5\xAF\xB6\xED\xA0\xA9\xAA" + 0x9F8DFE42).s), 0x7FFFFFFF, (BYTE*)"\x55\x8B\xEC\x83\xE4\xF0\x83\xEC\x7C\x56\x52", "xxxxxxxxxxx");

		TraceLine(vecAbsStart, vecAbsEnd, mask, ignore, collisionGroup, ptr);
	}

	icliententity* pget_target(usercmd* cmd)
	{
		icliententity* pret = NULL;

		float fclosest = 64000;

		for (int ient_index = 0; ient_index < g::ientlist->iget_highest_index(); ient_index++)
		{
			icliententity* pme = g::ientlist->pget_cliententity(g::ivengine->get_me());
			icliententity* phim = g::ientlist->pget_cliententity(ient_index);

			if (phim && pme)
			{
				if (phim->iget_hp() > 0)
				{
					if (phim->iget_team() != pme->iget_team())
					{
						vector vhead_pos = phim->vget_pos() + vector(0, 0, 50);
						vector vmy_pos = pme->vget_pos() + vector(0, 0, 50);

						Ray_t ray;
						ray.Init(vmy_pos, vhead_pos);

						trace_t results;
						tracefilter filter;
						filter.pignore = pme;

						g::itrace->TraceRay(ray, 0x46004003, &filter, &results);

						if (results.m_pEnt && !results.allsolid)
						{
							if (results.m_pEnt->iget_hp() == phim->iget_hp())
							{
								if (results.fraction > 0.97f)
								{
									debug::print("hi\n");
								}
							}
						}
					}
				}
			}
		}

		return pret;
	}

	void aim_at(icliententity* ptarget, usercmd* cmd)
	{

	}

	void execute(usercmd* cmd)
	{
		//pget_target(cmd);
	}
}