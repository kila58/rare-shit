#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)	// Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)

namespace utils
{
	void sanitize_usercmd(usercmd* cmd)
	{
		if (cmd->vviewangles.x > 89.0f)
			cmd->vviewangles.x = 89.0f;

		if (cmd->vviewangles.x < -89.0f)
			cmd->vviewangles.x = -89.0f;

		while (cmd->vviewangles.y > 180)
			cmd->vviewangles.y -= 360;

		while (cmd->vviewangles.y < -180)
			cmd->vviewangles.x += 360;

		cmd->vviewangles.z = 0;
	}
}

namespace hooks
{
	bool bhooked_cm = false;
	bool balternator = false;
	bool balternator2 = false;
	int stdc createmove(float fsample, usercmd* cmd)
	{
		icliententity* pme = g::ientlist->pget_cliententity(g::ivengine->get_me());
		if (!g::ivengine->in_game() && pme)
			return 0;

		//if (fsample == 0.f)
		//{
			//utils::sanitize_usercmd(cmd);
			//return 0;
		//}

		//choppa::execute(cmd);

		if (data::iflicker == 1 && !(cmd->ibuttons & IN_ATTACK))
		{
			balternator = !balternator;

			if (balternator)
			{
				cmd->vviewangles = vector(80, cmd->vviewangles.y, 0.f);
			}
			else
			{
				cmd->vviewangles = vector(-80, cmd->vviewangles.y, 0.f);
			}
		}

		if (data::ijitter == 1 && !(cmd->ibuttons & IN_ATTACK))
		{
			balternator2 = !balternator2;
			if (balternator2)
			{
				cmd->vviewangles = vector(cmd->vviewangles.x, cmd->vviewangles.y + 180, 0);
				cmd->fforwardmove = -cmd->fforwardmove;
				cmd->fsidemove = -cmd->fsidemove;
			}
			else
			{
				cmd->vviewangles = vector(cmd->vviewangles.x, cmd->vviewangles.y, 0);
				cmd->fforwardmove = cmd->fforwardmove;
				cmd->fsidemove = cmd->fsidemove;
			}
		}

		if (data::ireverse == 1 && !(cmd->ibuttons & IN_ATTACK))
		{
			cmd->vviewangles = vector(cmd->vviewangles.x, cmd->vviewangles.y + 180, 0);
			cmd->fforwardmove = -cmd->fforwardmove;
			cmd->fsidemove = -cmd->fsidemove;
		}

		if (data::ibhop == 1)
		{
			if (cmd->ibuttons & IN_JUMP)
			{
				icliententity* pme = g::ientlist->pget_cliententity(g::ivengine->get_me());
				if (!(pme->iget_movement_state() & (1 << 0)))
					cmd->ibuttons &= ~IN_JUMP;
			}
		}

		if (data::ircs)
		{
			rc::manage_rc(cmd);
		}

		utils::sanitize_usercmd(cmd);

		return 0;
	}
}