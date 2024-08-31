#ifndef _CONTROL_VARIABLES_H_
#define _CONTROL_VARIABLES_H_
//===================================================================================
class CControlVariables
{
public:

	void Initialize( void );
	void Load( void );
	void Save( void );


	float aimbot_switch;
	float triggerbot_switch;
	float seedtriggerbot_switch;
	float fov;
	float autoshoot;
	float rcs;
	float smooth;
	float barrels;
	float skins;
	float bbox;
	float AABB;
	float aim_human_speed;
	float autostrafe_vis;
	float autostrafe_sideways;
	float aim_human_scale;
	float fake_edge;
	float aimkey;
	float triggerkey;
	float seedtriggerkey;
	float seedtrigger;
	float CornerBox;
	float glow;
	bool MenuSwitch;
	bool DrawTeam;
	float Crosshair;
	float Radar;
	float Entity;
	float Chicken;
	float Skeleton;
	float spreadhelper;
	float standrcs;
	float c4esp;
	float AntiAim;
	float AntiAim2;
	float fakelag;
	float mouse11;
	float trigger;
	float aimbone;
	float aimbot;
	float NO;
	float silent;
	float aimteam;
	float aimonfire;
	float smoothon;
	float aimhead;
	float aimchest;
	float aimpelvis;
	float LCLICK;
	float RCLICK;
	float Bunny;
	float Name;
	float prediction;
	float Recoil;
	float seedBone;
	float watermark;
	float norecoil;
	float nospread;
	float namesteal;
	float autopistol;
	float aimActive;
	float autowall;
	float aimtime;
	float psilent;
	float novisualrecoil;
	float mouse3;
	float mouse4;
	float fov2;
	float Healthbar;
	float Armor;
	float Weapons;
	float spotted;
	float autostrafe;
	float chams;
	float shaderchams;
	float hands;
	float aa1;
	float head_trigger;
	float aa2;
	float aa3;
	float aa4;
	float hitscan;
	float RCS_X;
	float RCS_Y;
	float RCS_SMOOTH;
	float aim_head;
	float aim_chest;
	float aim_stomach;
	float aim_neck;
	float hbarL;
	float hbarB;
	float weaponS;
	float stop_crouch;
	int fakelag_s;
	float AA_FakeStatic;
	float LClick;
	float nohands;

	

	float misc_switch;
	float esp;
	float boxesp;
	float Health;
	float noflash;

	float misc_menu_x;
	float misc_menu_y;
	float misc_menu_w;
};

#endif