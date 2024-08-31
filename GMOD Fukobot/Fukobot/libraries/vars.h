class vars{
public:
	// Aimbot:
	int* AIM_Enabled		= new int;
	int* AIM_AutoFire		= new int;
	int* AIM_SilentAim		= new int;
	int* AIM_TargetTeam		= new int;
	// ESP:
	int* ESP_ShowPlayer		= new int;
	int* ESP_ShowBones		= new int;
	int* ESP_ShowEntity		= new int;
	int* ESP_ShowCrosshair	= new int;
	// HvH:
	int* HVH_AA				= new int;
	int* HVH_AAA			= new int;
	int* HVH_KillStreak		= new int;
	int* HVH_FakeLag		= new int;
	// Misc:
	int* MIS_BunnyHop		= new int;
	int* MIS_Speed			= new int;
	int* MIS_ChatSpam		= new int;
	int* MIS_NoSpread		= new int;

	void init();

}; vars *Vars = new vars;

void vars::init()
{
	*AIM_Enabled		= 0;
	*AIM_AutoFire		= 0;
	*AIM_SilentAim		= 0;
	*AIM_TargetTeam		= 0;
	*ESP_ShowPlayer		= 0;
	*ESP_ShowBones		= 0;
	*ESP_ShowEntity		= 0;
	*ESP_ShowCrosshair	= 0;
	*HVH_AA				= 1;
	*HVH_AAA			= 1;
	*HVH_KillStreak		= 0;
	*HVH_FakeLag		= 0;
	*MIS_BunnyHop		= 1;
	*MIS_Speed			= 0;
	*MIS_ChatSpam		= 0;
	*MIS_NoSpread		= 0;
}