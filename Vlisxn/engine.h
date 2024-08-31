#pragma once

#include "main.h"

#undef CreateFont

struct ClientClass;

typedef void *(__cdecl *CreateInterfaceFn)( const char *, int * );
typedef void  (__cdecl *MsgFn)( const char *, ... );
typedef void  (__cdecl *WarningFn)( const char *, ... );
//typedef void  (__cdecl *ConColorMsgFn)( const Color &, const char* );
MsgFn Msg;
WarningFn Warning;
//ConColorMsgFn ConColorMsg;

typedef void  (__cdecl *RandomSeedFn)( int );
typedef float (__cdecl *RandomFloatFn)( float, float );
RandomSeedFn RandomSeed;
RandomFloatFn RandomFloat;

// &end, &tr, start, dir, trace
// \x55\x8B\xEC\x83\xEC\x2C\xF3\x0F\x10\x75\x1C\x33\xC0\xF3\x0F\x10\x6D\x18\x0F\x57\xDB\xF3\x0F\x10\x65\x14
// xxxxxxxxxxxxxxxxxxxxxxxxxx
typedef bool (__stdcall *TraceToExitFn)( float, float, float, CGameTrace&, float, float, float, float, float, float, CGameTrace* );
typedef int (__stdcall *HandleBulletPenetrationFn)( int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int );

void msg( const char *pszMsg, ... ) { // shitty 'wrapper' funcs i guess
	va_list vList;

	char form[ 1024 ];
	va_start( vList, pszMsg );
	vsprintf_s( form, pszMsg, vList );
	va_end( vList );
	
	Msg( "[nabe] %s", form );
}

void error( const char *pszMsg, ... ) {
	va_list vList;

	char form[ 1024 ];
	va_start( vList, pszMsg );
	vsprintf_s( form, pszMsg, vList );
	va_end( vList );
	
	Warning( "[nabe] Error: %s", form );
}

// hook typedefs
typedef void (__thiscall *PaintTraverseFn)( void *, unsigned int, bool, bool );
typedef void (__thiscall *RunCommandFn)( void *, CBaseEntity *, CUserCmd *, void * );
typedef void (__thiscall *OverrideViewFn)( void *, CViewSetup * );
typedef IMaterial *(__thiscall *FindMaterialFn)( void *, const char *, const char *, bool, void * );
typedef void (__thiscall *SceneEndFn)( void * );
typedef void (__thiscall *HudUpdateFn)( void *, bool );

class Engine {
private:
	void *getInterface( const char *pszModule, const char *pszInterface ) {
		CreateInterfaceFn cI = (CreateInterfaceFn)GetProcAddress( GetModuleHandleA(pszModule), "CreateInterface" );
		if( !cI ) {
			error( "Invalid module: %s.\n", pszModule );
			return nullptr;
		}

		void *ret;

		char szInterface[ 64 ];
		for( int i = 99; i > 0; i-- ) {
			sprintf_s( szInterface, i > 9 ? "%s0%i" : "%s00%i", pszInterface, i );

			ret = cI( szInterface, 0 );
			if( ret ) {
				msg( "Got interface: %s[ 0x%x ].\n", szInterface, ret );
				return ret;
			}
		}

		if( !ret )
			error( "Failed to get interface: %s.\n", pszInterface );

		return nullptr;
	}
	inline bool dataCompare( char *data, char *sig, char *mask ) {
		for( ; *mask; ++mask, ++data, ++sig ) {
			if( *mask == 'x' && *data != *sig )
				return false;
		}
		
		return *mask == 0;
	}
public:
	DWORD sigScan(DWORD address, DWORD size, char *sig, char *mask ) {
		for(DWORD i = 0; i < size; i++ ) {
			if( dataCompare((char *)(address + i), sig, mask) )
				return address + i;
		}
	
		return 0;
	}

	// interfaces
	void *client;
	CGlobalVarsBase *globals; // ugly when called, but whatever
	void *clientMode;
	void *engineClient;
	void *gameMovement;
	void *moveHelper;
	void *prediction;
	void *entList;
	void *surfaceProps;
	void *engTrace;
	void *material;
	void *renderView;
	void *modelRender;
	void *modelInfo;
	void *panel;
	void *surface;
	void *cvar;

	// hooks
	PaintTraverseFn oPaintTraverse;
	RunCommandFn oRunCommand;
	OverrideViewFn oOverrideView;
	FindMaterialFn oFindMaterial;
	SceneEndFn oSceneEnd;
	HudUpdateFn oHudUpdate;

	inline void PaintTraverse( unsigned int vPanel, bool repaint, bool force ) { oPaintTraverse(panel, vPanel, repaint, force); }
	inline void RunCommand( CBaseEntity *ent, CUserCmd *cmd, void *moveHelper ) { oRunCommand(prediction, ent, cmd, moveHelper); }
	inline void OverrideView( CViewSetup *setup ) { oOverrideView(clientMode, setup); }
	//inline void FindMaterial( const char *mat, const char *group, bool complain, void *prefix ) { oFindMaterial(material, mat, group, complain, prefix); }
	inline void SceneEnd() { oSceneEnd(renderView); }
	inline void HudUpdate( bool active ) { oHudUpdate(client, active); }

	// other variables
	DWORD clientBase;
	DWORD engineBase;
	TraceToExitFn TraceToExit;
	HandleBulletPenetrationFn HandleBulletPenetration;

	Engine() {
		if( GetFileAttributesA("C:\\nabe") == INVALID_FILE_ATTRIBUTES )
			_wmkdir( L"C:\\nabe" );

		HMODULE t0 = GetModuleHandleA( "tier0.dll" );
		HMODULE vst = GetModuleHandleA( "vstdlib.dll" );

		Msg		= (MsgFn)GetProcAddress( t0, "Msg" );
		Warning = (WarningFn)GetProcAddress( t0, "Warning" );
		//ConColorMsg = (ConColorMsgFn)GetProcAddress( t0, "ConColorMsg" );

		RandomSeed = (RandomSeedFn)GetProcAddress( vst, "RandomSeed" );
		RandomFloat = (RandomFloatFn)GetProcAddress( vst, "RandomFloat" );

		clientBase = (DWORD)GetModuleHandleA( "client.dll" );
		engineBase = (DWORD)GetModuleHandleA( "engine.dll" );

		//TraceToExit = (TraceToExitFn)sigScan( clientBase, 0x7FFFFFFF, 
		//	"\x55\x8B\xEC\x83\xEC\x2C\xF3\x0F\x10\x75\x00\x33\xC0",
		//	"xxxxxxxxxx?xx" );
		//HandleBulletPenetration = (HandleBulletPenetrationFn)( sigScan(clientBase, 0x7FFFFFFF, 
		//	"\x0F\x57\xF6\x84\xC0\x75\x27\xF3\x0F\x10\x45\xF8\x0F\x2F\xC6\xF3\x0F\x10\x4D\x80\xF3\x0F\x10\x55\x94\xF3\x0F\x10\x65\xC4\xF3\x0F\x11\x45\xC0\x0F\x87\x00\x00\x00\x00\xEB\x03", 
		//	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xx") - 0x1 );
		
		client			= getInterface( "client.dll", "VClient" );
		globals			= **(CGlobalVarsBase ***)( getvFunc<DWORD>(client, 0) + 0x53 ); // 0x53
		clientMode		= **(void ***)( getvFunc<DWORD>(client, 10) + 0x5 );
		engineClient	= getInterface( "engine.dll", "VEngineClient" );
		gameMovement	= getInterface( "client.dll", "GameMovement" );
		//moveHelper		= **(void ***)( clientBase + 0x4B11228 ); // string ref "bogus" in client // 4B11228?
		prediction		= getInterface( "client.dll", "VClientPrediction" );
		entList			= getInterface( "client.dll", "VClientEntityList" );
		engTrace		= getInterface( "engine.dll", "EngineTraceClient" );
		surfaceProps	= getInterface( "vphysics.dll", "VPhysicsSurfaceProps" );
		material		= getInterface( "materialsystem.dll", "VMaterialSystem" );
		renderView		= getInterface( "engine.dll", "VEngineRenderView" );
		modelRender		= getInterface( "engine.dll", "VEngineModel" );
		modelInfo		= getInterface( "engine.dll", "VModelInfoClient" );
		panel			= getInterface( "vgui2.dll", "VGUI_Panel" );
		surface			= getInterface( "vguimatsurface.dll", "VGUI_Surface" );
		cvar			= getInterface( "vstdlib.dll", "VEngineCvar" );
	}

	/*
		CHLClient
	*/
	ClientClass *GetAllClasses() {
		typedef ClientClass *(__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(client, 8)( client );
	}

	/*
		CEngineClient
	*/
	inline void GetScreenSize( int &w, int &h ) {
		typedef void (__thiscall *OrigFn)( void *, int &, int & );
		return getvFunc<OrigFn>(engineClient, 5)( engineClient, w, h );
	}
	inline bool GetPlayerInfo( int index, player_info *pInfo ) {
		typedef bool (__thiscall *OrigFn)( void *, int, player_info * );
		return getvFunc<OrigFn>(engineClient, 8)( engineClient, index, pInfo );
	}
	inline int GetLocalPlayer() {
		typedef int (__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(engineClient, 12)( engineClient );
	}
	inline void SetViewAngles( Vector &Ang ) {
		typedef void (__thiscall *OrigFn)( void *, Vector& );
		getvFunc<OrigFn>(engineClient, 19)( engineClient, Ang );
	}
	inline bool IsInGame() {
		typedef bool (__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(engineClient, 26)( engineClient );
	}
	inline bool IsConnected() {
		typedef bool (__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(engineClient, 27)( engineClient );
	}
	inline const VMatrix &WorldToScreenMatrix() {
		typedef const VMatrix &(__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(engineClient, 37)( engineClient );
	}

	/*
		CGameMovement
	*/
	inline void ProcessMovement( CBaseEntity *ent, void *data ) {
		typedef void (__thiscall *OrigFn)( void *, CBaseEntity *, void * );
		getvFunc<OrigFn>(gameMovement, 1)( gameMovement, ent, data );
	}
	inline void DecayPunchAngle() {
		typedef void (__thiscall *OrigFn)( void * );
		getvFunc<OrigFn>(gameMovement, 19)( gameMovement );
	}
	inline void FullWalkMove() {
		typedef void (__thiscall *OrigFn)( void * );
		getvFunc<OrigFn>(gameMovement, 30)( gameMovement );
	}
	
	/*
		IMoveHelper
	*/
	inline void SetHost( CBaseEntity *ent ) {
		typedef void (__thiscall *OrigFn)( void *, CBaseEntity *ent );
		getvFunc<OrigFn>(moveHelper, 1)( moveHelper, ent );
	}

	/*
		CPrediction
	*/
	inline void SetupMove( CBaseEntity *ent, CUserCmd *cmd, void *data ) {
		//void *data = *(void **)( (dword)gameMovement + 0x8 );

		typedef void (__thiscall *OrigFn)( void *, CBaseEntity *, CUserCmd *, int, void * );
		getvFunc<OrigFn>(prediction, 20)( prediction, ent, cmd, 0, data );
	}
	inline void FinishMove( CBaseEntity *ent, CUserCmd *cmd, void *data ) {
		//void *data = *(void **)( (dword)gameMovement + 0x8 );

		typedef void (__thiscall *OrigFn)( void *, CBaseEntity *, CUserCmd *, void * );
		getvFunc<OrigFn>(prediction, 21)( prediction, ent, cmd, data );
	}

	/*
		IClientEntityList
	*/
	inline CBaseEntity *GetClientEntity( int index, bool hand = false ) {
		typedef CBaseEntity *(__thiscall *OrigFn)( void *, int );
		return getvFunc<OrigFn>(entList, hand ? 4 : 3)( entList, index );
	}
	inline int GetHighestEntityIndex() {
		typedef int (__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(entList, 6)( entList );
	}

	/*
		IEngineTrace
	*/
	inline int GetPointContents( Vector &pos ) {
		typedef int (__thiscall *OrigFn)( void *, Vector &, int, void * );
		return getvFunc<OrigFn>(engTrace, 0)( engTrace, pos, 0xFFFFFFFF, 0 );
	}
	inline void TraceRay( Ray_t &ray, CTraceFilter &filt, CGameTrace &trace, bool wall = false ) {
		typedef void (__thiscall *OrigFn)( void *, Ray_t &, unsigned int, CTraceFilter &, CGameTrace & );
		getvFunc<OrigFn>(engTrace, 5)( engTrace, ray, wall ? 0x200400B : 0x46004003, filt, trace );				// 0x46004003 0x4600400B
	}

	/*
		IPhysicsSurfaceProps
	*/
	inline surfacedata_t *GetSurfaceData( int data ) {
		typedef surfacedata_t *(__thiscall *OrigFn)( void *, int );
		return getvFunc<OrigFn>(surfaceProps, 5)( surfaceProps, data );
	}

	/*
		Material
	*/
	inline IMaterial *FindMaterial( const char *name, const char *type = "Model textures" ) {
		// Model textures - World textures - SkyBox textures
		typedef IMaterial *(__thiscall *OrigFn)( void *, const char *, const char *, bool, void * );
		return getvFunc<OrigFn>(material, 84)( material, name, type, 1, 0 );
	}
	inline void SetBlend( float blend ) {
		typedef void (__thiscall *OrigFn)( void *, float );
		getvFunc<OrigFn>( renderView, 4 )( renderView, blend );
	}
	inline void SetColor( float r, float g, float b ) {
		typedef void (__thiscall *OrigFn)( void *, float * );
		float col[ 3 ];
		col[ 0 ] = r / 255;
		col[ 1 ] = g / 255;
		col[ 2 ] = b / 255;
		col[ 3 ] = 1;
		getvFunc<OrigFn>(renderView, 6)( renderView, col );
	}
	inline void MaterialOverride( IMaterial *mat ) {
		typedef void (__thiscall *OrigFn)( void *, IMaterial *, int, int );
		getvFunc<OrigFn>(modelRender, 1)( modelRender, mat, 0, 0 );
	}

	/*
		IVModelInfo
	*/
	inline const char *GetModelName( void *model ) {
		typedef const char *(__thiscall *OrigFn)( void *, const void * );
		return getvFunc<OrigFn>(modelInfo, 3)( modelInfo, model );
	}
	inline studiohdr_t *GetStudiomodel( const void *model ) {
		typedef studiohdr_t *(__thiscall *OrigFn)( void *, const void * );
		return getvFunc<OrigFn>(modelInfo, 30)( modelInfo, model );
	}

	/*
		IPanel
	*/
	inline const char *GetName( unsigned int vPanel ) {
		typedef const char *(__thiscall *OrigFn)( void *, unsigned int );
		return getvFunc<OrigFn>(panel, 36)( panel, vPanel );
	}

	/*
		cvar
	*/
	ConVar* FindVar(char* var)
	{
		typedef ConVar* (__thiscall* dfn)(void*,char*);
		return getvFunc<dfn>(cvar, 15)(cvar, var);
	}

	/*
		ISurface
	*/
	inline void DrawSetColor( Color col ) {
		typedef void (__thiscall *OrigFn )( void *, Color );
		getvFunc<OrigFn>(surface, 14)( surface, col );
	}
	inline void DrawFilledRect( int x0, int y0, int x1, int y1 ) {
		typedef void (__thiscall *OrigFn)( void*, int, int, int, int );
		getvFunc<OrigFn>(surface, 16)( surface, x0, y0, x1, y1 );      
	}
	inline void DrawOutlinedRect( int x0, int y0, int x1, int y1 ) {
	     typedef void (__thiscall *OrigFn)( void*, int, int, int, int );
	     getvFunc<OrigFn>(surface, 18)( surface, x0, y0, x1, y1 );
	}
	inline void DrawLine( int x0, int y0, int x1, int y1 ) {
		 typedef void (__thiscall *OrigFn)( void*, int, int, int, int );
		 getvFunc<OrigFn>(surface, 19)( surface, x0, y0, x1, y1 );
	}
	inline void DrawSetTextFont( unsigned long font ) {
	     typedef void (__thiscall *OrigFn)( void *, unsigned long );
	     getvFunc<OrigFn>(surface, 23)( surface, font );
	}
	inline void DrawSetTextColor( Color col ) {
	     typedef void (__thiscall *OrigFn)( void*, Color );
	     getvFunc<OrigFn>(surface, 24)( surface, col );
	}
	inline void DrawSetTextPos(int x, int y ) {
	     typedef void (__thiscall *OrigFn)( void*, int, int );
	     getvFunc<OrigFn>(surface, 26)( surface, x, y );
	}
	inline void DrawPrintText(const wchar_t *text, int textLen ) {
		typedef void (__thiscall *OrigFn)( void *, const wchar_t *, int, int );
		return getvFunc<OrigFn>(surface, 28)( surface, text, textLen, 0 );
	}
	inline void DrawSetTextureFile( int id, const char *pFileName, int hardwareFilter, bool forceReload ) {
		typedef void (__thiscall *OrigFn)( void *, int, const char *, int, bool );
		getvFunc<OrigFn>(surface, 37)( surface, id, pFileName, hardwareFilter, forceReload );
	}
	inline void DrawSetTextureRGBA( int id, const unsigned char *rgba, int wide, int tall ) {
		typedef void (__thiscall *OrigFn)( void *, int, const unsigned char *, int, int );
		getvFunc<OrigFn>(surface, 38)( surface, id, rgba, wide, tall );
	}
	inline void DrawSetTexture( int id ) {
		typedef void (__thiscall *OrigFn)( void *, int );
		getvFunc<OrigFn>(surface, 39)( surface, id );
	}
	inline void DrawGetTextureSize( int id, int &w, int &h ) {
		typedef void (__thiscall *OrigFn)( void *, int, int &, int & );
		getvFunc<OrigFn>(surface, 41)( surface, id, w, h );
	}
	inline void DrawTexturedRect( int x, int y, int w, int h ) {
		typedef void (__thiscall *OrigFn)( void *, int, int, int, int );
		getvFunc<OrigFn>(surface, 42)( surface, x, y, w, h );
	}
	inline int CreateNewTextureID( bool procedural ) {
		typedef int (__thiscall *OrigFn)( void *, bool );
		return getvFunc<OrigFn>(surface, 44)( surface, procedural );
	}
	inline unsigned long CreateFont() {
	    typedef unsigned long (__thiscall *OrigFn)( void * );
	    return getvFunc<OrigFn>(surface, 71)( surface );
	}
	inline bool SetFontGlyphSet( unsigned long &font, const char *windowsfont, int tall, int weight, int blur, int scanlines, int flags ) {
	    typedef bool (__thiscall *OrigFn)( void*, unsigned long, const char*, int, int, int, int, int, int, int );
	    return getvFunc<OrigFn>(surface, 72)( surface, font, windowsfont, tall, weight, blur, scanlines, flags, 0, 0 );
	}
	inline void GetTextSize( unsigned long font, const wchar_t *text, int &w, int &h )  {
		typedef void (__thiscall *OrigFn)( void *, unsigned long, const wchar_t*, int &, int & );
		getvFunc<OrigFn>(surface, 79)( surface, font, text, w, h );
	}
}; extern Engine *engine;