class esp{
public:
	void DrawPlayer();
	void DrawCrosshair();
}; esp *Esp = new esp;

void esp::DrawCrosshair()
{

	if (!*Vars->ESP_ShowCrosshair)
		return;

	int Width, Height;
	Engine->GetScreenSize(Width, Height);

	int x = Width*.5;
	int y = Height*.5;

	int Len = 5;
	int Gap = 0;
	int BoxX, BoxY, BoxX2, BoxY2; 
	BoxX = x - Len;
	BoxY = y - Len;
	BoxX2 = x + Len; 
	BoxY2 = y + Len;

	Draw->DrawLine(BoxX, BoxY, x - Gap, y - Gap, COL_CHEAT);
	Draw->DrawLine(BoxX2, BoxY2, x + Gap, y + Gap, COL_CHEAT);
	Draw->DrawLine(BoxX, BoxY2, x - Gap, y + Gap, COL_CHEAT);
	Draw->DrawLine(BoxX2, BoxY, x + Gap, y - Gap, COL_CHEAT);

	Draw->DrawLineOutline(BoxX, BoxY, x - Gap, y - Gap, COL_BLACK);
	Draw->DrawLineOutline(BoxX2, BoxY2, x + Gap, y + Gap, COL_BLACK);
	Draw->DrawLineOutline(BoxX, BoxY2, x - Gap, y + Gap, COL_BLACK);
	Draw->DrawLineOutline(BoxX2, BoxY, x + Gap, y - Gap, COL_BLACK);

}

void GetCoords(CBaseEntity* Ent, int* minx, int* miny, int* maxx, int* maxy, bool* ShouldDraw)
{
	Vector min; Vector max;
	max = Ent->GetCollideable()->OBBMaxs();
	min = Ent->GetCollideable()->OBBMins();

	std::vector<Vector> corners = 
	{
		Vector(min.x, min.y, min.z),
		Vector(min.x, min.y, max.z),
		Vector(min.x, max.y, min.z),
		Vector(min.x, max.y, max.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, min.y, max.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, max.y, max.z)
	};

	int MinX, MinY, MaxX, MaxY;
	int W, H;
	Engine->GetScreenSize(W, H);
	MinX = W * 2;
	MinY = H * 2;
	MaxX = 0;
	MaxY = 0;

	for (Vector corner : corners)
	{

		Vector Pos3D;
		Vector OnScreen;

		if (Ent->GetAbsAngles() == vec3_angle)
		{
			VectorAdd(corner, Ent->GetAbsOrigin(), Pos3D);
		}
		else
		{
			VectorTransform(corner, Ent->EntityToWorldTransform(), Pos3D);
		}

		*ShouldDraw = WorldToScreen(Pos3D, OnScreen);
		
		MinX = min(MinX, OnScreen.x);
		MinY = min(MinY, OnScreen.y);
		MaxX = max(MaxX, OnScreen.x);
		MaxY = max(MaxY, OnScreen.y);

	}

	*minx = MinX;
	*miny = MinY;
	*maxx = MaxX;
	*maxy = MaxY;

}	


void esp::DrawPlayer()
{

	if (!*Vars->ESP_ShowPlayer)
		return;

	for (int i = 0; i < ClientEntList->GetHighestEntityIndex(); i++)
	{

		CBaseEntity* LocalPlayer = (CBaseEntity*)ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
		CBaseEntity* Target = (CBaseEntity*)ClientEntList->GetClientEntity(i);

		if (Target == NULL)
			continue;

		if (Target == LocalPlayer)
			continue;

		if (Target->IsDormant())
			continue;

		player_info_s PlayerInfo;
		if (Engine->GetPlayerInfo(i, &PlayerInfo))
		{

			int x1, y1, x2, y2; bool ShouldDraw;
			GetCoords(Target, &x1, &y1, &x2, &y2, &ShouldDraw);

			if (ShouldDraw)
			{

				Surface->DrawSetColor(0, 0, 0, 200);
				Surface->DrawOutlinedRect(x1 - 1, y1 - 1, x2 + 1, y2 + 1);
				Surface->DrawOutlinedRect(x1 + 1, y1 + 1, x2 - 1, y2 - 1);

				Draw->DrawStringA(FukoFont, x1 + (x2 - x1) / 2, y1 - 7, Color(255, 255, 255, 255), PlayerInfo.name);

				Surface->DrawSetColor(200, 0, 0, 255);
				Surface->DrawOutlinedRect(x1, y1, x2, y2);

				//int PlayerHealth = *(int*)((DWORD)Target + 0x90);
				int PlayerHealth = *(int*)((DWORD)Target + NVarManager->GetOffset("DT_BaseEntity", "m_iHealth"));
				int BarWidth = (x2 - x1)*.045;

				Surface->DrawSetColor(0, 0, 0, 200);
				Surface->DrawFilledRect(x1 - BarWidth - 2, y1 - 1, x1 - 2, y2 + 1);
				int BarHeight = ((y2 - y1) * PlayerHealth) / 100;

				Surface->DrawSetColor(0, 200, 0, 255);
				Surface->DrawFilledRect(x1 - BarWidth - 2 - 1, y1, x1 - 3, y1 + BarHeight + 1);

			}

		}
		else
		{

			Vector Pos3D = Target->GetAbsOrigin();
			Vector Pos;

			if (WorldToScreen(Pos3D, Pos))
			{
				//string_t ClassName = *(string_t*)((DWORD)Target + NVarManager->GetOffset("DT_BaseEntity", "m_RealClassName"));
				//Draw->DrawStringA(FukoFont, Pos.x, Pos.y, Color(255, 255, 255, 255), "%s", ClassName.ToCStr() );
			}

		}
	
	}

}