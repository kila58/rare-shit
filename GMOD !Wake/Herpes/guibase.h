/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

//-- CVars --
float aim_menu, esp_menu, vis_menu, rem_menu, misc_menu;

// Aimbot
float cvarAimbot;
float cvarAutoshoot = 1.00;
float cvarAimkey;
float cvarAimspot = 0.00;
float cvarFOV = 360.00;
float cvarSmooth = 0.00;
float cvarSilentAim = 0.00;
float cvarPrediction = 1.00;
float cvarFriends = 1.00;
float cvarFriendlyfire;
float cvarDeathmatch;
float cvarBoxFix;
float cvarAimThru;
float cvarHitScan;

// ESP
float cvarEnableESP = 1.00;
float cvarNameESP = 1.00;
float cvarWeaponESP = 1.00;
float cvarHealthESP = 1.00;
float cvarBoxESP = 1.00;
float cvarEntityESP = 1.00;

float cvarFriendlyVisibleRed = 0.0;
float cvarFriendlyVisibleGreen = 150.0;
float cvarFriendlyVisibleBlue = 255.0;
float cvarFriendlyInvisibleRed = 0.0;
float cvarFriendlyInvisibleGreen = 255.0;
float cvarFriendlyInvisibleBlue = 0.0;

float cvarEnemyVisibleRed = 255.0;
float cvarEnemyVisibleGreen = 0.0;
float cvarEnemyVisibleBlue = 0.0;
float cvarEnemyInvisibleRed = 255.0;
float cvarEnemyInvisibleGreen = 255.0;
float cvarEnemyInvisibleBlue = 0.0;

// Visual
float cvarCrosshair = 1.0;

// Removals
float cvarSeedNoSpread;
float cvarCompensationalSpread;
float cvarFASFix;

// Misc
float cvarBunnyhop = 1.00;
float cvarAutopistol = 1.00;
float cvarSpeedHack = 1.00;
float cvarNamestealer = 0.00;
float cvarFakeLag;
float cvarFakeLag2;
float cvarAntiAim;
float cvarAntiAntiAim;
float cvarAAngleX;
float cvarAAngleY;
float cvarFakeAAngleX;
float cvarFakeAAngleY;
float cvarpSilent;
float cvarSpeedinJump;
float cvarTeleport;
float cvarDebug;

#define _KEY_INSERT		0x2D
#define _KEY_UP			0x26
#define _KEY_DOWN		0x28
#define _KEY_RIGHT		0x27
#define _KEY_LEFT		0x25
#define _MWHEEL_DOWN	0x20A

int selectionPos = 0;
bool drawMenu = false;

int size = 0;
int space = 14;
int maxItems = 0;
int menuIndex = 0;
int cvar_num = 0;

struct item {
	char name[1000];
	float* value;
	float min;
	float max;
	float step;
};
item aitem[150];

int AddItem( char m_name[1000], float* m_value, float m_min, float m_max, float m_step, int i )
{
	strcpy( aitem[i].name, m_name );
	aitem[i].value = m_value;
	aitem[i].min = m_min;
	aitem[i].max = m_max;
	aitem[i].step = m_step;

	return i + 1;
}

void KeyPress()
{
	if( GetAsyncKeyState( _KEY_UP ) & 1 )
	{
		if( selectionPos > 0 )
			selectionPos -= 1;
	}

	if( GetAsyncKeyState( _KEY_DOWN ) & 1 )
	{
		if( selectionPos < maxItems - 1 )
			selectionPos += 1;
	}

	if( GetAsyncKeyState( _KEY_LEFT ) & 1 )
	{
		if( aitem[menuIndex].value )
		{
			aitem[menuIndex].value[0] -= 1;
			if( aitem[menuIndex].value[0] < aitem[menuIndex].min )
				aitem[menuIndex].value[0] = aitem[menuIndex].max;
		}
	}

	if( GetAsyncKeyState( _KEY_RIGHT ) & 1 )
	{
		if( aitem[menuIndex].value )
		{
			aitem[menuIndex].value[0] += 1;
			if( aitem[menuIndex].value[0] > aitem[menuIndex].max )
				aitem[menuIndex].value[0] = aitem[menuIndex].min;
		}
	}
}

void InitMenu()
{
	int i = 0;

	if( aim_menu == 0 )
		i = AddItem( "+ AIMBOT",		&aim_menu, 0, 1, 1, i );
	
	if( aim_menu == 1 )
	{
		i = AddItem( "- AIMBOT",		&aim_menu, 0, 1, 1, i );
		i = AddItem("     Aimbot", &cvarAimbot, 0, 1, 1, i);
		i = AddItem( "     Autoshoot",	&cvarAutoshoot,	0, 1, 1, i );
		i = AddItem( "     Aimkey",		&cvarAimkey,	0, 3, 1, i );
		i = AddItem( "     Aimspot",	&cvarAimspot,	0, 16, 0, i );
		//i = AddItem("     Box fix", &cvarBoxFix, 0, 1, 0, i);
		//i = AddItem( "     Smooth",		&cvarSmooth,	0, 20, 1, i );
		i = AddItem( "     Silent",		&cvarSilentAim,	0, 1, 1, i );
		//i = AddItem("     pSilent", &cvarpSilent, 0, 1, 1, i);
		i = AddItem( "     FOV",		&cvarFOV,	0, 360, 1, i );
		i = AddItem( "     Friends",	&cvarFriends,	0, 1, 1, i );
		//i = AddItem( "     Prediction",	&cvarPrediction,	0, 1, 1, i );
		i = AddItem( "     Friendlyfire",&cvarFriendlyfire,	0, 1, 1, i );
		i = AddItem( "     Deathmatch",	&cvarDeathmatch,	0, 1, 1, i );
		//i = AddItem("     AimThru", &cvarAimThru, 0, 1, 1, i);
		//i = AddItem("     HitScan", &cvarHitScan, 0, 1, 1, i);
	}

	if( esp_menu == 0 )
		i = AddItem( "+ ESP",			&esp_menu, 0, 1, 1, i );
	
	if( esp_menu == 1 )
	{
		i = AddItem( "- ESP",			&esp_menu, 0, 1, 1, i );
		i = AddItem( "     Enable",		&cvarEnableESP,	0, 1, 1, i );
		i = AddItem( "     Name",		&cvarNameESP,	0, 1, 1, i );
		//i = AddItem( "     Weapon",		&cvarWeaponESP,	0, 1, 1, i );
		//i = AddItem( "     Health",		&cvarHealthESP,	0, 1, 1, i );
		i = AddItem( "     Box",		&cvarBoxESP,	0, 1, 1, i );
		/*i = AddItem("     Friendly Visible Color R", &cvarFriendlyVisibleRed, 0, 255, 1, i);
		i = AddItem("     Friendly Visible Color G", &cvarFriendlyVisibleGreen, 0, 255, 1, i);
		i = AddItem("     Friendly Visible Color B", &cvarFriendlyVisibleBlue, 0, 255, 1, i);
		i = AddItem("     Friendly Hidden Color R", &cvarFriendlyInvisibleRed, 0, 255, 1, i);
		i = AddItem("     Friendly Hidden Color G", &cvarFriendlyInvisibleGreen, 0, 255, 1, i);
		i = AddItem("     Friendly Hidden Color B", &cvarFriendlyInvisibleBlue, 0, 255, 1, i);
		i = AddItem("     Enemy Visible Color R", &cvarEnemyVisibleRed, 0, 255, 1, i);
		i = AddItem("     Enemy Visible Color G", &cvarEnemyVisibleGreen, 0, 255, 1, i);
		i = AddItem("     Enemy Visible Color B", &cvarEnemyVisibleBlue, 0, 255, 1, i);
		i = AddItem("     Enemy Hidden Color R", &cvarEnemyInvisibleRed, 0, 255, 1, i);
		i = AddItem("     Enemy Hidden Color G", &cvarEnemyInvisibleGreen, 0, 255, 1, i);
		i = AddItem("     Enemy Hidden Color B", &cvarEnemyInvisibleBlue, 0, 255, 1, i);*/
		//i = AddItem( "     Entity",		&cvarEntityESP,	0, 1, 1, i );
	}

	if( vis_menu == 0 )
		i = AddItem( "+ VISUALS",		&vis_menu, 0, 1, 1, i );
	
	if( vis_menu == 1 )
	{
		i = AddItem( "- VISUALS",		&vis_menu, 0, 1, 1, i );
		i = AddItem( "     Crosshair",	&cvarCrosshair, 0, 1, 1, i );
	}

	if( rem_menu == 0 )
		i = AddItem( "+ REMOVALS",		&rem_menu, 0, 1, 1, i );

	if( rem_menu == 1 )
	{
		i = AddItem( "- REMOVALS",		&rem_menu, 0, 1, 1, i );
		//i = AddItem( "     NoRecoil",	&cvarNoRecoil, 0, 1, 1, i );
		//i = AddItem( "     NoVisRecoil",&cvarNoVisRecoil, 0, 1, 1, i );
		i = AddItem( "     Seed",	&cvarSeedNoSpread, 0, 1, 1, i );
		//i = AddItem("	    Compensational", &cvarCompensationalSpread, 0, 1, 1, i);
		//i = AddItem("     FAS Fix", &cvarFASFix, 0, 1, 1, i);
	}

	if( misc_menu == 0 )
		i = AddItem( "+ MISC",			&misc_menu, 0, 1, 1, i );

	if( misc_menu == 1 )
	{
		i = AddItem( "- MISC",			&misc_menu, 0, 1, 1, i );
		i = AddItem( "     Bunnyhop",	&cvarBunnyhop, 0, 1, 1, i );
		/*i = AddItem( "     Fakelag",	&cvarFakeLag, 0, 1, 1, i);
		i = AddItem("     Fakelag2", &cvarFakeLag2, 0, 1, 1, i);
		i = AddItem( "     Autopistol",	&cvarAutopistol, 0, 1, 1, i );
		i = AddItem( "     SpeedHack",	&cvarSpeedHack, 0, 1, 1, i );
		i = AddItem("     SpeedJump", &cvarSpeedinJump, 0, 1, 1, i);
		i = AddItem("     Teleport", &cvarTeleport, 0, 1, 1, i);
		i = AddItem("     AntiAntiAim", &cvarAntiAntiAim, 0, 1, 1, i);
		i = AddItem( "     AntiAim",	&cvarAntiAim, 0, 7, 1, i );
		i = AddItem( "     Namestealer",&cvarNamestealer, 0, 1, 1, i );
		i = AddItem("     AA Angle X", &cvarAAngleX, -360, 360, 1, i);
		i = AddItem("     AA Angle Y", &cvarAAngleY, -360, 360, 1, i);
		i = AddItem("     AA Fake X", &cvarFakeAAngleX, -360, 360, 1, i);
		i = AddItem("     AA Fake Y", &cvarFakeAAngleY, -360, 360, 1, i);
		//i = AddItem("     Floopy Say", &cvarFloopySay, 0, 3, 0, i);
		//i = AddItem("     Clan Owner", &cvarClanOwner, 0, 1, 0, i);
		i = AddItem("     Debug", &cvarDebug, 0, 1, 1, i);
		//i = AddItem("     Aim Through", &cvarAimThrough, 0, 1, 1, i);*/
	}

	size = i * space;
	maxItems = i;
}

void MenuDrawing()
{
	if( GetAsyncKeyState( _KEY_INSERT ) & 1 )
		drawMenu = !drawMenu;

	if( !drawMenu )
		return;

	static int x = ( wide / 2 ) - size / 2;
	static int y = 50;

	int h = size;
	int w = 255;

	KeyPress();

	// Tabby Thing
	FillRGBA( x, y - space, w, space, Color( 0, 0, 0, 255 ) );

	// Menu UI lul
	FillRGBA( x, y, w, h, Color( 0, 0, 0, 200 ) );

	// Selector
	FillRGBA( x + 1, y + ( selectionPos * space ), w - 2, space, Color( 255, 0, 0, 150 ) );

	// theshit
	for( int index = 0; index < maxItems; index++ )
	{
		if( index == selectionPos )
		{
			menuIndex = index;
		}
		DrawString( x + 2, y + ( space * index ), Color( 255, 255, 255, 255 ), aitem[index].name );

		char valBuff[10];
		sprintf( valBuff, "%2.2f", aitem[index].value[0] );
		
		DrawString( x + 220, y + ( space * index ), Color( 255, 255, 255, 255 ), valBuff );
	}

	DrawOutlinedRect( x, y - space, w, space, Color( 0, 0, 0, 255 ) );
	DrawOutlinedRect( x, y, w, h, Color( 0, 0, 0, 255 ) );

	DrawString( x + 2, y - ( space - 1 ), Color( 255, 255, 255, 255 ), "!Wake" );
}