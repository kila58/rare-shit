void __fastcall Hooked_PaintTraverse(void *thisptr, void *_EDX, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{

	oPaintTraverse(thisptr, _EDX, vguiPanel, forceRepaint, allowForce);

	if (!strcmp(VPanel->GetClassName(vguiPanel), "OverlayPopupPanel"))
	{
		Draw->CreateFonts();
		Esp->DrawCrosshair();
		Esp->DrawPlayer();
		
		FukoMenu->Paint();
	}

}

void __fastcall Hooked_CreateMove(void* thisptr, void* _EDX, float InputSampleTime, CUserCmd *UserCmd)
{

	oCreateMove(thisptr, _EDX, InputSampleTime, UserCmd);

	CBaseEntity* LocalPlayer = (CBaseEntity*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
	int iFlags = *(PINT)((DWORD)LocalPlayer + 0x350);
	if (*Vars->MIS_BunnyHop && (UserCmd->buttons & IN_JUMP) ) 
	{
		if (!(iFlags&FL_ONGROUND) && !(iFlags&FL_PARTIALGROUND))
		{
			UserCmd->buttons &= ~IN_JUMP;
		}
		else
		{
			UserCmd->buttons |= IN_JUMP;
			//UserCmd->buttons |= IN_DUCK;
		}
	}

	if (UserCmd)
		Aimbot.Aimbot(UserCmd);

	if (FukoMenu->Enabled)
		Lua.RunString("gui.EnableScreenClicker(true)");
	else
		Lua.RunString("gui.EnableScreenClicker(false)");


}

int speedCmd = 2;
void SpeedHack(void *__ebp, int factor) {
	byte *sendPacket = (byte *)(*(char **)__ebp - 0x1);
	DWORD *retnAddr = (DWORD *)(*(char **)__ebp + 0x1);

	if (speedCmd > 1)
	{
		speedCmd -= 1;
		*sendPacket = 0;
		*retnAddr -= 0x5;
	}
	else
	{
		speedCmd = factor;
		*sendPacket = 1;
	}
}

void __fastcall Hooked_ClCreateMove(void* thisptr, void* _EDX, int sequence_number, float input_sample_frametime, bool active)
{

	oClCreateMove(thisptr, _EDX, sequence_number, input_sample_frametime, active);

	void *__ebp = NULL;
	_asm mov __ebp, ebp;

	Aimbot.bSendPacket = (bool *)(*(DWORD*)(__ebp)-0x1);

	static int iSpeedEffect = 0;
	int SpeedFac = 5;

	if (GetAsyncKeyState(VK_SHIFT) && *Vars->MIS_Speed == 1)
	{
		if (iSpeedEffect <= SpeedFac) {
			iSpeedEffect++;
			*(*(char**)__ebp + 0x4) -= 0x5;
		}
		else if (iSpeedEffect >= SpeedFac+1) {
			iSpeedEffect = 0;
		}
	}

}

void __fastcall Hooked_OverrideView(void* _EDX, void* This, CViewSetup* ViewSetup)
{
	oOverrideView(_EDX, This, ViewSetup);
	ViewSetup->angles = Aimbot.FakeView;
}

void __fastcall Hooked_RunString(void* _EDX, void* This, const char* Identifier, const char* Path, const char* LuaString, bool ShouldRun, bool IForgot)
{

	oRunString(_EDX, This, Identifier, Path, LuaString, ShouldRun, IForgot);
	
	if (strcmp(Identifier, "[C]") && strcmp(Identifier, "RunString") && strcmp(Identifier, "LuaCmd"))
		Msg("%s\n", Identifier);

	if (!strcmp(Identifier, "Startup"))
		oRunString(_EDX, This, Identifier, Path, "print('<3')", ShouldRun, IForgot);

}

bool IsHooked = false;
void* __stdcall Hooked_CreateInterface(char state, bool renew)
{

	void* ret = oCreateInterface(state, renew);

	Msg("[RunString] CreateInterface has been called!\n");

	if (state == LUA_CLIENT) // This is implying you want to hook for ClientSide Lua.
	{

		if (IsHooked)
			vtablehook_hook(ret, oRunString, 88);

		IsHooked = true;
		oRunString = (RunStringFn)vtablehook_hook(ret, Hooked_RunString, 88);
		Msg("[RunString] Hooked RunString! \n");
	}

	return ret;

}

void* __stdcall Hooked_CloseInterface(ILuaInterface* LuaInt)
{
	vtablehook_hook(LuaInt, oRunString, 88);
	return oCloseInterface(LuaInt);
}

void FixAA(const CRecvProxyData *Data, void *Struct, void *Out)
{

	float Pitch = Data->m_Value.m_Float;

	if (Pitch == 90)
		Pitch = 270;
	else if (Pitch == -90)
		Pitch = 90;

	*(float*)Out = Pitch;

}