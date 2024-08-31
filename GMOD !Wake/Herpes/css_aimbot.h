/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/
C_BaseEntity* tar;
float bestDist;

QAngle viewangle = QAngle( 0, 0, 0 );
QAngle DeltaPunch = QAngle();

float MathDist( float x1, float y1, float x2, float y2 )
{
	return std::sqrtf( ( ( x2 - x1 ) * ( x2 - x1 ) ) + ( ( y2 - y1 ) * ( y2 - y1 ) ) );
}

static const float RAD_TO_DEG_f = 57.295779513082320876798154814105f;
static const float M_RADPI = 57.295779513082f;

void CalcAngle( Vector &src, Vector &dst, QAngle &angles )
{

	double delta[3] = {(src[0] - dst[0]),(src[1] - dst[1]),(src[2] - dst[2])};
	double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	angles[0] = (float)(atan(delta[2] / hyp) * RAD_TO_DEG_f);
	angles[1] = (float)(atan(delta[1] / delta[0]) * RAD_TO_DEG_f);
	angles[2] = 0.0f;
	if(delta[0] >= 0.0)
		angles[1] += 180.0f;
}

float GetFov( QAngle angle, Vector src, Vector dst ) 
{
	QAngle ang,aim; 
	float fov; 
	double delta[3] = { (src[0]-dst[0]), (src[1]-dst[1]), (src[2]-dst[2]) };
	double hyp = sqrt(delta[0]*delta[0] + delta[1]*delta[1]);
	ang[0] = (float) (atan(delta[2]/hyp) * M_RADPI);
	ang[1] = (float) (atan(delta[1]/delta[0]) * M_RADPI);
	ang[2] = 0.0f;
	if(delta[0] >= 0.0) { ang[1] += 180.0f; }
	float pitch,yaw,tmp;
	pitch	= (float)(angle[0] * M_PI/180); 
	yaw		= (float)(angle[1] * M_PI/180); 
	tmp		= (float) cos(pitch);
	aim[0] = (float) (-tmp * -cos(yaw)); 
	aim[1] = (float) (sin(yaw)*tmp);
	aim[2] = (float) -sin(pitch);
	pitch	= (float)(ang[0] * M_PI/180); 
	yaw		= (float)(ang[1] * M_PI/180); 
	tmp		= (float) cos(pitch);
	ang[0] = (float) (-tmp * -cos(yaw)); 
	ang[1] = (float) (sin(yaw)*tmp);
	ang[2] = (float) -sin(pitch);
	float mag_s = sqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2])); 
	float mag_d = sqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2])); 
	float u_dot_v = aim[0]*ang[0] + aim[1]*ang[1] + aim[2]*ang[2]; 
	fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI); 
	return fov; 
}

void Normalize(Vector &vIn, Vector &vOut)
{
    float flLen = vIn.Length();
    if(flLen == 0)
    {
        vOut.Init(0, 0, 1);
        return;
    }
    flLen = 1 / flLen;
    vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}


bool GetHitbox( int iHitBox, Vector& vecOrigin, QAngle qAngles, int index )
{
	if( iHitBox < 0 || iHitBox >= 20 )
		return false;
	matrix3x4_t pmatrix[MAXSTUDIOBONES];
	Vector vMin, vMax;
	IClientEntity* ClientEntity = m_pClientEntList->GetClientEntity( index );
	if ( ClientEntity == NULL )
		return false;
	if ( ClientEntity->IsDormant() )
		return false;
	const model_t * model;
	model = ClientEntity->GetModel();

	if( model )
	{
		studiohdr_t *pStudioHdr = m_pModelInfo->GetStudiomodel(model);
		if ( !pStudioHdr )
			return false;
		if( ClientEntity->SetupBones( pmatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, m_pGlobals->curtime) == false )
			return false;
		mstudiohitboxset_t *set = pStudioHdr->pHitboxSet( 0 );
		if ( !set )
			return false;
		mstudiobbox_t* pbox = NULL;
		pbox = pStudioHdr->pHitbox(iHitBox, 0);
		VectorTransform( pbox->bbmin, pmatrix[ pbox->bone ], vMin );
		VectorTransform( pbox->bbmax, pmatrix[ pbox->bone ], vMax );
		vecOrigin = ( vMin + vMax ) * 0.5f;

		if (cvarBoxFix == 1){
			vecOrigin.z += 5.6;
		}

		return true;
	}
	return false;
}

Vector GetHeadPosition( C_BaseEntity* pEntity )
{
	Vector vecViewOffset;

	QAngle ang;
	if( !GetHitbox( cvarAimspot, vecViewOffset, ang, pEntity->index ) )
		return pEntity->GetAbsOrigin();

	return vecViewOffset;
}

bool IsVisibleToAimbot( C_BaseEntity* pEntity )
{
	trace_t tr;
	Ray_t ray;

	C_BaseEntity* pLocal = GetLocalEntity();

	Vector selfPos = EyePos( GetLocalEntity() );

	Vector vE;
	QAngle ang2;
	if( !GetHitbox( 0, vE, ang2, pEntity->index ) )
		return false;

	ray.Init( selfPos, vE );
	m_pEngineTrace->TraceRay( ray, MASK_SHOT, NULL, &tr );

	if( tr.fraction > 0.97f )
		return true;

	player_info_s pinfo;

	if( tr.m_pEnt && pEntity )
	{
		if ( tr.m_pEnt->index == 0 || tr.allsolid )
		return false;

		if ( ( m_pEngine->GetPlayerInfo( tr.m_pEnt->index, &pinfo )
		|| pEntity->index == tr.m_pEnt->index ) && tr.fraction != 1.0 )
		return true;
	}
	return false;
}

C_BaseEntity* GetBestTarget( CUserCmd* cmd )
{
	for( int i = 0; i <= m_pEngine->GetMaxClients(); i++ )
	{
		if( i == m_pEngine->GetLocalPlayer() )
			continue;

		C_BaseEntity* pl = GetEntityByIndex( i );

		if( !pl )
			continue;

		if( !GetLocalEntity() )
			continue;

		Color Alpha = *(Color*) ((DWORD) pl + cssAlpha);
		int myTeam = GetPlayerTeamNumber( GetLocalEntity() );
		int Team = GetPlayerTeamNumber( pl );
		int Health = GetPlayerHealth( pl );

		if( GetPlayerLifeState( pl ) != LIFE_ALIVE )
			continue;
		player_info_t pi;
		if (m_pEngine->GetPlayerInfo(pl->index, &pi) == false)
			continue;

		//if (pi.fakeplayer || pi.friendsID == NULL)
		//	continue;
		CSteamID fID = CSteamID(pi.friendsID, k_EUniversePublic, k_EAccountTypeIndividual);
		if (m_pSteamFriends->HasFriend(fID, k_EFriendFlagImmediate) && cvarFriends == 1)
			continue;
		if (Alpha.a() < 245)
			continue;
		if( ( cvarDeathmatch == 1 ) && Health > 100 && Alpha.a() > 240 )
			continue;
		if( ( cvarFriendlyfire == 0 ) && myTeam == Team )
			continue;

		Vector targetVec, selfVec;
		QAngle ang;

		if (!IsVisibleToAimbot(pl))
			continue;

		Vector tarPos, oldPos;
		Vector self = EyePos(GetLocalEntity());
		Vector target = pl->GetAbsOrigin() + Vector(0, 0, 50);

		float tarDist = MathDist(self.x, self.y, target.x, target.y);

		if (tarDist <= bestDist)
		{
			tar = pl;
			bestDist = tarDist;
		}

		if (tar == NULL)
		{
			tar = pl;
			bestDist = tarDist;
		}
	}
	return tar;
}

bool AimKeyPressed()
{
	if( cvarAimkey == 0 )
		return true;
	
	if( cvarAimkey == 1 && GetAsyncKeyState( 0x01 ) )	// Mouse 1
		return true;
	
	if (cvarAimkey == 2 && GetAsyncKeyState(0x46))
		return true;

	return false;
}

void Aimbot( CUserCmd* cmd )
{
	QAngle ang;
	
	tar = NULL;
	bestDist = 0;

	if( !AimKeyPressed() )
		return;

	C_BaseEntity *targ = GetBestTarget( cmd );
	C_BaseEntity* pMe = GetLocalEntity();

	if( !targ )
		return;
	m_pPrediction->RunCommand(pMe, cmd, NULL);
	Vector tarPos, selfPos;

	if( !GetHitbox( cvarAimspot, tarPos, ang, targ->index ) )
		return;

	selfPos = EyePos(GetLocalEntity()) + *(Vector*) ((DWORD) GetLocalEntity() + cssVELOCITY) * m_pGlobals->interval_per_tick;

	if( GetFov( GetLocalEntity()->GetAbsAngles(), selfPos, tarPos ) > cvarFOV )
		return;
	
	// Now start aimbot prediction/aiming/autoshoot
	Vector vPredicted( 0, 0, 0 );

	float fFrameTime = m_pGlobals->frametime;
	Vector tarvec = *( Vector* )( ( DWORD )targ + cssVELOCITY );
	Vector selfvec = *( Vector* )( ( DWORD )GetLocalEntity() + cssVELOCITY );

	//if( cvarPrediction == 1 )
	//	vPredicted = tarPos + ( ( tarvec * fFrameTime ) - ( selfvec * fFrameTime ) );
	//else
		vPredicted = tarPos;
	
	Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
	QAngle qAimAngles;

	float forward = cmd->forwardmove;
	float right = cmd->sidemove;
	float up = cmd->upmove;

	cmd->mousedx = 9999;
	cmd->mousedy = 9999;

	qAimAngles.Init(0.0f,cmd->viewangles.x,0.0f);
	qAimAngles.Init(0.0f,cmd->viewangles.y,0.0f);

	AngleVectors(qAimAngles,&viewforward,&viewright,&viewup);
	AngleVectors(cmd->viewangles,&viewforward,&viewright,&viewup);

	m_pPrediction->RunCommand(pMe, cmd, NULL);

	CalcAngle( selfPos, vPredicted, cmd->viewangles );

	if( cvarSilentAim == 0 )
	{
		ang = cmd->viewangles;
		m_pEngine->SetViewAngles( ang );
	}
	else
	{
		qAimAngles.Init(0.0f,cmd->viewangles.x,0.0f);
		qAimAngles.Init(0.0f,cmd->viewangles.y,0.0f);

		AngleVectors(qAimAngles,&aimforward,&aimright,&aimup);
		AngleVectors(cmd->viewangles,&aimforward,&aimright,&aimup);

		Vector vForwardNorm;
		Vector vRightNorm;
		Vector vUpNorm;

		Normalize(viewforward,vForwardNorm);
		Normalize(viewright,vRightNorm);
		Normalize(viewup,vUpNorm);

		cmd->forwardmove = DotProduct(forward * vForwardNorm,aimforward) + DotProduct(right * vRightNorm,aimforward) + DotProduct(up * vUpNorm, aimforward);
		cmd->sidemove = DotProduct(forward * vForwardNorm,aimright) + DotProduct(right * vRightNorm,aimright) + DotProduct(up * vUpNorm,aimright);
		cmd->upmove = DotProduct(forward * vForwardNorm,aimup) +DotProduct(right * vRightNorm,aimforward) +DotProduct(up * vUpNorm,aimforward);
	}

	if (cvarAutoshoot == 1)
	{
		if (GetActiveWeapon((C_BaseEntity*) m_pClientEntList->GetClientEntity(m_pEngine->GetLocalPlayer()))){
			float flServerTime = (float) *(int*) ((DWORD) m_pClientEntList->GetClientEntity(m_pEngine->GetLocalPlayer()) + cssTickBase) /*m_nTickBase*/ * m_pGlobals->interval_per_tick;
			float flNextPrimaryAttack = *(float*) ((DWORD) GetActiveWeapon((C_BaseEntity*) m_pClientEntList->GetClientEntity(m_pEngine->GetLocalPlayer())) + cssPrimary); /*NextPrimaryAttack*/
			if (flNextPrimaryAttack < flServerTime){
				static bool attacking = false;
				if (IsPistol())
				{
					if (!attacking)
						cmd->buttons |= IN_ATTACK;
					else
						cmd->buttons &= ~IN_ATTACK;
					attacking = !attacking;
				}
				else
					cmd->buttons |= IN_ATTACK;
			}
		}
	}
}