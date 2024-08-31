/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/
int countdown_ticks = 0;
int previous_user = 0;
ConVar* name = 0;

bool IsValidPlayer(C_BaseEntity* pl)
{
	if (!pl)
		return false;

	if (pl == GetLocalEntity())
		return false;

	if ((int) pl == previous_user)
		return false;

	return true;
}

bool IsValidPlayer2(int pl)
{
	return IsValidPlayer((C_BaseEntity*) m_pClientEntList->GetClientEntity(pl));
}

int ValidPlayers()
{
	int valid_players = 0;

	for (int i = 1; i <= m_pEngine->GetMaxClients(); ++i)
	if (IsValidPlayer((C_BaseEntity*) m_pClientEntList->GetClientEntity(i)))
		valid_players++;

	return valid_players;
}

void Think()
{

	if (countdown_ticks > 0)
	{
		countdown_ticks--;
		return;
	}

	if (ValidPlayers() < 3)
		return;

	int user = 0;
	while (!user)
	{
		int randp = (rand() % m_pEngine->GetMaxClients()) + 1;

		if (IsValidPlayer2(randp))
			user = randp;
	}

	if (!name)
		name = m_pCVar->FindVar("name");

	if (name)
	{
		player_info_t info;
		m_pEngine->GetPlayerInfo(user, &info);

		char new_name[64];
		sprintf(new_name, "\xE2\x80\x8F%s", info.name);

		*name->GetCallback() = 0;
		name->SetValue(new_name);

		previous_user = user;
		countdown_ticks = (1.f / m_pGlobals->interval_per_tick); //  (1.f / m_pGlobals->interval_per_tick); since this gabage doesn't work

		if (ConVar* timeout_static = m_pCVar->FindVar("sv_namechange_cooldown_seconds"))
			countdown_ticks *= timeout_static->GetFloat();
	}
}

void Nosky()
{
/*	if( cvarNoSky == 1 )
	{
		m_pEngine->ClientCmd( "gl_clear 1" );
		m_pEngine->ClientCmd( "__r_drawskybox 0" );
		//m_pEngine->ClientCmd( "__r_3dsky 0" );
	}
	else
	{
		m_pEngine->ClientCmd( "gl_clear 1" );
		m_pEngine->ClientCmd("__r_drawskybox 1");
		//m_pEngine->ClientCmd( "__r_3dsky 1" );
	}*/
}

void Bunnyhop( CUserCmd *cmd )
{
	if ( cmd->buttons & IN_JUMP && cvarBunnyhop == 1 )
	{
		if( !( GetPlayerFlags( GetLocalEntity() ) &FL_ONGROUND ) )
			cmd->buttons &= ~IN_JUMP;
		if (!(GetPlayerFlags(GetLocalEntity()) &FL_ONGROUND))
			cmd->buttons &= ~IN_JUMP;
	}

	if ( cmd->buttons & IN_ATTACK && IsPistol() && cvarAutopistol == 1 )
	{
		static bool isauto = false;
		if( !isauto )
			cmd->buttons |=  IN_ATTACK;
		else
			cmd->buttons &= ~IN_ATTACK;

		isauto = !isauto;
	}
}

void Autostrafe(CUserCmd* cmd)
{
	C_BaseEntity* pLocal = GetLocalEntity();

	static bool bDirection = false;
	bool bKeysPressed = true;
	bool bAir = GetPlayerFlags(pLocal) & FL_ONGROUND;

	Vector vecOldView = (Vector&)cmd->viewangles;
	Vector vecSelfVelocity = GetVelocity(pLocal);
	Vector fvecT;
	float fYaw = 0.f;
	float fRes = 0.f;

	if (GetAsyncKeyState(0x41) || GetAsyncKeyState(0x57) || GetAsyncKeyState(0x53) || GetAsyncKeyState(0x44)) // A D 
		bKeysPressed = false;

	if (GetAsyncKeyState(0x20) && bAir && bKeysPressed)

	if (vecSelfVelocity.Length() <= 50)
		cmd->sidemove = 800.f;

	if (!bAir && cmd->buttons & IN_JUMP)
	{
		if (vecSelfVelocity.Length() <= 65)
			cmd->sidemove = 800.f;

		cmd->buttons &= ~IN_JUMP;
	}

	if (vecSelfVelocity.Length() > 65)
	{
		fvecT = Vector(30.f, vecSelfVelocity.Length(), 0);

		fvecT.z = fvecT.x / fvecT.y;
		fvecT.z = fabsf(fvecT.z);
		fRes = (fvecT.x * fvecT.z);
		fYaw = fRes;
	}

	if (GetAsyncKeyState(0x20) && !bAir && bKeysPressed)
	{
		
		if (cmd->mousedy > 0)
			cmd->sidemove = 800.f;

		if (cmd->mousedx < 0)
			cmd->sidemove = -800.f;

		if (bDirection)
		{
			cmd->viewangles.y -= fYaw;
			cmd->sidemove = -800.f;
			bDirection = false;
		}
		else
		{
			cmd->viewangles.y += fYaw;
			cmd->sidemove = 800.f;
			bDirection = true;
		}
		
	}
}

void Norecoil( CUserCmd *cmd )
{
/*	if( cvarNoRecoil == 0 )
		return;

	if( !( cmd->buttons & IN_ATTACK ) )
		return;
	
	QAngle punchAngle =  *( QAngle* )( GetPlayerPunchAngle( GetLocalEntity() ) );
	static QAngle qOldPunch( 0, 0, 0 );
	static QAngle qOldestPunch( 0, 0, 0 );
	QAngle qDeltaPunch( 0, 0, 0 );

	qDeltaPunch = punchAngle - qOldestPunch;
	qOldestPunch = qOldPunch;
	qOldPunch = punchAngle;
	QAngle nextPunch = punchAngle + qDeltaPunch;

	cmd->viewangles[0] -= ( punchAngle[0] + nextPunch[0] );
	cmd->viewangles[1] -= ( punchAngle[1] + nextPunch[1] );
	cmd->viewangles[2] -= ( punchAngle[2] + nextPunch[2] );*/
}

int speedCmd = 2;

void SpeedHack(void *__ebp, int factor) {
	byte *sendPacket = (byte *) (*(char **) __ebp - 0x1);
	DWORD *retnAddr = (DWORD *) (*(char **) __ebp + 0x4);

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

void FakeLag(CUserCmd *cmd, bool *bSendPackets){
	if (cvarFakeLag){
	static int queued = 0;
	const int maxcmds = 15;

		if (queued >= 0)
		{
			queued++;
			if (queued < 5)
			{
				*bSendPackets = true;
			}
			else
			{
				*bSendPackets = false;
			}
		}
		if (queued == maxcmds)
			queued = 0;
	}
};

void FakeLag2(CUserCmd *cmd, bool *bSendPackets){
	if (cvarFakeLag2){
		static int queued = 0;
		const int maxcmds = 15;

		if (queued >= 0)
		{
			queued++;
			if (queued < 5 || cmd->buttons&IN_ATTACK)
			{
				*bSendPackets = true;
			}
			else
			{
				*bSendPackets = false;
			}
		}
		if (queued == maxcmds)
			queued = 0;
	}
};

C_BaseEntity *nametar;

void AntiAntiAimX(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
	/*float flPitch = pData->m_Value.m_Float;

	if (flPitch < -89)
		flPitch = 90;
	if (flPitch > 89)
		flPitch = 90;

	*(float*) pOut = flPitch;*/

	float flPitch = pData->m_Value.m_Float;

	if (cvarAntiAntiAim)
	{
		if (flPitch > 89)
		{
			flPitch = 270;
		}
		if (flPitch < -89)
		{
			flPitch = 90;
		}
	}

	*(float*) pOut = flPitch;
}
void AntiAntiAimY(const CRecvProxyData *pData, void *pStruct, void *pOut)
{
	static bool lookedLastTick[MAX_PLAYERS];
	float flYaw = pData->m_Value.m_Float;
	flYaw -= 0.087929;
	bool tmp = lookedLastTick[((C_BaseEntity*) (pStruct))->index];
	lookedLastTick[((C_BaseEntity*) (pStruct))->index] = (flYaw >= 180 && flYaw <= 360);
	if (tmp && (flYaw >= 0 && flYaw <= 180))
	{
		flYaw += 359;
	}
	flYaw = flYaw - (int) (flYaw / 360) * 360;
	if (flYaw < -180)
	{
		flYaw = flYaw + 360;
	}
	else if (flYaw > 180)
	{
		flYaw = flYaw - 360;
	}
	*(float*) pOut = flYaw;
}