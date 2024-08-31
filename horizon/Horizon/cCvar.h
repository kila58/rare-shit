#ifndef __C_CVAR_H
#define __C_CVAR_H

#include "sdk.h"

class CCvars
{
public:
	// Aimbot //
	float aim_active = 0;
	float aim_angles = 360;

	// ESP //
	float esp_active = 1;
	float esp_name = 1;
	float esp_health = 1;
	float esp_guid = 0;
	float esp_rank = 1;
	float esp_box = 1; // 1 = 2D 2 = 3D
	float esp_distance = 0;
	float esp_hitbox = 0;
	float esp_crosshair = 1;
	float esp_bones = 1;

	// Misc //
	float misc_bunnyhop = 1;

	// Removal //
	float rem_recoil = 0;
	float rem_spread = 0;

};

extern CCvars gCvar;

#endif