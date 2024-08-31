#pragma once

typedef struct CScreenSize_t
{
	int iScreenHeight;
	int iScreenWidth;

} CScreenSize;

typedef void* ( __stdcall* PaintTraverseFn )( int, bool, bool );
typedef void* ( __stdcall* AchievementMgrFn )( float );
void Hooked_Init( );
void fnCvarRenamer(const char* chOrigName, const char* chNewName, const char* dummyname );

extern CScreenSize gScreenSize;
extern unsigned long espfont;