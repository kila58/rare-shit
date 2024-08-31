#pragma once

class Vars {
public:
	// tab vars
	int espTab = 0;
	int aimbotTab = 0;
	int miscTab = 0;
	int hvhTab = 0;

	// esp
	int espEnabled = 1;
	int box = 1;
	int box3D = 0;
	int name = 1;
	int hpBar = 1;
	int bones = 0;
	int weapon = 1;
	int chams = 0;
	int weapons = 0;

	// aimbot
	int aimEnabled = 1;
	int autoShoot = 0;
	int fov = 4;
	int smooth = 5;
	int silent = 0;
	int pSilent = 0;
	int stopMovement = 0;
	int hitbox = 10;
	int autoWall = 0;
	int autoWallMinDamage = 4;
	int hitScan = 0;
	int hitChance = 0;
	int smartAim = 0;
	int ignoreTeam = 1;

	// misc
	int autostrafe = 0;
	int rcs = 1;
	int visualFov = 0;
	int visNoRecoil = 0;
	int noSky = 0;
	int asusWalls = 0;
	int noHands = 0;
	int lol = 0;

	// hvh
	int aaholdticks = 3;
	int aa = 0;
	int edgeAA = 0;
	int aimAA = 0;
	int spinBot = 0;
	int spinBotSpeed = 32;
	int fakeLag = 0;
	int fakeLagFactor = 5;

	// mm unsafe
	int antiUntrust = 1;
	int noSpread = 0;
	int speed = 4;
}; extern Vars *vars;