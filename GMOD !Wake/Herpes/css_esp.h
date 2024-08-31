/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

void Crosshair() //not stolen from ph0ne i promise
{
	if (cvarCrosshair == 1){
		int iWidth, iHeight;

		m_pEngine->GetScreenSize(iWidth, iHeight);

		iWidth *= 0.5f;
		iHeight *= 0.5f;

		m_pSurface->DrawSetColor(0, 0, 0, 255);
		m_pSurface->DrawFilledRect(iWidth - 1, iHeight - 4, iWidth + 2, iHeight + 5);
		m_pSurface->DrawFilledRect(iWidth - 4, iHeight - 1, iWidth + 5, iHeight + 2);

		m_pSurface->DrawSetColor(0, 255, 0, 255);
		m_pSurface->DrawFilledRect(iWidth, iHeight - 3, iWidth + 1, iHeight + 4);
		m_pSurface->DrawFilledRect(iWidth - 3, iHeight, iWidth + 4, iHeight + 1);
	}
}

void SpeedDraw()
{
	C_BaseEntity* pLocal = GetLocalEntity();
	float d = (GetVelocity(pLocal).Length() / 10);
	if (cvarHealthESP == 1)
	{
		if (d >= 0)
		{
			DrawString(10, 40, Color(0, 0, 255, 255), ("Vel:" + boost::lexical_cast<std::string, int> (d)));
		}
		if (d >= 100)
		{
			DrawString(10, 40, Color(0, 255, 0, 255), ("Vel:" + boost::lexical_cast<std::string, int> (d)));
		}
		if (d >= 200)
		{
			DrawString(10, 40, Color(255, 0, 0, 255), ("Vel:" + boost::lexical_cast<std::string, int> (d)));
		}
	}
}

void DrawHitbox( C_BaseEntity* pl )
{
	for( int i = 0; i <= 40; i++ )
	{
		Vector vec;
		QAngle ang;
		if( GetHitboxPosition( i, vec, pl->index, ang ) )
		{
			Vector bone;
			if( WorldToScreen( vec, bone ) )
			{
				std::stringstream out;
				out << i;
				std::string str = out.str();
				BeginESPDraw( bone.x, bone.y, Color( 255, 255, 255, 255 ) );
				DrawESPText( str );
			}
		}
	}
}

void DrawBox( C_BaseEntity* pl )
{;
	Vector vec, vec1, vec2, vec3, vec4;
	
	QAngle ang;

	if( !GetBonePosition( 14, vec, ang, pl->index ) )
		return;
	vec3 = vec - Vector( 0, 0, 55 );

	float size = 10;
	Vector head, pos;
	if( WorldToScreen( vec, head ) && WorldToScreen( vec3, pos ) )
	{
		Vector headR = head + Vector( size, 0, 0 ); // right
		Vector headL = head + Vector( -size, 0, 0 ); // left
		Vector absR = pos + Vector( size, 0, 0 ); // right
		Vector absL = pos + Vector( -size, 0, 0 ); // left
		m_pSurface->DrawSetColor( Color( 0, 255, 0, 255 ) );
		m_pSurface->DrawLine( headL.x, headL.y, headR.x, headR.y );
		m_pSurface->DrawLine( headR.x, headR.y, absR.x, absR.y );
		m_pSurface->DrawLine( absR.x, absR.y, absL.x, absL.y );
		m_pSurface->DrawLine( absL.x, absL.y, headL.x, headL.y );
	}
}

void DrawPlayerESP(int Index)
{
	if (m_pEngine->IsConnected() == false
		|| m_pEngine->IsInGame() == false
		|| m_pEngine->IsLevelMainMenuBackground() == true)
		return;

	Vector AbsScreen, Abserson;
	Color color;
	color = Color(255, 255, 255, 255);

	IClientEntity* pEnt = m_pClientEntList->GetClientEntity(Index);

	if (!pEnt || pEnt->IsDormant())
		return;

	C_BaseEntity* pBaseEntity = pEnt->GetBaseEntity();

	if (pBaseEntity == NULL)
		return;

	if (pBaseEntity->entindex() <= m_pEngine->GetMaxClients())
	{
		player_info_s plInfo;
		if (GetPlayerLifeState(pBaseEntity) != LIFE_ALIVE)
			return;
		if (!pBaseEntity)
			return;
		if (!m_pEngine->GetPlayerInfo(Index, &plInfo))
			return;

		Vector vec, head, abs;

		QAngle ang;
		if (!GetBonePosition(10, vec, ang, Index))
			return;
		if (WorldToScreen(vec, AbsScreen))
		{
			Vector mon, nom;
			nom = pEnt->GetAbsOrigin();

			if (GetPlayerFlags(pBaseEntity) & FL_DUCKING)
			{
				mon = nom + Vector(0, -1.6f, 50.f);
			}
			else
			{
				mon = nom + Vector(0, -1.6f, 70.f);
			}
			Vector bot, top;
			float h, w;
			if (WorldToScreen(nom, bot) && WorldToScreen(mon, top))
			{
				h = (bot.y - top.y);
				w = h / 5.f;

				BeginESPDraw((top.x + w) + 1, top.y, Color(255, 255, 255, 255));
			}
			if (cvarBoxESP == 1){
				DrawOutlinedRectangle(top.x - w, top.y, w * 2, (bot.y - top.y), GetTeamColor(pBaseEntity));
			}
			if (cvarNameESP == 1){
				DrawESPText(plInfo.name);
			}
			if (cvarHealthESP == 1)
			{
				DrawESPText("Hp: " + boost::lexical_cast<std::string, int> (GetPlayerHealth(pBaseEntity)));
			}
			/*if (cvarNameESP == 1)
			{
				DrawESPText(plInfo.name);
			}
			
			if (cvarWeaponESP == 1)
			{
				//DrawESPText("W: " + boost::lexical_cast<std::string> (GetActiveWeapon(pBaseEntity)->GetClientClass()->m_pNetworkName));
				/* will not work in GMod unless I do some magic */
			//}
		}
	}
}