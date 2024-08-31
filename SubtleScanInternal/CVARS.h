#pragma once
#include "Main.h"
class CVars
{
public:
	float bhop;
	float bhop_strafe;
	float aimassist;
	float aimbot_autoshoot;
	float aimbot_silent;
	float triggerbot;
	float esp;
	float esp_fov;
	float esp_name;
	float esp_distance;
	float esp_health;
	float esp_weapon;
	float chams;
	float esp_healthbar;
	float esp_bone;
	float radar;
	float nohands;
	float fakelag;
	float chiken_glow;
	float aimbot_rcs;
	float fakeangle;
	float fakeside;
	float aimbot_psilent;
	float rcs;
	float spinbot;
	float esp_team;
	float novisrecoil;
	float fov = 30.f;
	float smoothamount;
	float aa_fakedownback;
	float nospread;
	bool MenuSwitch;
};
extern CVars gCvars;