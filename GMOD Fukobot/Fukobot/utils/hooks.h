class CHooks{
public:
	void GetHooks();

}; CHooks Hooks;

void CHooks::GetHooks()
{

	oPaintTraverse = (PaintTraverseFn)vtablehook_hook(VPanel, Hooked_PaintTraverse, 41);
	oCreateMove = (CreateMoveFn)vtablehook_hook(ClientMode, Hooked_CreateMove, 21);
	oClCreateMove = (ClCreateMoveFn)vtablehook_hook(Client, Hooked_ClCreateMove, 21);
	oOverrideView = (OverrideViewFn)vtablehook_hook(ClientMode, Hooked_OverrideView, 16);
	//oGetUserCmd = (GetUserCmdFn)vtablehook_hook(Input, Hooked_GetUserCmd, 8); // oGetUserCmd = 
	//oCreateInterface = (CreateLuaInterfaceFn)vtablehook_hook(LuaShared, Hooked_CreateInterface, 4);
	//oCloseInterface = (CloseLuaInterfaceFn)vtablehook_hook(LuaShared, Hooked_CloseInterface, 5);

	NVarManager->HookProp("DT_HL2MP_Player", "m_angEyeAngles[0]", FixAA);

}