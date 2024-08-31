typedef void*(__thiscall* pt_t)(ipanel* pthis, unsigned int, bool, bool);

floatie* fdmg_floaties[512];

namespace utils
{
	void addfloatie(int ix, int iy, std::string scontent)
	{
		for (int ifloatie_index = 0; ifloatie_index < 512; ifloatie_index++)
		{
			if (fdmg_floaties[ifloatie_index] == NULL)
			{
				fdmg_floaties[ifloatie_index] = new floatie(ix, iy, scontent);
				break;
			}
		}
	}
}

namespace hooks
{
	pt_t opt;
	dword dwpt;

	void fstc pt(ipanel* pthis, void* pedx, unsigned int ivguipanel, bool bforce_rp, bool ballow_force)
	{
		opt(pthis, ivguipanel, bforce_rp, ballow_force);

		if (strcmp(g::ivguipanel->get_name(ivguipanel), /*MatSystemTopPanel*/XorStr<0x98, 18, 0xB3B783C9>("\xD5\xF8\xEE\xC8\xE5\xEE\xEA\xFA\xCD\xF5\xCD\xD3\xF4\xC4\xC8\xC2\xC4" + 0xB3B783C9).s) == 0)
		{
			ui::update();
			if (!g::ivengine->in_game())
				return;

			int iscrnw = 1920;
			int iscrnh = 1080; 

			g::ivengine->get_scrnsize(iscrnw, iscrnh);

			for (int ifloatie_index = 0; ifloatie_index < 512; ifloatie_index++)
			{
				if (fdmg_floaties[ifloatie_index] != NULL)
				{
					fdmg_floaties[ifloatie_index]->update();
					if (fdmg_floaties[ifloatie_index]->alpha <= 5)
					{
						fdmg_floaties[ifloatie_index] = NULL;
					}
				}
			}

			for (int ient_index = 0; ient_index <= g::ientlist->iget_highest_index(); ient_index++)
			{
				icliententity* pselected_entity = g::ientlist->pget_cliententity(ient_index);
				icliententity* pme = g::ientlist->pget_cliententity(g::ivengine->get_me());
				
				if (pselected_entity && pme)
				{
					trace_t tresults;

					if (pselected_entity->iget_hp() > 0)
					{
						vector vworld = pselected_entity->vget_pos();
						vworld = vworld + vector(0, 0, 40);
						vector vscreen = math::to_screen(vworld);

						if (vscreen != vector(0.f, 0.f, 0.f))
						{
							if (pselected_entity->iget_team() != pme->iget_team())
							{
								if (data::iesp == 1)
								{
									g::ivguisurface->set_color(color(18, 122, 204, 255));
									utils::drawtxt(vscreen.x + 15, vscreen.y, color(18, 122, 204, 255), std::to_string(pselected_entity->iget_hp()), 6);
								}

								if (data::itracers == 1)
								{
									int iwidth, iheight;
									g::ivengine->get_scrnsize(iwidth, iheight);
									g::ivguisurface->fill_line(vscreen.x, vscreen.y, iwidth / 2, iheight / 2);
								}
							}
							else
							{
								if (data::iesp == 1)
								{
									g::ivguisurface->set_color(color(255, 255, 255, 255));
									utils::drawtxt(vscreen.x + 15, vscreen.y, color(255, 255, 255, 255), std::to_string(pselected_entity->iget_hp()), 6);
								}
							}

							if (data::iesp == 1)
							{
								g::ivguisurface->fill_orect(vscreen.x, vscreen.y, vscreen.x + 10, vscreen.y + 10);
							}
						}
					}
				}
			}
		}
	}
}