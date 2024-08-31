#pragma once

#include "main.h"

#define TIME_TO_TICKS( dt )	( (int)( 0.5f + (float)(dt) / engine->globals->interval_per_tick ) )

class Cheat {
public:
	// cheat variables
	int scrW, scrH;
	char *sendPacket;
	CUserCmd *cmd;
	CBaseEntity *localPly = 0;
	CBaseEntity *wep;
	WeaponInfo wepInfo;
	Vector oldAngs;
	Vector localPlyViewPos;
	Vector punch;
	std::vector<IMaterial *> skyTextures;
	std::vector<IMaterial *> worldTextures;
	std::vector<IMaterial *> armTextures;

	//void fontThink() {
	//	static int wLast = 0, hLast = 0;
	//	
	//	if( wLast != scrW && hLast != scrH )
	//		draw->setupFonts();
	//	
	//	wLast = scrW;
	//	hLast = scrH;
	//}

	Vector getLocalHeadPos() {
		static Vector add(0);
		static int last_tick = 0;
		
		if( cmd->tick_count != last_tick )
			add = Vector(0);
		else
			return localPly->getHeadPos() + add;
	
		last_tick = cmd->tick_count;
	
		int i = 1;
		
		if( GetAsyncKeyState('F') && vars->speed )
			i += 10;
	
		Vector vel = localPly->getVelocity();
	
		float len;
	
		Vector forward = cmd->viewangles.Forward() * cmd->move.x;
		forward.z = 0;
	
		Vector right = cmd->viewangles.Right() * cmd->move.y;
		right.z = 0;
	
		Vector dir = forward + right;
	
		len = dir.Length();
		
		if( len )
			dir /= len;
		
		static Vector last(0);
		
		Vector accel = vel - last;
		
		len = accel.Length();
		
		if( len ) {
			accel /= len;
			accel = dir;
			accel *= len;
		}
		
		last = vel;
		
		float speed = 215;
		
		while( i-- ) {
			len = vel.Length();
		
			if( len && len <= speed ) {
				vel /= len;
				vel += accel * 0.015625;
				vel *= len;
		
				len = vel.Length();
		
				if( len && len > speed ) {
					vel /= len;
					len = speed;
					vel *= len;
				}
			}
		
			add += vel * 0.015625;
		}
		
		return localPly->getHeadPos() + add;
	}

	//Vector getLocalHeadPos() {
	//	if( !localPly )
	//		return Vector( 0 );
	//
	//	Vector vel = localPly->getVelocity();
	//	
	//	Vector forward = cmd->viewangles.Forward() * cmd->move.x;
	//	forward.z = 0;
	//	
	//	Vector right = cmd->viewangles.Right() * cmd->move.y;
	//	right.z = 0;
	//	
	//	Vector dir = forward + right;
	//	
	//	float len = dir.Length();
	//	if( len != 0 )
	//		dir /= len;
	//
	//	static Vector last(0);
	//
	//	Vector accel = vel - last;
	//	
	//	len = accel.Length();
	//	
	//	if( len ){
	//		accel /= len;
	//		accel = dir;
	//		accel *= len;
	//	}
	//	
	//	last = vel;
	//	
	//	vel += accel;
	//	vel *= engine->globals->interval_per_tick;
	//
	//	return localPly->getHeadPos() + vel;
	//}

	bool invalidWep() {
		if( !wep )
			return false;

		int id = wep->getWeaponID();
		if( id == weapon_knife_ct 
			|| id == weapon_knife_t
			|| id == weapon_c4
			|| id == weapon_flashbang
			|| id == weapon_hegrenade
			|| id == weapon_incgrenade
			|| id == weapon_decoy
			|| id == weapon_smokegrenade
			|| id == weapon_molotov
			|| id == weapon_bayonet
			|| id == weapon_falchion
			|| id == weapon_butterfly
			|| id == weapon_karambit
			|| id == weapon_m9bayonet)
			return true;

		return false;
	}

	bool scopedWep() {
		if( !wep )
			return false;

		int id = wep->getWeaponID();
		if( id == weapon_g3sg1 
			|| id == weapon_scar20
			|| id == weapon_awp 
			|| id == weapon_aug 
			|| id == weapon_sg553
			|| id == weapon_ssg08)
			return true;

		return false;
	}
	
	void matThink() {
		for( int i = 0; i < skyTextures.size(); i++ ) {
			if( vars->noSky )
				skyTextures[i]->SetColor( 0, 0, 0 );
			else
				skyTextures[i]->SetColor( 1, 1, 1 );
		}

		for( int i = 0; i < worldTextures.size(); i++ ) {
			if( vars->asusWalls )
				worldTextures[i]->SetAlpha( 0.6 );
			else
				worldTextures[i]->SetAlpha( 1 );
		}
		
		for( int i = 0; i < armTextures.size(); i++ ) {
			if( vars->noHands )
				armTextures[i]->SetVarFlag( MATERIAL_VAR_WIREFRAME, true );
			else
				armTextures[i]->SetVarFlag( MATERIAL_VAR_WIREFRAME, false );
		}
	}

	void prediction() {
		//if( !localPly )
		//	return;
		//
		//static int lastTick = 0;
		//
		//if( cmd->tick_count != lastTick ) {
		//	gameMovement->origin	= localPly->GetAbsOrigin();
		//	gameMovement->velocity	= localPly->getVelocity();
		//	gameMovement->onground	= localPly->getFlags() & 1;
		//}
		//
		//lastTick = cmd->tick_count;
		//
		//gameMovement->ProcessMovement( localPly, cmd );
		//
		//localPlyViewPos = gameMovement->origin + localPly->getVecViewOffset();
		//oldAngs = cmd->viewangles;
		//
		//if( wep )
		//	wep->UpdateAccuracyPenalty();

		if( !engine->moveHelper || !localPly )
			return;
		
		*(CBaseEntity **)( (DWORD)engine->gameMovement + 0x4 ) = localPly;
		
		void *data = *(void **)( (DWORD)engine->gameMovement + 0x8 );
		if( !data )
			return;
		
		float back = engine->globals->frametime;
		engine->globals->frametime = engine->globals->interval_per_tick;
		
		engine->SetHost( localPly );
		
		engine->SetupMove( localPly, cmd, data );
		engine->ProcessMovement( localPly, data );
		engine->FinishMove( localPly, cmd, data );
		
		engine->SetHost( 0 );
		
		localPlyViewPos = localPly->getHeadPos();
		oldAngs = cmd->viewangles;

		if( wep )
			wep->UpdateAccuracyPenalty();
		
		engine->globals->frametime = back;
	}

	bool canFire() {
		if( !wep )
			return false;

		if( wep->getWeaponClip() <= 0 )
			return false;

		float serverTime = localPly->getTickBase() * engine->globals->interval_per_tick;

		if( localPly->getNextAttack() > serverTime )
			return false;

		if( wep->getNextPrimaryAttack() > serverTime )
			return false;

		return true;
	}

	inline Vector getSpread( int seed ) {
		RandomSeed( seed );

		float a = RandomFloat( 0, pi * 2 );
		float b = RandomFloat( 0, wep->GetInnacuracy() );
		float c = RandomFloat( 0, pi * 2 );
		float d = RandomFloat( 0, wep->GetSpread() );

		float sa, sb, ca, cb; // yeah im a cb
		SinCos( a, sa, ca );
		SinCos( c, sb, cb );

		return Vector( ca * b + cb * d, sa * b + sb * d, 0 );
	}

	void doWavRoll( Vector dir ) {
		Vector forward( 1, -dir.x, dir.y );

		Vector up( 0, -dir.x, abs(dir.y + (1 / dir.y) + (1 / dir.y)) );

		if( dir.x > 0 && dir.y < 0 )
			up.y = abs( up.y );
		else if( dir.x < 0 && dir.y < 0 )
			up.y = -abs( up.y );

		Vector left = up.Cross( forward );

		float roll = deg( atan2f(left.z, (left.y * forward.x) - (left.x * forward.y)) );

		cmd->viewangles.z += roll;
	}

	inline void noSpread() {
		Vector spread = getSpread( (MD5_PseudoRandom(cmd->command_number) & 255) + 1 ) * -1;
		if( !spread )
			return;

		Vector ang = cmd->viewangles;

		Vector dir = ang.Forward() + ang.Right() * spread.x + ang.Up() * spread.y;

		cmd->viewangles = dir.Angle( &ang.Up() );

		doWavRoll( spread );
	}

	void firedBullet() {
		if( !wep || invalidWep() )
			return;

		if( !(cmd->buttons & IN_ATTACK) )
			return;

		if( !canFire() ) {
			cmd->buttons &= ~IN_ATTACK;
			return;
		}

		if( vars->noSpread && !vars->antiUntrust )
			noSpread();

		if( vars->rcs == 2 ) {
			engine->DecayPunchAngle();
			cmd->viewangles -= localPly->getPunch() * 2;
		}
		
		if( vars->pSilent )
			*sendPacket = 0;

		//int fireTicks = (int)( 0.5 + engine->wepInfo.cycleTime / engine->globals->interval_per_tick );
		//
		//static int ticks = 0;
		//if( ticks ) {
		//	engine->cmd->buttons &= ~IN_ATTACK;
		//	ticks--;
		//}
		//
		//if( engine->cmd->buttons & IN_ATTACK && fireTicks != -1 )
		//	ticks = fireTicks;
		//if( cmd->buttons & IN_ATTACK ) {
		//	if( !cheat->canFire() )
		//		engine->cmd->buttons &= ~IN_ATTACK;
		//
		//	if( vars->pSilent && cheat->canFire() )
		//		*engine->sendPacket = 0;
		//}
		//static int ticks = 0;
		//if( ticks ) {
		//	engine->cmd->buttons &= ~IN_ATTACK;
		//	ticks--;
		//}
		//
		//if( engine->cmd->buttons & IN_ATTACK && fireTicks != -1 )
		//	ticks = fireTicks;
	}

	void aimAA() {
		if( (cmd->buttons & IN_USE) || localPly->GetMoveType() == MOVETYPE_LADDER )
			return;

		float len, closest = 8192;
		Vector pos;
		for( int i = 1; i <= engine->globals->maxClients; i++ ) {
			CBaseEntity *ent = engine->GetClientEntity( i );
			if( !ent || ent == localPly )
				continue;

			if( ent->IsDormant() )
				continue;

			if( ent->getHealth() <= 0 )
				continue;

			if( ent->getColor().a < 250 )
				continue;

			if( (ent->getTeam() == localPly->getTeam()) && vars->ignoreTeam )
				continue;

			pos = ent->getHeadPos();
			len = (localPlyViewPos - pos).Length();
			if( len > closest )
				continue;

			closest = len;
		}

		cmd->viewangles.y = (pos - localPlyViewPos).Angle().y;
	}

	void edgeAA() {
		if( (cmd->buttons & IN_USE) || localPly->GetMoveType() == MOVETYPE_LADDER )
			return;

		CTraceFilter filt;
		filt.pSkip = localPly;

		bool edge = false;

		Vector ang;
		Vector eyePos = localPlyViewPos;

		for( int y = 0; y < 360; y++ ) {
			Vector tmp( 10, cmd->viewangles.y, 0 );
			tmp.y += y;

			Vector forward = tmp.Forward();
			
			float len = ( (16 * cosf(rad(10)) * 2) + 7 ); // 16
			forward *= len;

			Ray_t ray;
			CGameTrace tr;

			ray.init( eyePos, (eyePos + forward) );
			engine->TraceRay( ray, filt, tr, true );
			
			if( tr.fraction != 1 ) {
				Vector negate = tr.plane.normal;
				negate *= -1;

				Vector angles = negate.Angle();
				tmp.y = angles.y;

				CGameTrace leftTrace, rightTrace;

				Vector left = (tmp + Vector(0, 45, 0)).Forward(); // or 45
				Vector right = (tmp - Vector(0, 45, 0)).Forward();

				left *= (len * cosf(rad(30)) * 2); //left *= (len * cosf(rad(30)) * 2);
                right *= (len * cosf(rad(30)) * 2); // right *= (len * cosf(rad(30)) * 2);
				
				ray.init( eyePos, (eyePos + left) );
				engine->TraceRay( ray, filt, leftTrace, true );
				
				ray.init( eyePos, (eyePos + right) );
				engine->TraceRay( ray, filt, rightTrace, true );

				if ((leftTrace.fraction == 1)
					&& (rightTrace.fraction != 1))
				{
					tmp.y -= 45; // 45 / 90
				}
				else if ((leftTrace.fraction != 1)
					&& (rightTrace.fraction == 1))
				{
					tmp.y += 45; // 45 / 90
				}

				ang.y = tmp.y;
				edge = true;
			}
		}

		static int wait = 4;

		if( edge ) {
			if( vars->edgeAA == 1 ) { // += 360 = out, -= 360 = in, test 180 / 360, might be the other way around
				cmd->viewangles.y = ang.y;
				cmd->viewangles.y += 360;
			}else if ( vars->edgeAA == 2 ) {
				if( wait ) {
					wait--;
					*sendPacket = 0;
					cmd->viewangles.y = ang.y;
					cmd->viewangles.y += 180;
				}else{
					wait = 4;
					*sendPacket = 1;
					cmd->viewangles.y = ang.y;
				}

				/*
				static bool swap = false;
				if( swap ) {
					cmd->viewangles.y = ang.y;
					cmd->viewangles.y -= 360;
					holdCmds();
				}else{
					cmd->viewangles.y = ang.y;
					cmd->viewangles.y -= 180;
				}
				
				swap = !swap;
				*/
			}
		}
	}

	void antiAim() {
		if( (cmd->buttons & IN_USE) || localPly->GetMoveType() == MOVETYPE_LADDER )
			return;

		if (vars->aa)
		{

		}
	}

	void spinBot() {
		if( (cmd->buttons & IN_USE) || localPly->GetMoveType() == MOVETYPE_LADDER )
			return;
	
		static int y = -179;
		y += vars->spinBotSpeed;

		if( y >= 179 )
			y = -179;
	
		cmd->viewangles.y = y;
	}

	// //if( !vars->noSpread )
	//cmd->move = (cmd->move.Angle() + (Vector(0, cmd->viewangles.y) - Vector(0, engine->oldAngs.y))).Forward() * cmd->move.Length();
	void fixMovement() {
		float len = cmd->move.Length();
	
		if( cmd->viewangles != oldAngs && len ) {
			Vector dt = cmd->move.Angle();
			dt.y += cmd->viewangles.y - oldAngs.y;

			Vector move = dt.Forward() * len;

			if( !vars->antiUntrust && vars->aa ) {
				if( cmd->viewangles.x > 90 || cmd->viewangles.x < -90 )
					move.x = -move.x;

				cmd->move = move;
			}else
				cmd->move = move;
		}
	}
}; extern Cheat *cheat;