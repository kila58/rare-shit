#pragma once

#include "main.h"

struct Item {
	Item() {
		value = 0;
		min = 0;
		max = 0;
	}

	char name[ 256 ];
	int *value;
	int min;
	int max;
};

struct playerList {
	playerList() {
		all = 0;
		open = 0;
		x = 0;
		y = 0;
		friendly = 0;
		rage = 0;
		body = 0;
	}

	int all;
	int open;
	int x;
	int y;
	int friendly;
	int rage;
	int body;
};

class Menu {
private:
	std::vector<Item> items;
	int menuX = 0, menuY = 0, menuW = 200, menuH = 0, playerListH = 0, selected = 0;
	bool menuToggle = false, playerlistToggle = false;

	void addItem( char name[ 256 ], int *val, int min, int max ) {
		Item i;
		strcpy_s( i.name, name );
		i.value = val;
		i.min = min;
		i.max = max;
		items.push_back( i );
	}

	void itemThink() {
		addItem( vars->espTab ? "[-] ESP" : "[+] ESP", &vars->espTab, 0, 1 );
		if( vars->espTab ) {
			addItem( "\t\t\t Enabled", &vars->espEnabled, 0, 1 );
			addItem( "\t\t\t Player 2DBox", &vars->box, 0, 1 );
			addItem( "\t\t\t Player 3DBox", &vars->box3D, 0, 1 );
			addItem( "\t\t\t Player Name", &vars->name, 0, 1 );
			addItem( "\t\t\t Player HP bar", &vars->hpBar, 0, 1 );
			addItem( "\t\t\t Player Bones", &vars->bones, 0, 1 );
			addItem( "\t\t\t Player weapons", &vars->weapon, 0, 1 );
			addItem( "\t\t\t Player Chams", &vars->chams, 0, 1 );
			addItem( "\t\t\t Weapons", &vars->weapons, 0, 1 );
		}
		
		addItem( vars->aimbotTab ? "[-] Aimbot" : "[+] Aimbot", &vars->aimbotTab, 0, 1 );
		if( vars->aimbotTab ) {
			addItem( "\t\t\t Enabled", &vars->aimEnabled, 0, 1 );
			addItem( "\t\t\t Autoshoot", &vars->autoShoot, 0, 1 );
			addItem( "\t\t\t Fov", &vars->fov, 0, 180 );
			addItem( "\t\t\t Smooth", &vars->smooth, 0, 100 );
			addItem( "\t\t\t Silent", &vars->silent, 0, 1 );
			addItem( "\t\t\t pSilent", &vars->pSilent, 0, 1 );
			addItem( "\t\t\t Stop movement", &vars->stopMovement, 0, 1 );
			addItem( "\t\t\t Hitbox", &vars->hitbox, 0, 18 );
			addItem( "\t\t\t Autowall", &vars->autoWall, 0, 1 );
			addItem( "\t\t\t Autowall min damage", &vars->autoWallMinDamage, 1, 99 );
			if( vars->hitScan < 2 )
				addItem( "\t\t\t Hit scan", &vars->hitScan, 0, 2 );
			else if( vars->hitScan == 2 )
				addItem( "\t\t\t Hit scan ( extreme )", &vars->hitScan, 0, 2 );
			addItem( "\t\t\t Hitchance", &vars->hitChance, 0, 99 );
			addItem( "\t\t\t Smart aim", &vars->smartAim, 0, 1 );
			addItem( "\t\t\t Ignore team", &vars->ignoreTeam, 0, 1 );
		}
		
		addItem( vars->miscTab ? "[-] Misc" : "[+] Misc", &vars->miscTab, 0, 1 );
		if( vars->miscTab ) {
			addItem( "\t\t\t Auto strafe", &vars->autostrafe, 0, 1 );
			if( vars->rcs < 2 )
				addItem( "\t\t\t RCS", &vars->rcs, 0, 2 );
			else if( vars->rcs == 2 )
				addItem( "\t\t\t RCS ( constant )", &vars->rcs, 0, 2 );
			addItem( "\t\t\t Visual no recoil", &vars->visNoRecoil, 0, 1 );
			addItem( "\t\t\t Visual fov", &vars->visualFov, 0, 50 );
			addItem( "\t\t\t No sky", &vars->noSky, 0, 1 );
			addItem( "\t\t\t Asus walls", &vars->asusWalls, 0, 1 );
			addItem( "\t\t\t No hands", &vars->noHands, 0, 1 );
		}
		
		addItem( vars->hvhTab ? "[-] HvH" : "[+] HvH", &vars->hvhTab, 0, 1 );
		if( vars->hvhTab ) {
			addItem( "\t\t\t AA hold ticks", &vars->aaholdticks, 1, 6 );
			addItem( "\t\t\t Anti aim", &vars->aa, 0, 6 );
			addItem( "\t\t\t Edge AA", &vars->edgeAA, 0, 2 );
			addItem( "\t\t\t Aim AA", &vars->aimAA, 0, 1 );
			addItem( "\t\t\t Spinbot", &vars->spinBot, 0, 1 );
			addItem( "\t\t\t Spinbot speed", &vars->spinBotSpeed, 0, 179 );
			addItem( "\t\t\t Fakelag", &vars->fakeLag, 0, 1 );
			addItem( "\t\t\t Fakelag factor", &vars->fakeLagFactor, 0, 15 );
			addItem( "\t\t\t Anti untrust (!)", &vars->antiUntrust, 0, 1 );
			addItem( "\t\t\t Nospread (!)", &vars->noSpread, 0, 1 );
			addItem( "\t\t\t Speedhack (!)", &vars->speed, 0, 50 );
		}
	}

	void handleInput() {
		//if( items.empty() )
		//	return;

		if( GetAsyncKeyState(VK_UP) & 1 )
			selected--;
		else if( GetAsyncKeyState(VK_DOWN) & 1 )
			selected++;
		else if( GetAsyncKeyState(VK_RIGHT) & 1 )
			*items[ selected ].value += 1;
		else if( GetAsyncKeyState(VK_LEFT) & 1 )
			*items[ selected ].value -= 1;

		if( selected < 0 )
			selected = items.size() - 1;
		else if( selected > items.size() - 1 )
			selected = 0;
		else if( *items[selected].value < items[selected].min )
			*items[selected].value = items[selected].max;
		else if( *items[selected].value > items[selected].max )
			*items[selected].value = items[selected].min;
	}

	void drawMenu() {
		draw->drawFilledRect( menuX, menuY, menuW, 14, Color(0, 0, 0, 150) );
		draw->drawFilledRectOutlined( menuX, menuY, menuW, menuH, Color(0, 0, 0, 200), Color(102, 255, 102, 255) );
		draw->drawText( 5, menuX + menuW * 0.5, menuY + 1, true, Color(255, 255, 255, 255), "[ nabeFramework CS:GO ]" );
		
		int y = menuY + 14;
		for( int i = 0; i < items.size(); i++ ) {
			Color selection = Color( 255, 255, 255, 0 );
			if( selected == i )
				selection.a = 50;

			draw->drawFilledRect( menuX, y, menuW, 12, selection );
			draw->drawText( 5, menuX + 1, y, false, Color(255,255,255,255), items[i].name );
			draw->drawText( 5, menuX + 180, y, false, Color(255,255,255,255), "%i", *items[i].value );

			y += 12;
		}

		menuH = y - menuY;
	}

	void listThink() {
		if( menuToggle || !cheat->localPly )
			return;

		addItem( list[0].open ? "[-] All" : "[+] All", &list[0].open, 0, 1 );
		if( list[0].open ) {
			if( list[0].x == 0 )
					addItem( "\t\t\t x", &list[0].x, 0, 5 );
				else if( list[0].x == 1 )
					addItem( "\t\t\t x (clamp)", &list[0].x, 0, 5 );
				else if( list[0].x == 2 )
					addItem( "\t\t\t x (fix)", &list[0].x, 0, 5 );
				else if( list[0].x == 3 )
					addItem( "\t\t\t x (90)", &list[0].x, 0, 5 );
				else if( list[0].x == 4 )
					addItem( "\t\t\t x (-90)", &list[0].x, 0, 5 );
				else if( list[0].x == 5 )
					addItem( "\t\t\t x (jitter)", &list[0].x, 0, 5 );

				if( list[0].y == 0 )
					addItem( "\t\t\t y", &list[0].y, 0, 10 );
				else if( list[0].y == 1 )
					addItem( "\t\t\t y (clamp)", &list[0].y, 0, 10 );
				else if( list[0].y == 2 )
					addItem( "\t\t\t y (fix)", &list[0].y, 0, 10 );
				else if( list[0].y == 3 )
					addItem( "\t\t\t y (-=45)", &list[0].y, 0, 10 );
				else if( list[0].y == 4 )
					addItem( "\t\t\t y (+=45)", &list[0].y, 0, 10 );
				else if( list[0].y == 5 )
					addItem( "\t\t\t y (-=90)", &list[0].y, 0, 10 );
				else if( list[0].y == 6 )
					addItem( "\t\t\t y (+=90)", &list[0].y, 0, 10 );
				else if( list[0].y == 7 )
					addItem( "\t\t\t y (-=135)", &list[0].y, 0, 10 );
				else if( list[0].y == 8 )
					addItem( "\t\t\t y (+=135)", &list[0].y, 0, 10 );
				else if( list[0].y == 9 )
					addItem( "\t\t\t y (-=180)", &list[0].y, 0, 10 );
				else if( list[0].y == 10 )
					addItem( "\t\t\t y (jitter)", &list[0].y, 0, 10 );
		}

		char tab[ 128 ];
		for( int i = 1; i <= engine->globals->maxClients; i++ ) {
			CBaseEntity *ent = engine->GetClientEntity( i );
			if( !ent || ent == cheat->localPly ) {
				list[ i ] = playerList();
				continue;
			}
		
			player_info info;
			if( !engine->GetPlayerInfo(i, &info) ) {
				list[ i ] = playerList();
				continue;
			}
		
			if( ent->getTeam() == cheat->localPly->getTeam() ) {
				list[ i ] = playerList();
				continue;
			}
			
			if( list[i].open )
				sprintf_s( tab, sizeof(tab), "[-] %s", info.name );
			else
				sprintf_s( tab, sizeof(tab), "[+] %s", info.name );

			addItem( tab, &list[i].open, 0, 1 );
			if( list[i].open ) {
				if( list[i].x == 0 )
					addItem( "\t\t\t x", &list[i].x, 0, 5 );
				else if( list[i].x == 1 )
					addItem( "\t\t\t x (clamp)", &list[i].x, 0, 5 );
				else if( list[i].x == 2 )
					addItem( "\t\t\t x (fix)", &list[i].x, 0, 5 );
				else if( list[i].x == 3 )
					addItem( "\t\t\t x (90)", &list[i].x, 0, 5 );
				else if( list[i].x == 4 )
					addItem( "\t\t\t x (-90)", &list[i].x, 0, 5 );
				else if( list[i].x == 5 )
					addItem( "\t\t\t x (jitter)", &list[i].x, 0, 5 );

				if( list[i].y == 0 )
					addItem( "\t\t\t y", &list[i].y, 0, 10 );
				else if( list[i].y == 1 )
					addItem( "\t\t\t y (clamp)", &list[i].y, 0, 10 );
				else if( list[i].y == 2 )
					addItem( "\t\t\t y (fix)", &list[i].y, 0, 10 );
				else if( list[i].y == 3 )
					addItem( "\t\t\t y (-=45)", &list[i].y, 0, 10 );
				else if( list[i].y == 4 )
					addItem( "\t\t\t y (+=45)", &list[i].y, 0, 10 );
				else if( list[i].y == 5 )
					addItem( "\t\t\t y (-=90)", &list[i].y, 0, 10 );
				else if( list[i].y == 6 )
					addItem( "\t\t\t y (+=90)", &list[i].y, 0, 10 );
				else if( list[i].y == 7 )
					addItem( "\t\t\t y (-=135)", &list[i].y, 0, 10 );
				else if( list[i].y == 8 )
					addItem( "\t\t\t y (+=135)", &list[i].y, 0, 10 );
				else if( list[i].y == 9 )
					addItem( "\t\t\t y (-=180)", &list[i].y, 0, 10 );
				else if( list[i].y == 10 )
					addItem( "\t\t\t y (jitter)", &list[i].y, 0, 10 );

				addItem( "\t\t\t friend", &list[i].friendly, 0, 1 );
				addItem( "\t\t\t rage", &list[i].rage, 0, 1 );
				addItem( "\t\t\t body", &list[i].body, 0, 1 );
			}
		}
	}

	void drawList() {
		if( menuToggle )
			return;

		menuX -= 200;

		draw->drawFilledRect( menuX, menuY, menuW, 14, Color(0, 0, 0, 150) );
		draw->drawFilledRectOutlined( menuX, menuY, menuW, playerListH, Color(0, 0, 0, 200), Color(176, 48, 96, 255) );
		draw->drawText( 5, menuX + menuW * 0.5, menuY + 1, true, Color(255, 255, 255, 255), "[ nabeFramework ] - Player list" );
		
		int y = menuY + 14;
		for( int i = 0; i < items.size(); i++ ) {
			Color selection = Color( 255, 255, 255, 0 );
			if( selected == i )
				selection.a = 50;
			
			draw->drawFilledRect( menuX, y, menuW, 12, selection );
			draw->drawText( 5, menuX + 1, y, false, Color(255,255,255,255), items[i].name );
			draw->drawText( 5, menuX + 180, y, false, Color(255,255,255,255), "%i", *items[i].value );
			y += 12;
		}
		
		playerListH = y - menuY;
	}
public:
	std::vector<playerList> list;

	Menu() {
		list.assign( 64, playerList() );
	}

	void think() {
		if( GetAsyncKeyState(VK_INSERT) & 1 ) {
			if( playerlistToggle )
				menuToggle = true;
			else
				menuToggle = !menuToggle;

			playerlistToggle = false;
		}else if( GetAsyncKeyState(VK_DELETE) & 1 ){
			if( menuToggle  )
				playerlistToggle = true;
			else
				playerlistToggle = !playerlistToggle;

			menuToggle = false;
		}

		if( !menuToggle && !playerlistToggle )
			return;

		listThink(); // update player list

		menuX = cheat->scrW * 0.25;
		menuY = cheat->scrH * 0.25;

		if( menuToggle ) {
			itemThink();
			drawMenu();
		}else if( playerlistToggle )
			drawList();

		handleInput();

		items.clear();
	}
}; extern Menu *menu;


/*
	//struct Item {
//	char *name;
//	int val, min, max;
//};

//class Tab {
//private:
//	char *name;
//public:
//	bool enabled = true;
//	std::vector< Item > items;
//	Tab( char *name ) {
//		this->name = name;
//	}
//
//	void drawTab( int x, int &y ) {
//		if( !enabled )
//			return;
//
//		for( int i = 0; i < items.size(); i++ ) {
//			//Color selection = Color( 255, 255, 255, 0 );
//			//if( selected == i )
//			//	selection.a = 50;
//
//			// todo draw items / tabs with values
//			//draw->drawFilledRect( x, y, 200, 12, selection );
//			draw->drawText( 5, x + 1, y, false, Color(255,255,255,255), items[i].name );
//			draw->drawText( 5, x + 180, y, false, Color(255,255,255,255), "%i", items[i].val );
//
//			y += 12;
//		}
//	}
//
//	void addItem( char *name, int &val, int min, int max ) {
//		Item i;
//		i.name = name;
//		i.val = val;
//		i.min = min;
//		i.max = max;
//		items.push_back( i );
//	}
//
//	void addItems( std::vector<Item> v ) {
//		for( int i = 0; i < items.size(); i++ )
//			v.push_back( items[i] );
//	}
//};
//
//int testVal = 0;
//int testVal2 = 0;
//int testVal3 = 0;
//
//class Menu {
//private:
//	std::vector< Tab > tabs;
//	std::vector< Item > items;
//	bool menuToggle = false;
//	int menuX = 0, menuY = 0, menuH = 0, tabY = 0, selected = 0;
//public:
//	Menu() {
//		Tab esp( "ESP" );
//		esp.addItem( "test", testVal, 0, 5 );
//		esp.addItem( "test2", testVal2, 0, 5 );
//		tabs.push_back( esp );
//		
//		//Tab aimbot( "Aimbot" );
//		//aimbot.addItem( "test3", testVal3, 0, 5 );
//		//tabs.push_back( aimbot );
//	}
//
//	void handleInput() {
//		if( GetAsyncKeyState(VK_UP) & 1 )
//			selected--;
//		else if( GetAsyncKeyState(VK_DOWN) & 1 )
//			selected++;
//		else if( GetAsyncKeyState(VK_RIGHT) & 1 )
//			items[selected].val++;
//		else if( GetAsyncKeyState(VK_LEFT) & 1 )
//			items[selected].val--;
//	
//		//if( selected < 0 )
//		//	selected = items.size() - 1;
//		//else if( selected > items.size() - 1 )
//		//	selected = 0;
//		//else if( *items[selected].value < items[selected].min )
//		//	*items[selected].value = items[selected].max;
//		//else if( *items[selected].value > items[selected].max )
//		//	*items[selected].value = items[selected].min;
//	}
//
//	void drawMenu() {
//		menuX = cheat->scrW * 0.25;
//		menuY = cheat->scrH * 0.25;
//
//		draw->drawFilledRect( menuX, menuY, 200, 14, Color(0, 0, 0, 150) );
//		draw->drawFilledRectOutlined( menuX, menuY, 200, menuH, Color(0, 0, 0, 155), Color(176, 48, 96, 255) );
//		draw->drawText( 5, menuX + 200 * 0.5, menuY + 1, true, Color(255, 255, 255, 255), "[ nabeFramework ]" );
//
//		tabY = menuY + 14;
//		for( int i = 0; i < tabs.size(); i++ ) {
//			tabs[i].drawTab( menuX, tabY );
//
//			if( tabs[i].enabled )
//				tabs[i].addItems( items );
//		}
//
//		menuH = tabY - menuY;
//	}
//
//	void think() {
//		if( GetAsyncKeyState(VK_INSERT) & 1 )
//			menuToggle = !menuToggle;
//
//		if( !menuToggle )
//			return;
//
//		handleInput();
//		drawMenu();
//	}
//};
*/