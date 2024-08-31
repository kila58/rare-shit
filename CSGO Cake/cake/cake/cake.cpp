#include "package.h"

class cake_dmg_listener : public igameeventlistener
{
	void fire_gameevent(igameevent* ievent)
	{
		int idmg = (int)ievent->fget(/*dmg_health*/XorStr<0xAD, 11, 0x2B8756D8>("\xC9\xC3\xC8\xEF\xD9\xD7\xD2\xD8\xC1\xDE" + 0x2B8756D8).s);
		icliententity* plocal = g::ientlist->pget_cliententity(g::ivengine->get_me());
		icliententity* pattacked = g::ientlist->pget_cliententity(g::ivengine->iget_player_by_id(ievent->iget(/*userid*/XorStr<0xA0, 7, 0xEDF8461E>("\xD5\xD2\xC7\xD1\xCD\xC1" + 0xEDF8461E).s)));
		
		if (plocal == g::ientlist->pget_cliententity(g::ivengine->iget_player_by_id(ievent->iget(/*attacker*/XorStr<0x7B, 9, 0x007BBA89>("\x1A\x08\x09\x1F\x1C\xEB\xE4\xF0" + 0x007BBA89).s))))
		{
			vector vworld = pattacked->vget_pos() + vector((int)(rand() % 10), (int)(rand() % 10), 40);
			vector vscreen = math::to_screen(vworld);

			if (vscreen != vector(0.f, 0.f, 0.f))
			{
				if (data::ifloaties == 1)
				{
					utils::addfloatie(vscreen.x, vscreen.y, std::to_string(idmg));
				}
			}
		}
	}
	int iget_debugid()
	{
		return 42;
	}
} cdmg;

void load()
{
	g::iengine = utils::icap_factory(/*engine.dll*/XorStr<0xFA, 11, 0x24AAC5B4>("\x9F\x95\x9B\x94\x90\x9A\x2E\x65\x6E\x6F" + 0x24AAC5B4).s);
	g::iclient = utils::icap_factory(/*client.dll*/XorStr<0x9B, 11, 0x1FC73DBA>("\xF8\xF0\xF4\xFB\xF1\xD4\x8F\xC6\xCF\xC8" + 0x1FC73DBA).s);
	g::ivgui2 = utils::icap_factory(/*vgui2.dll*/XorStr<0xAD, 10, 0x5D6CC3AC>("\xDB\xC9\xDA\xD9\x83\x9C\xD7\xD8\xD9" + 0x5D6CC3AC).s);
	g::imatsurface = utils::icap_factory(/*vguimatsurface.dll*/XorStr<0xB7, 19, 0x9432223E>("\xC1\xDF\xCC\xD3\xD6\xDD\xC9\xCD\xCA\xB2\xA7\xA3\xA0\xA1\xEB\xA2\xAB\xA4" + 0x9432223E).s);
	g::ivstd = utils::icap_factory(/*vstdlib.dll*/XorStr<0xB8, 12, 0x948A97DA>("\xCE\xCA\xCE\xDF\xD0\xD4\xDC\x91\xA4\xAD\xAE" + 0x948A97DA).s);

	g::ivguipanel = (ipanel*)g::ivgui2(/*VGUI_Panel009*/XorStr<0xBA, 14, 0xBBE5195A>("\xEC\xFC\xE9\xF4\xE1\xEF\xA1\xAF\xA7\xAF\xF4\xF5\xFF" + 0xBBE5195A).s, NULL);
	g::ivguisurface = (isurface*)utils::pcap_interface(g::imatsurface, /*VGUI_Surface*/XorStr<0x8E, 13, 0x6B68CC76>("\xD8\xC8\xC5\xD8\xCD\xC0\xE1\xE7\xF0\xF6\xFB\xFC" + 0x6B68CC76).s);
	g::ivengine = (ivengineclient*)utils::pcap_interface(g::iengine, /*VEngineClient*/XorStr<0xFF, 14, 0x385D3F29>("\xA9\x45\x6F\x65\x6A\x6A\x60\x45\x6B\x61\x6C\x64\x7F" + 0x385D3F29).s);
	g::ientlist = (icliententitylist*)utils::pcap_interface(g::iclient, /*VClientEntityList*/XorStr<0xFA, 18, 0xC9AC86BE>("\xAC\xB8\x90\x94\x9B\x91\x74\x44\x6C\x77\x6D\x71\x7F\x4B\x61\x7A\x7E" + 0xC9AC86BE).s);
	g::ilistener = (igameeventlistener*)utils::pcap_interfacea(g::iengine, /*GAMEEVENTSMANAGER002*/XorStr<0x1D, 21, 0x1268D30B>("\x5A\x5F\x52\x65\x64\x74\x66\x6A\x71\x75\x6A\x69\x67\x6B\x6C\x69\x7F\x1E\x1F\x02" + 0x1268D30B).s);
	g::itrace = (ienginetrace*)utils::pcap_interface(g::iengine, /*EngineTraceClient*/XorStr<0xBC, 18, 0x81927C72>("\xF9\xD3\xD9\xD6\xAE\xA4\x96\xB1\xA5\xA6\xA3\x84\xA4\xA0\xAF\xA5\xB8" + 0x81927C72).s);
	debug::print = (msg)(GetProcAddress(GetModuleHandleA(/*tier0.dll*/XorStr<0x0F, 10, 0xF814572B>("\x7B\x79\x74\x60\x23\x3A\x71\x7A\x7B" + 0xF814572B).s), /*Msg*/XorStr<0xBB, 4, 0x241AD208>("\xF6\xCF\xDA" + 0x241AD208).s));
	void* clientmode = *(void**)((dword)GetModuleHandleA(/*client.dll*/XorStr<0x8A, 11, 0x09C5ECAC>("\xE9\xE7\xE5\xE8\xE0\xFB\xBE\xF5\xFE\xFF" + 0x09C5ECAC).s) + (dword)0x4AA7B8C);

	g::vpanel = new fisherman();
	hooks::opt = (pt_t)g::vpanel->dwhook((DWORD**)g::ivguipanel, (dword)hooks::pt, 41);
	
	Sleep(1);

	g::vclientmode = new fisherman();
	g::vclientmode->dwhook((dword**)clientmode, (dword)hooks::createmove, 24);

	g::ilistener->badd_listener(&cdmg, /*player_hurt*/XorStr<0x65, 12, 0xF59FF41E>("\x15\x0A\x06\x11\x0C\x18\x34\x04\x18\x1C\x1B" + 0xF59FF41E).s, false);

	debug::print(/*.cake: welcome\n*/XorStr<0xD4, 16, 0x459DEEFC>("\xFA\xB6\xB7\xBC\xBD\xE3\xFA\xAC\xB9\xB1\xBD\xB0\x8D\x84\xE8" + 0x459DEEFC).s);
	debug::print(/*.cake: auth failed. either it isn't active or i am far away from home ;_;\n*/XorStr<0x7E, 75, 0x798871E2>("\x50\x1C\xE1\xEA\xE7\xB9\xA4\xE4\xF3\xF3\xE0\xA9\xEC\xEA\xE5\xE1\xEB\xEB\xBE\xB1\xF7\xFA\xE0\xFD\xF3\xE5\xB8\xF0\xEE\xBB\xF5\xEE\xF0\xB8\xD4\x81\xC3\xC0\xD0\xCC\xD0\xC2\x88\xC6\xD8\x8B\xC5\x8D\xCF\xC2\x90\xD7\xD3\xC1\x94\xD4\xC1\xD6\xC1\x99\xDC\xC9\xD3\xD0\x9E\xD7\xAF\xAC\xA7\xE3\xFF\x9A\xFD\xCD" + 0x798871E2).s);
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD lreason, LPVOID lreserved)
{
	if (lreason == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)load, hinst, 0, NULL);
	}
	return true;
}