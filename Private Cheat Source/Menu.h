#include "Vector.h"
#include "SDK.h"
#include "Color Manager.h"
#include "Control Variables.h"

#define colGrey Color(80,80,80,255)
#define colDarkGrey Color(40,40,40,255)
#define colRed Color(255,90,90,255)
#define colCrimson Color(220,20,60,255)
#define colStrongBlue Color(0,0,255,255)
#define colGreen Color(0,255,0,255)
#define colLightGreen Color(154,205,50,255)
#define colBlack Color(0,0,0,255)
#define ClrDGrey Color(26,26,26,255)
#define ClrLGrey Color(90,90,90,255)
#define colWhite Color(255,255,255,255)
#define Magneta Color(237,33,125,255)
#define colBlue Color(70,130,180,255)
#define colCyan Color(0,255,255,255)
#define menuGreen Color(90, 255, 90, 255)
#define colWhite2 Color(255,255,255,255)
#define colYellow Color(255,255,0,255)

#define colMenu Color(255,102,0,255)
#define colMagnetaFrom Color(248,87,166,255)
#define colMagnetaTo Color(255,88,88,255)



class CMenu
{
public:
	void Render(int x, int y, int w, int h);
	void AddTab(int x, int y, int w, int h, Color Fill, Color Outline, const char* Text);
	void AddOtherTab(int x, int y, int w, int h, Color Fill, Color Outline, const char* Text);
	void TabOperator(int x, int y, int w, int h, bool &tab1, bool &tab2, bool &tab3, bool &tab4, bool &tab5, bool &tab6,bool &tab7);
	bool MouseClick(int x, int y, int w, int h);
	void DrawConsole(int x, int y, int w, int h, char *title);
	void KeyPicker(int x, int y, int w, int h, const char* option, bool &Click, bool &Clicker, bool &Clicky);
	void GetMouse();
	void PlayerList(int xpos, int ypos, int w, int h);
	void SideLabel(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption);
	void Notifier(int x, int y, int w, int h);
	void SideButtonL(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption);
	void DrawCheckBoxF(int x, int y, Color colour, const char* fmt, float &option, Color back, const char* desc);
	void NotifierRender(int x, int y, int w, int h);
	void DrawRhombusFill(int x, int y, int w, int h, Color dwColor);
	void RenderPlayerlist(int xpos, int ypos, int w, int h);
	void SideButton(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption);
	bool MoverWH(int &X, int &Y, int W, int H, int index);
	void DrawLineBox(int x, int y, int howfaryo, int w, int h, Color Line, Color bground, const char* Text);
	void ConsoleRender(int x, int y, int w, int h);
	void DrawSliderINT(float x, float y, float w, int min, int max, int &SmoothValue, int &sliderx2);
	void DrawSlider(float x, float y, float w, int min, int max, float &SmoothValue, int &sliderx,const char* option);
	bool Mousein(int x, int y, int w, int h);
	void DrawCombobox(int x, int y, int w, int h, Color Outline, Color back, Color String, const char* title, const char* item1, const char* item2, float &option1, float &option2, bool &Click, bool &Clicker, const char* desc);
	void TabDraw(int x, int y, int w, int h);
	//bool Mover(int &X, int &Y, int W, int H, int index);
	bool MoveMenu(int &X, int &Y, int W, int H,int index);
	void DrawCheckBox(int x, int y, const char* fmt, float &option);
	void DrawListBoxThing(int x, int y, int w, int h, int letters, Color background, Color text, const char* fmt);
	void SideLabel2(int x, int y, int w, int h, Color Fill, Color Text, int letters, const char* letter1, const char* letter2, const char* letter3, const char* letter4, const char* letter5, const char* letter6, const char* letter7, bool &pOption);
};


class COptions
{
public:
	bool Box;
	float Aimbot1;
	int N_X = 50;
	int N_Y = 50;
	bool CornerBox;
	bool Glow;
	bool Skeleton;
	bool Jitter;
	bool Panic = false;
	bool NoSmoke;
	bool Playerlist;
	bool CornerBoxX;
	bool BT_1;
	bool AK_2;
	bool tabLEGIT = true;
	bool team;
	int s1 = 0;
	int s2 = 0;
	int s3 = 0;
	bool KEYCLICK;
	bool KEYCLICKER;
	bool ESPCLICK;
	bool ESPCLICKER;
	bool TRIGGERCLICK;
	bool TRIGGERCICKER;
	bool TKEYCLICK;
	bool TKEYCLICKER;
	bool SKEYCLICK;
	bool SKEYCLICKER;
	int s4 = 0;
	int s5 = 0;
	int human_scale_s;
	int human_speed_s;
	int s6 = 0;
	bool tabAIM = true;
	bool NO;
	bool AIMCLICK;
	bool AIMCLIKER;
	bool tabVISUALS;
	bool tabMISC;
	bool tabSPECIAL;
	bool tabCOLORS;
	bool tabRAGE;
	bool AK_1;
	bool LifeA;
	bool tabESP;
	bool Armor;
	int PL_X = 40;
	int PL_Y = 300;
	int PL_W = 100;
	int PL_H = 100;

	bool Click;
	bool Clicky;
	bool Clicker;
	
	bool AimbotLegit;
	bool AimbotSilent;
	bool MenuSwitch;
	bool Console;
	bool HealthBarTop;
	bool HealthBarBottom;
	bool HealthBarLeft;
	bool keyTYPE;
	bool LClick;
	bool ShaderChams;
	bool RunOnce = true;
	bool runOnce = true;
	bool RClick;
	bool M3;
	bool SeedTrigger;
	bool M5;
	bool TKEY;
	bool HealthBarRight;
	bool Trigger;
	bool Distance;
	bool Name;
	bool Weapon;
	bool Snapline;
	int R;
	int G;
	int B;
	Vector g_vHitPosition;
	bool ColorPicker;
	bool Chams;
	bool NoHands;
	bool Random;
	bool Spam;
	bool Entities;
	bool Bunny;
	bool RCS;
	float lastX;
	float lastY;
	float destX;
	float destY;
	float curX;
	float curY;
	bool bHead;
	bool bBody;
	bool bPelvis;
	bool Chicken;
	bool EnemyOnly = true;
	float aim_human_speed = 10;
	float aim_human = 10;
	bool AutoStrafe;
	bool AntiAim1;
	bool Smooth;
	bool AutoFire;
	bool Weapons;
	bool Crosshair;
	bool SpreadCross;
	Vector Screen;
	bool Radar;
	bool Tooltip = true;
	int Console_X = 100;
	int Console_Y = 200;
	int Radar_X = 200;
	int Radar_Y = 200;
	int Menu_X = 350;
	int Menu_Y = 200;
	int Radar_Size = 100;
	int Radar_Range = 35;
	int SliderSm_X = Menu_X + 35;
	int SliderSm_Y = Menu_Y + 140;
};

class CEnable
{
public:
	bool enableLEGIT;
	bool enableRAGE;
	bool enableESP;
	bool enableMISC;
	bool Tooltip;
	bool boxType;
	bool AimEnable;
	bool TriggerEnable;
	bool VisualsEnable;
	bool RadarEnable;
	bool AntiaimEnable;
	bool MiscEnable;
	bool ConfigEnable;
};

class smoothAngle
{
public:

	smoothAngle()
	{
		smoothValue = 1.0f;
	}

	float smoothValue;

};

class AntiAngleX
{
public:

	AntiAngleX()
	{
		angleX = 1.0f;
	}

	float angleX;

};

class AntiAngleY
{
public:
	AntiAngleY()
	{
		angleY = 1.0f;
	}

	float angleY;
};

class FOVAngle
{
public:
	FOVAngle()
	{
		FOV = 1.0f;
	}
    
	FLOAT FOV;
};




