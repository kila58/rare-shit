class misc{
public:
	void SpeedHack();

}; misc *Misc = new misc;

void misc::SpeedHack() { // TODO: pSpeed

	if (!*Vars->MIS_Speed == 1)
		return;

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		Cvar->FindVar("host_timescale")->SetValue(5);
	}
	else
	{
		Cvar->FindVar("host_timescale")->SetValue(1);
	}

}