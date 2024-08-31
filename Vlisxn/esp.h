#pragma once

#include "main.h"

void esp() {
	if( !vars->espEnabled || !cheat->localPly )
		return;

	//for( int i = 1; i <= engine->globals->maxClients; i++ ) {
	//	CBaseEntity *ent = engine->GetClientEntity( i );
	//	if( !ent || ent == cheat->localPly )
	//		continue;
	//
	//	if( ent->IsDormant() )
	//		continue;
	//
	//	int hp = ent->getHealth();
	//	if( hp <= 0 )
	//		continue;
	//
	//	Color espCol = Color( 231, 76, 60, 255 );
	//	if( (ent->getTeam() == cheat->localPly->getTeam()) || menu->list[i].friendly )
	//		espCol = Color( 52, 152, 219, 255 );
	//
	//	player_info info;
	//	engine->GetPlayerInfo( i, &info );
	//
	//	Vector mins	= ent->getMins();
	//	Vector maxs	= ent->getMaxs();
	//	
	//	Vector corners[8] = {
	//		Vector( mins.x, mins.y, mins.z ),
	//		Vector( mins.x, mins.y, maxs.z ),
	//		Vector( mins.x, maxs.y, mins.z ),
	//		Vector( mins.x, maxs.y, maxs.z ),
	//		Vector( maxs.x, mins.y, mins.z ),
	//		Vector( maxs.x, mins.y, maxs.z ),
	//		Vector( maxs.x, maxs.y, mins.z ),
	//		Vector( maxs.x, maxs.y, maxs.z )
	//	};
	//	
	//	int x, y, w, h;
	//	x = cheat->scrW * 2;
	//	y = cheat->scrH * 2;
	//	w = -9999;
	//	h = -9999;
	//	
	//	matrix3x4_t matrix;
	//	matrixFromAngles( ent->GetAbsOrigin(), ent->GetAngles(), matrix );
	//
	//	Vector screenPos[8];
	//	for( int j = 0; j < 8; j++ ) {
	//		VectorTransform( corners[j], matrix, corners[j] );
	//	
	//		if( !draw->w2s(corners[j], screenPos[j]) )
	//			continue;
	//	
	//		x = min( x, screenPos[j].x );
	//		y = min( y, screenPos[j].y );
	//		w = max( w, screenPos[j].x );
	//		h = max( h, screenPos[j].y );
	//	}
	//	
	//	w -= x;
	//	h -= y;
	//
	//	if( vars->name )
	//		draw->drawText( draw->font, x + w * 0.5, y - 15, true, Color(255, 255, 255, 255), info.name );
	//
	//	if( vars->weapon ) {
	//		std::string wepName = engine->GetClientEntity( ent->getActiveWeapon(), true )->GetClientClass()->m_pNetworkName;
	//		if( !wepName.empty() ) {
	//			if( !strncmp(wepName.c_str(), "C", 1) )
	//				wepName.erase( 0, 1 );
	//	
	//			if( !strncmp(wepName.c_str(), "Weapon", 6) )
	//				wepName.erase( 0, 6 );
	//	
	//			draw->drawText( draw->font, x + w * 0.5, y + h + 1, true, Color(255, 255, 255, 255), wepName.c_str() );
	//		}
	//	}
	//
	//	if( vars->box )
	//		draw->drawEspBox( x, y, w, h, espCol );
	//
	//	if( vars->box3D )
	//		draw->draw3DEspBox( screenPos, espCol );
	//
	//	if( vars->hpBar )
	//		draw->drawHPBar( hp, x, y, h, espCol );
	//
	//	if( vars->bones )
	//		draw->drawBones( ent );
	//}

	for( int i = 1; i <= engine->GetHighestEntityIndex(); i++ ) {
		CBaseEntity *ent = engine->GetClientEntity( i );
		if( !ent || ent == cheat->localPly )
			continue;
	
		if( ent->IsDormant() )
			continue;
	
		player_info info;
		bool isPlayer = engine->GetPlayerInfo( i, &info );
		
		std::string name = "";
		if( !isPlayer ) {
			name = ent->GetClientClass()->m_pNetworkName;
			if( name.empty() )
				continue;
		}

		bool isWeapon = (name[1] == 'W' && name[2] == 'e' && name[3] == 'a') || name[3] == '4' || name[2] == 'E'; 
		bool isC4 = (name[1] == 'C' && name[2] == '4') || (name[8] == 'C' && name[9] == '4');
	
		if( !isPlayer && !isWeapon && !isC4 ) 
			continue;
	
		if( engine->GetClientEntity(ent->getOwnerEnt(), true) && isWeapon || isC4 )
			continue;
	
		Vector entPos	= ent->GetAbsOrigin();
		Vector mins		= ent->getMins();
		Vector maxs		= ent->getMaxs();

		if( (!mins || !maxs) && (isPlayer || isWeapon) )
			continue;
	
		Vector corners[8] = {
			Vector( mins.x, mins.y, mins.z ),
			Vector( mins.x, mins.y, maxs.z ),
			Vector( mins.x, maxs.y, mins.z ),
			Vector( mins.x, maxs.y, maxs.z ),
			Vector( maxs.x, mins.y, mins.z ),
			Vector( maxs.x, mins.y, maxs.z ),
			Vector( maxs.x, maxs.y, mins.z ),
			Vector( maxs.x, maxs.y, maxs.z )
		};
	
		int x, y, w, h;
		x = cheat->scrW * 2;
		y = cheat->scrH * 2;
		w = -9999;
		h = -9999;
	
		matrix3x4_t matrix;
		matrixFromAngles( entPos, ent->GetAngles(), matrix );
	
		Vector entPosScr, screenPos[8];
		if( isC4 || isWeapon ) {
			if( !draw->w2s(entPos, entPosScr) )
				continue;
		}
	
		for( int j = 0; j < 8; j++ ) {
			VectorTransform( corners[j], matrix, corners[j] );
	
			if( !draw->w2s(corners[j], screenPos[j]) )
				continue;
	
			x = min( x, screenPos[j].x );
			y = min( y, screenPos[j].y );
			w = max( w, screenPos[j].x );
			h = max( h, screenPos[j].y );
		}
		
		w -= x;
		h -= y;
	
		if( isWeapon && vars->weapons ) {
			if( !strncmp(name.c_str(), "C", 1) )
				name.erase( 0, 1 );
			
			if( !strncmp(name.c_str(), "Weapon", 6) )
				name.erase( 0, 6 );
	
			draw->draw3DEspBox( screenPos, Color( 44, 62, 80, 255 ) );
			draw->drawText( draw->font, x + w * 0.5, y - 15, true, Color(255, 255, 255, 255), name.c_str() );
		}else if( isPlayer ) {
			int hp = ent->getHealth();
			if( hp <= 0 )
				continue;
	
			Color espCol = Color( 231, 76, 60, 255 );
			if( (ent->getTeam() == cheat->localPly->getTeam()) || (!menu->list.empty() && menu->list[i].friendly) )
				espCol = Color( 52, 152, 219, 255 );
	
			if( vars->name )
				draw->drawText( draw->font, x + w * 0.5, y - 15, true, Color(255, 255, 255, 255), info.name );
	
			if( vars->weapon ) {
				CBaseEntity *activeWep = engine->GetClientEntity( ent->getActiveWeapon(), true );
				if( activeWep ) {
					std::string wepName = activeWep->GetClientClass()->m_pNetworkName;
					if( !wepName.empty() ) {
						if( !strncmp(wepName.c_str(), "C", 1) )
							wepName.erase( 0, 1 );
			
						if( !strncmp(wepName.c_str(), "Weapon", 6) )
							wepName.erase( 0, 6 );
			
						draw->drawText( draw->font, x + w * 0.5, y + h + 1, true, Color(255, 255, 255, 255), wepName.c_str() );
					}
				}
			}
	
			if( vars->box )
				draw->drawEspBox( x, y, w, h, espCol );
	
			if( vars->box3D )
				draw->draw3DEspBox( screenPos, espCol );
	
			if( vars->hpBar )
				draw->drawHPBar( hp, x, y, h, espCol );
	
			if( vars->bones )
				draw->drawBones( ent );
		}else if( isC4 ) {
			float time = ent->getC4Blow() - engine->globals->curtime;
			draw->drawText( draw->font, entPosScr.x, entPosScr.y, true, Color(255, 255, 255, 255), time >= 0 ? "C4 [ %2.1f ]" : "C4", time );
		}
	}

	//for( int i = 1; i <= engine->globals->maxClients; i++ ) {
	//	CBaseEntity *ent = engine->GetClientEntity( i );
	//	if( !ent || ent == cheat->localPly )
	//		continue;
	//
	//	if( ent->IsDormant() )
	//		continue;
	//
	//	player_info info;
	//	engine->GetPlayerInfo( i, &info );
	//
	//	Vector entPos	= ent->GetAbsOrigin();
	//	int entHP		= ent->getHealth();
	//
	//	if( entHP <= 0 )
	//		continue;
	//
	//	Color espCol = Color( 50, 50, 255, 255 );
	//	if( ent->getTeam() != cheat->localPly->getTeam() )
	//		espCol = Color( 255, 50, 50, 255 );
	//
	//	if( menu->list[i].friendly )
	//		espCol = Color( 235, 235, 235, 255 );
	//
	//	Vector mins = ent->getMins();
	//	Vector maxs = ent->getMaxs();
	//	mins += entPos;
	//	maxs += entPos;
	//
	//	Vector corners[8] = {
	//		Vector( mins.x, mins.y, mins.z ),
	//		Vector( mins.x, mins.y, maxs.z ),
	//		Vector( mins.x, maxs.y, mins.z ),
	//		Vector( mins.x, maxs.y, maxs.z ),
	//		Vector( maxs.x, mins.y, mins.z ),
	//		Vector( maxs.x, mins.y, maxs.z ),
	//		Vector( maxs.x, maxs.y, mins.z ),
	//		Vector( maxs.x, maxs.y, maxs.z )
	//	};
	//
	//	int minx, miny, maxx, maxy; // x, y, w, h
	//	minx = cheat->scrW * 2;
	//	miny = cheat->scrH * 2;
	//	maxx = -9999;
	//	maxy = -9999;
	//
	//	Vector screenPos[8];
	//	for( int i = 0; i < 8; i++ ) {
	//		if( !draw->w2s(corners[i], screenPos[i]) )
	//			continue;
	//
	//		minx = min( minx, screenPos[i].x );
	//		miny = min( miny, screenPos[i].y );
	//		maxx = max( maxx, screenPos[i].x );
	//		maxy = max( maxy, screenPos[i].y );
	//	}
	//
	//	maxx -= minx; // w
	//	maxy -= miny; // h
	//
	//	if( vars->box )
	//		draw->drawEspBox( minx, miny, maxx, maxy, espCol );
	//
	//	if( vars->box3D )
	//		draw->draw3DEspBox( screenPos, espCol );
	//	
	//	if( vars->bones )
	//		draw->drawBones( ent );
	//
	//	if( vars->hpBar )
	//		draw->drawHPBar( entHP, minx, miny, maxy, espCol );
	//
	//	if( vars->name )
	//		draw->drawText( draw->font, minx + maxx * 0.5, miny - 15, true, Color(255, 255, 255, 255), info.name );
	//
	//	if( vars->weapon ) {
	//		std::string wepName = engine->GetClientEntity( ent->getActiveWeapon(), true )->GetClientClass()->m_pNetworkName;
	//		if( !wepName.empty() ) {
	//			if( !strncmp(wepName.c_str(), "C", 1) )
	//				wepName.erase( 0, 1 );
	//
	//			if( !strncmp(wepName.c_str(), "Weapon", 6) )
	//				wepName.erase( 0, 6 );
	//
	//			draw->drawText( draw->font, minx + maxx * 0.5, miny + maxy + 1, true, Color(255, 255, 255, 255), wepName.c_str() );
	//		}
	//	}
	//
	//	//if( vars->chams ) {
	//	//	int id = 0, w = 0, h = 0;
	//	//	if( !id )
	//	//		draw->setupTexture( id, "", w, h );
	//	//
	//	//	draw->drawTexture( id, 50, 50, w, h );
	//	//}
	//}
}