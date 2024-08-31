#pragma once

#include "main.h"

// https://github.com/LestaD/SourceEngine2007/blob/43a5c90a5ada1e69ca044595383be67f40b33c61/se2007/game/server/cstrike/cs_player.cpp#L1669
// https://github.com/LestaD/SourceEngine2007/blob/43a5c90a5ada1e69ca044595383be67f40b33c61/src_main/game/shared/cstrike/cs_player_shared.cpp#L312

inline float hitgroupMult( int hitGroup ) {
	if( hitGroup == 1 )
		return 4.0;

	if( hitGroup == 3 )
		return 1.25;

	if( hitGroup == 6 || hitGroup == 7 )
		return 0.75;

	return 1.0;
}

inline void scaleDamage( int hitGroup, CBaseEntity *ent, float &damage ) {
	if( !ent )
		return;

	damage *= hitgroupMult( hitGroup );
	
	if( ent->getArmor() > 0 ) {
		if( hitGroup == 1 ) { // or > 0?
			if( ent->hasHelmet() )
				damage *= (cheat->wepInfo.ratio * 0.5);
		}
		else
			damage *= (cheat->wepInfo.ratio * 0.5);
	}
}

// ++ or 4? ~sometimes~ messes up // * ( 24 * len )
inline bool traceToExit( Vector &start, Vector dt ) {
	float len = 0;

	Vector pos = start;
	while( len += 4 <= 90 ) {
		start = pos + dt * len;			

		if( !engine->GetPointContents(start) )
			return true;
	}

	return false;
}

inline bool isVisible( CBaseEntity *ent, Vector pos ) {
	if( !ent || !cheat->localPly )
		return false;

	Ray_t ray;
	CGameTrace tr;
	CTraceFilter filt;
	filt.pSkip = cheat->localPly;
	filt.pSkip2 = ent;
	
	ray.init( cheat->localPlyViewPos, pos );
	
	engine->TraceRay( ray, filt, tr );
	
	if( tr.fraction == 1 || tr.m_pEnt == ent )
		return true;
	
	if( vars->autoWall ) {
		Vector dt = pos - cheat->localPlyViewPos;
		Vector start = tr.endPos;
		
		int wall = cheat->wepInfo.pen;
		float damage = cheat->wepInfo.damage;
		
		CGameTrace exit;
		
		while( wall ) {
			start = tr.endPos;
	
			if( !traceToExit(start, dt / dt.Length()) )
				return false;
	
			ray.init( start, tr.endPos );
			engine->TraceRay( ray, filt, exit );
	
			surfacedata_t *data;
			if( !(data = engine->GetSurfaceData(tr.props)) )
				return false;

			float mod = *(float *)( (DWORD)data + 0x4C );
	
			damage -= ( (exit.endPos - tr.endPos).Length() / mod );
			//scaleDamage( tr.hitgroup, tr.m_pEnt, damage );

			if( damage <= vars->autoWallMinDamage )
				return false;

			ray.init( exit.endPos, pos );
			engine->TraceRay( ray, filt, tr );
	
			if( tr.fraction == 1 ) // end of trace
				return true;
	
			wall--;
		}
	}
	
	return false;
}

inline bool getHitbox( CBaseEntity *ent, int num, Vector &out ) {
	matrix3x4_t matrix[ 128 ];
	if( !ent->SetupBones(matrix) )
		return false;

	studiohdr_t *stdHdr = engine->GetStudiomodel( ent->GetModel() );
	if( !stdHdr )
		return false;

	mstudiobbox_t *hitbox = stdHdr->GetHitbox( num );
	if( !hitbox )
		return false;

	Vector min, max;
	VectorTransform( hitbox->min, matrix[hitbox->bone], min );
	VectorTransform( hitbox->max, matrix[hitbox->bone], max );
	out = ( min + max ) * 0.5;

	if( isVisible(ent, out) ) {
		return true;
	}else if( vars->hitScan == 1 ) {
		for( int i = 0; i < 18; i++ ) {
			//if( (i == 3 || i == 6 || i == 14 || i == 17) && !vars->noSpread )
			//	continue;
			
			hitbox = stdHdr->GetHitbox( i );
			if( !hitbox )
				continue;
			
			VectorTransform( hitbox->min, matrix[hitbox->bone], min );
			VectorTransform( hitbox->max, matrix[hitbox->bone], max );
			out = ( min + max ) * 0.5;

			if( isVisible(ent, out) )
				return true;
		}
	}else if( vars->hitScan == 2 ) { // 'extreme', but more so for mm-esque hvh
		for( int i = 0; i < 18; i++ ) {
			hitbox = stdHdr->GetHitbox( i );
			if( !hitbox )
				continue;
			
			Vector corners[17] = {
				Vector( (hitbox->min + hitbox->max) * 0.5 ),
				Vector( hitbox->max.x - 1.65, hitbox->max.y - 1.65, hitbox->min.z + 1.65 ),
				Vector( hitbox->max.x - 1.65, hitbox->max.y - 1.65, hitbox->max.z - 1.65 ),
				Vector( hitbox->min.x + 1.65, hitbox->max.y - 1.65, hitbox->min.z + 1.65 ),
				Vector( hitbox->min.x + 1.65, hitbox->max.y - 1.65, hitbox->max.z - 1.65 ),
				Vector( hitbox->max.x - 1.65, hitbox->min.y + 1.65, hitbox->min.z + 1.65 ),
				Vector( hitbox->max.x - 1.65, hitbox->min.y + 1.65, hitbox->max.z - 1.65 ),
				Vector( hitbox->min.x + 1.65, hitbox->min.y + 1.65, hitbox->min.z + 1.65 ),
				Vector( hitbox->min.x + 1.65, hitbox->min.y + 1.65, hitbox->max.z - 1.65 ),
				Vector( hitbox->min.x, hitbox->min.y, hitbox->min.z ),
				Vector( hitbox->min.x, hitbox->min.y, hitbox->max.z ),
				Vector( hitbox->min.x, hitbox->max.y, hitbox->min.z ),
				Vector( hitbox->min.x, hitbox->max.y, hitbox->max.z ),
				Vector( hitbox->max.x, hitbox->min.y, hitbox->min.z ),
				Vector( hitbox->max.x, hitbox->min.y, hitbox->max.z ),
				Vector( hitbox->max.x, hitbox->max.y, hitbox->min.z ),
				Vector( hitbox->max.x, hitbox->max.y, hitbox->max.z )
			};
			
			//if( vars->hitScan == 2 ) {
			//	for( int j = 0; j < 9; j++ )
			//		VectorTransform( corners[j], matrix[hitbox->bone], out );
			//}else if ( vars->hitScan == 3 ) {
			for( int j = 0; j < 17; j++ ) {
				if( !corners[j] )
					continue;

				VectorTransform( corners[j], matrix[hitbox->bone], out );
			}
			//}
	
			if( isVisible(ent, out) )
				return true;
		}
	}

	return false;
}

Vector getHitboxPos() {
	int hitbox = vars->hitbox;
	float len, dist, closest = 8192;
	Vector out, hbox;

	float fov = (float)(vars->fov + 90);
	float radian_fov = sin(rad(fov));

	for( int i = 1; i <= engine->globals->maxClients; i++ ) {
		CBaseEntity *ent = engine->GetClientEntity( i );
		if( !ent || ent == cheat->localPly )
			continue;

		if( ent->IsDormant() )
			continue;

		if( ent->getHealth() <= 0 )
			continue;

		if( ent->getColor().a < 250 )
			continue;

		if( (ent->getTeam() == cheat->localPly->getTeam()) && vars->ignoreTeam )
			continue;

		if( !menu->list.empty() && menu->list[i].friendly )
			continue;

		if( !menu->list.empty() && menu->list[i].body )
			hitbox = 8;

		if( cheat->localPly->shotsFired() >= 3 && vars->smartAim )
			hitbox = 8;

		if( !getHitbox(ent, hitbox, hbox) )
			continue;

		if( !menu->list.empty() && menu->list[i].rage ) {
			out = hbox;
			break;
		}

		if( vars->fov && (!vars->aa && !vars->spinBot && !vars->edgeAA) ) {
			Vector dir = (hbox - cheat->localPlyViewPos);
			len = dir.Length();

			if( len ) {
				dir /= len;
				if( dir.Dot(cheat->cmd->viewangles.Forward()) < radian_fov )
					continue;
			}

			//angle = (hbox - cheat->localPlyViewPos).Angle();
			////angle.clampAngles();
			//
			//if( (angle - cheat->cmd->viewangles).Length() >= vars->fov )
			//	continue;
		}

		dist = (cheat->localPlyViewPos - hbox).Length();
		if( dist > closest )
			continue;

		if( cheat->wep ) {
			if( dist > 183 && cheat->wep->getWeaponID() == weapon_taser )
				continue;
		}

		closest = dist;
		out = hbox;
	}

	return out;
}

bool autoShoot() {
	if( !cheat->wep || !cheat->localPly )
		return false;

	if( cheat->wep->getWeaponClip() <= 0 )
		return false;

	if( vars->stopMovement ) {
		if( cheat->scopedWep() && !cheat->localPly->isScoped() )
			cheat->cmd->buttons |= IN_ATTACK2;

		float vel = cheat->localPly->getVelocity().Length();

		if( vel <= 60 ) // 70
			cheat->cmd->move *= 0.15;
		else {
			cheat->cmd->move.x = -cheat->cmd->move.x;
			cheat->cmd->move.y = -cheat->cmd->move.y;
		}
		
		cheat->cmd->buttons |= IN_DUCK;

		cheat->cmd->buttons &= ~IN_JUMP;
		cheat->cmd->buttons &= ~IN_FORWARD;
		cheat->cmd->buttons &= ~IN_BACK;
		cheat->cmd->buttons &= ~IN_MOVELEFT;
		cheat->cmd->buttons &= ~IN_MOVERIGHT;

		if( (cheat->cmd->buttons & IN_ATTACK2) || vel > 60 )
			return false;
	}

	if( vars->hitChance ) {
		float threshold = ((100 - vars->hitChance) * 0.65) * 0.01125;

		if( cheat->wep && (threshold <= cheat->wep->GetInnacuracy()) )
			return false;
	}

	if( vars->autoShoot )
		cheat->cmd->buttons |= IN_ATTACK;

	return true;
}

void aimbot() {
	if( !vars->aimEnabled || !cheat->localPly || !cheat->wep || !cheat->cmd )
		return;

	Vector hitboxPos = getHitboxPos();
	if( !hitboxPos )
		return;

	if( !autoShoot() )
		return;

	Vector old = cheat->cmd->viewangles;

	Vector aimPos = (hitboxPos - cheat->localPlyViewPos).Angle();
	
	if( cheat->localPly->getShotsFired() > 1 && vars->rcs == 1 ) {
		engine->DecayPunchAngle();
		aimPos -= (cheat->localPly->getPunch() * 2);
	}

	Vector delta = cheat->cmd->viewangles - aimPos;

	if( vars->smooth ) // it's backwards???
		aimPos = cheat->cmd->viewangles - delta / (100 - vars->smooth);

	cheat->cmd->viewangles = aimPos;

	if( vars->silent ) {
		if( vars->pSilent && !cheat->canFire() )
			cheat->cmd->viewangles = old;
	}else
		engine->SetViewAngles( cheat->cmd->viewangles );
}