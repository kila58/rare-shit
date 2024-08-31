#include "main.h"

void hk_PaintTraverse( unsigned int vPanel, bool repaint, bool force ) {
	engine->PaintTraverse( vPanel, repaint, force );
	
	const char *panel = engine->GetName( vPanel );
	if( panel[0] == 'F' && panel[5] == 'O' ) {
		static int call = 0;
		
		call++;
		if( call % 2 )
			return;

		engine->GetScreenSize( cheat->scrW, cheat->scrH );

		menu->think();
		esp();

		if( !vars->antiUntrust ) {
			int h, m;
			char c;
			char t[ 24 ];
			
			time_t ti = time( 0 );
			tm *now = localtime( &ti );

			h = now->tm_hour;
			m = now->tm_min;

			if( h > 12 ) {
				h -= 12;
				c = 'P';
			}else
				c = 'A';

			if( m < 9 )
				sprintf_s( t, "%i:%02d %cM", h, m, c );
			else
				sprintf_s( t, "%i:%i %cM", h, m, c );

			static std::vector<Color> flash = { Color(145, 255, 0, 255), Color(0, 255, 0, 255), Color(50, 255, 50, 255), Color(150, 255, 150, 255) };
			static Color cur = Color();
			
			static int wait = 0;
			wait++;
			if( wait >= 10 ) {
				srand( time(0) );
				cur = flash[ rand() % flash.size() ];
				wait = 0;
			}
			
			draw->drawText( draw->font2, cheat->scrW * 0.5, cheat->scrH * 0.1, true, cur, "$ nabeFramework CSGO $" );
			draw->drawText( draw->font2, cheat->scrW * 0.5, cheat->scrH * 0.13, true, cur, "%s", t );
		}
	}
}

void hk_RunCommand( CBaseEntity *ent, CUserCmd *cmd, void *moveHelper ) {
	engine->moveHelper = moveHelper;

	static int lastTick = 0;

	if( GetAsyncKeyState('F') && cmd->tick_count == lastTick )
		cheat->localPly->getTickBase()--;

	lastTick = cmd->tick_count;

	engine->RunCommand( ent, cmd, moveHelper );
}

bool hk_CreateMove( float frametime, CUserCmd *cmd ) {
	if( !cmd->command_number )
		return true;

	cheat->localPly = engine->GetClientEntity( engine->GetLocalPlayer() );
	if( !cheat->localPly )
		return true;
	void *basePtr, *inputBaseptr, *clientBaseptr;
	__asm mov basePtr, ebp;
	inputBaseptr = (void *)basePtr;
	clientBaseptr = **(void ***)basePtr;

	cheat->sendPacket = *(char **)inputBaseptr - 0x1C;

	cheat->wep = engine->GetClientEntity( cheat->localPly->getActiveWeapon(), true );
	if( !cheat->wep )
		return true;

	if( !cheat->wep->GetWeaponData(cheat->wepInfo) )
		return true;

	static int loop = 0;

	cheat->cmd = cmd;
	cheat->prediction();

	if( vars->aa )
		cheat->antiAim();

	if( vars->spinBot )
		cheat->spinBot();

	if( vars->aimAA )
		cheat->aimAA();

	if( vars->edgeAA )
		cheat->edgeAA();

	if( (cmd->buttons & IN_ATTACK) || vars->autoShoot )
		aimbot();

	cheat->firedBullet();

	if( vars->fakeLag ) {
		static int fakelagTick = 0;
		fakelagTick++;

		if( fakelagTick < vars->fakeLagFactor )
			*cheat->sendPacket = 1;
		else 
			*cheat->sendPacket = 0;

		if( fakelagTick > 15 )
			fakelagTick = 0;
	}

	cheat->fixMovement();

	if( vars->antiUntrust )
		cmd->viewangles.clampAngles();

	cmd->move.clampMove();

	return false;
}

void hk_OverrideView( CViewSetup *setup ) {
	if( !setup || !cheat->localPly )
		return;

	setup->fov += vars->visualFov;

	if( vars->visNoRecoil && cheat->localPly->getHealth() > 0 )
		setup->angles -= cheat->localPly->getViewPunch() + (cheat->localPly->getPunch() * 2) * 0.45;

	engine->OverrideView( setup );
}

IMaterial *hk_FindMaterial( const char *mat, const char *group, bool complain, void *prefix ) {
	IMaterial *ret = engine->oFindMaterial( engine->material, mat, group, complain, prefix );

	if( strstr(mat, "arms") )
		cheat->armTextures.push_back( ret );
	
	if( group[0] == 'S' && group[1] == 'k' && group[2] == 'y' )
		cheat->skyTextures.push_back( ret );
	
	if( group[0] == 'W' && group[1] == 'o' && group[6] == 't' )
		cheat->worldTextures.push_back( ret );
	
	return ret;
}

void hk_SceneEnd() {
	engine->SceneEnd();

	cheat->matThink();

	if( vars->chams ) {
		IMaterial *mat = engine->FindMaterial( "vgui/white_additive" );
		//mat->SetVarFlag( MATERIAL_VAR_TRANSLUCENT, false );
		//mat->SetVarFlag( MATERIAL_VAR_ALPHATEST, false );
		mat->SetVarFlag( MATERIAL_VAR_ADDITIVE, false );
		mat->SetVarFlag( MATERIAL_VAR_VERTEXCOLOR, false );
		mat->SetVarFlag( MATERIAL_VAR_VERTEXALPHA, false );
		mat->SetVarFlag( MATERIAL_VAR_NOFOG, true );
		mat->AddReference();
		
		if( !mat )
			return;
		
		engine->MaterialOverride( mat );

		for( int i = 1; i <= engine->globals->maxClients; i++ ) {
			CBaseEntity *ent = engine->GetClientEntity( i );
			if( !ent || ent == cheat->localPly )
				continue;
		
			if( ent->IsDormant() )
				continue;
		
			if( ent->getHealth() <= 0 )
				continue;

			mat->SetVarFlag( MATERIAL_VAR_IGNOREZ, true );

			if( ent->getTeam() == cheat->localPly->getTeam() || !menu->list.empty() && menu->list[i].friendly ) 
				engine->SetColor( 26, 188, 156 );
			else
				engine->SetColor( 241, 196, 15 );

			ent->DrawModel();

			mat->SetVarFlag( MATERIAL_VAR_IGNOREZ, false );

			if( ent->getTeam() == cheat->localPly->getTeam() || !menu->list.empty() && menu->list[i].friendly ) 
				engine->SetColor( 52, 152, 219 );
			else
				engine->SetColor( 231, 76, 60 );

			ent->DrawModel();
		}
	}

	engine->MaterialOverride( 0 );
}

void __cdecl aaaX( const CRecvProxyData *pData, void *pStruct, void *pOut ) {
	if( !pData )
		return;

	float pitch = pData->m_Value.m_Float;

	if( menu->list.empty() )
		return;

	if( menu->list[0].x > 0 ) {
		if( menu->list[0].x == 1 ) {
				if( pitch < -89 )
					pitch = -89;
				else if( pitch > 89 )
					pitch = 89;
			}else if( menu->list[0].x == 2 ) {
				if( pitch <= 88.945313 && pitch >= -180 )
					pitch = -89;
				else if( pitch >= 88.945313 && pitch <= 180 )
					pitch = 89;
			}else if( menu->list[0].x == 3 )
				pitch = 90;
			else if( menu->list[0].x == 4 )
				pitch = -90;
			else if( menu->list[0].x == 5 ) {
				pitch -= 0.087929;

				if( pitch > 180 )
					pitch -= 360;

				if( pitch < -90 )
					pitch = -90;
				else if( pitch > 90 )
					pitch = 90;

				static bool last[ 128 ];
				bool tmp = last[((CBaseEntity *)pStruct)->GetIndex()];
				last[((CBaseEntity *)pStruct)->GetIndex()] = (pitch = 90);
				
				if( pitch == -90 )
					if( tmp )
						pitch = 90;
		}
	}else {
		if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].x == 1 ) {
			if( pitch < -89 )
				pitch = -89;
			else if( pitch > 89 )
				pitch = 89;
		}else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].x == 2 ) {
			if( pitch <= 88.945313 && pitch >= -180 )
				pitch = -89;
			else if( pitch >= 88.945313 && pitch <= 180 )
				pitch = 89;
		}else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].x == 3 )
			pitch = 90;
		else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].x == 4 )
			pitch = -90;
		else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].x == 5 ) {
			pitch -= 0.087929;

			if( pitch > 180 )
				pitch -= 360;

			if( pitch < -90 )
				pitch = -90;
			else if( pitch > 90 )
				pitch = 90;

			static bool last[ 128 ];
			bool tmp = last[((CBaseEntity *)pStruct)->GetIndex()];
			last[((CBaseEntity *)pStruct)->GetIndex()] = (pitch = 90);
			
			if( pitch == -90 )
				if( tmp )
					pitch = 90;
		}
	}

	*(float *)pOut = pitch;
}

void __cdecl aaaY( const CRecvProxyData *pData, void *pStruct, void *pOut ) {
	if( !pData )
		return;

	float yaw = pData->m_Value.m_Float;

	if( menu->list.empty() )
		return;

	if( menu->list[0].y > 0 ) { // all
		if( menu->list[0].y == 1 ) {
				if( yaw < -180 )
					yaw += 360;
				else if( yaw > 180 )
					yaw -= 360;
			}else if( menu->list[0].y == 2 ) {
				if( yaw > 180 && yaw < -180 )
					yaw = 90;
			}else if( menu->list[0].y == 3 )
				yaw -= 45;
			else if( menu->list[0].y == 4 )
				yaw += 45;
			else if( menu->list[0].y == 5 )
				yaw -= 90;
			else if( menu->list[0].y == 6 )
				yaw += 90;
			else if( menu->list[0].y == 7 )
				yaw -= 135;
			else if( menu->list[0].y == 8 )
				yaw += 135;
			else if( menu->list[0].y == 9 )
				yaw -= 180;
			else if( menu->list[0].y == 10 ) {
				yaw -= 0.087929;
				static bool last[ 128 ];
				bool tmp = last[((CBaseEntity *)pStruct)->GetIndex()];
				last[((CBaseEntity *)pStruct)->GetIndex()] = (yaw >= 180 && yaw <= 360);

				if( tmp && (yaw >= 0 && yaw <= 180) )
					yaw += 359;

				yaw -= (int)(yaw / 360) * 360;
				if( yaw < -180 )
					yaw += 360;
				else if( yaw > 180 )
					yaw -= 360;
			}
	}else { // specific
		if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 1 ) {
				if( yaw < -180 )
					yaw += 360;
				else if( yaw > 180 )
					yaw -= 360;
			}else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 2 ) {
				if( yaw > 180 && yaw < -180 )
					yaw = 90;
			}else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 3 )
				yaw -= 45;
			else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 4 )
				yaw += 45;
			else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 5 )
				yaw -= 90;
			else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 6 )
				yaw += 90;
			else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 7 )
				yaw -= 135;
			else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 8 )
				yaw += 135;
			else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 9 )
				yaw -= 180;
			else if( menu->list[((CBaseEntity *)pStruct)->GetIndex()].y == 10 ) {
				static bool last[ 128 ];
	
				bool tmp = last[ ((CBaseEntity *)pStruct)->GetIndex() ];
				
				last[ ((CBaseEntity *)pStruct)->GetIndex() ] = ( yaw >= 180 && yaw <= 360 );
				
				yaw -= (int)( yaw / 360 ) * 360;
				if( tmp && (yaw >= 0 && yaw <= 180) )
					yaw += 360;
				
				if( yaw < -180 )
					yaw += 360;
				else if( yaw > 180 )
					yaw -= 360;
			}
	}

	*(float *)pOut = yaw;
}

void init() {
	//vmtHook panelVmt( engine->panel );
	//vmtHook predictionVmt( engine->prediction );
	//vmtHook clientModeVmt( engine->clientMode );
	////vmtHook materialVmt( engine->material );
	//vmtHook renderViewVmt( engine->renderView );

	auto *pPanelHook = new CVMTHookManager((PDWORD*)engine->panel);
	auto *pCreateMove = new CVMTHookManager((PDWORD*)engine->clientMode);
	auto *pSceneEnd = new CVMTHookManager((PDWORD*)engine->renderView);
	auto *pRunCommand = new CVMTHookManager((PDWORD*)engine->prediction);

	engine->oPaintTraverse = (PaintTraverseFn)pPanelHook->dwHookMethod((DWORD)hk_PaintTraverse, 41);
	engine->oRunCommand = (RunCommandFn)pRunCommand->dwHookMethod((DWORD)hk_RunCommand, 19);
	pCreateMove->dwHookMethod((DWORD)hk_CreateMove, 24);
	engine->oOverrideView = (OverrideViewFn)pCreateMove->dwHookMethod((DWORD)hk_OverrideView, 18);
	engine->oSceneEnd = (SceneEndFn)pSceneEnd->dwHookMethod((DWORD)hk_SceneEnd, 9);
	//engine->oPaintTraverse = (PaintTraverseFn)panelVmt.hookVirtual( 41, hk_PaintTraverse );
	//engine->oRunCommand = (RunCommandFn)predictionVmt.hookVirtual( 19, hk_RunCommand );
	//clientModeVmt.hookVirtual( 24, hk_CreateMove );
	//engine->oOverrideView = (OverrideViewFn)clientModeVmt.hookVirtual( 18, hk_OverrideView );
	////engine->oFindMaterial = (FindMaterialFn)materialVmt.hookVirtual( 84, hk_FindMaterial );
	//engine->oSceneEnd = (SceneEndFn)renderViewVmt.hookVirtual( 9, hk_SceneEnd );

	netvars->dumpNetvars();
	netvars->hookProp( "DT_CSPlayer", "m_angEyeAngles[0]", aaaX );
	netvars->hookProp( "DT_CSPlayer", "m_angEyeAngles[1]", aaaY );

	msg( "Loaded - %s. Shoutouts to: Me\n", __DATE__ );
}

int __stdcall DllMain( HINSTANCE inst, DWORD reason, LPVOID reserved ) {
	if( reason == DLL_PROCESS_ATTACH ) {
		DisableThreadLibraryCalls( inst );
		CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)init, 0, 0, 0 );
	}

	//TerminateThread( init, 0 );

	return 1;
}