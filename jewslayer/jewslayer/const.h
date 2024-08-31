#ifndef __SDK_CONST_H__
#define __SDK_CONST_H__

#ifdef _MSC_VER
#pragma once
#endif

#include <Windows.h>
#include "dt_recv2.h"

#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't z.B. schachtgitter 
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)
#define CONTENTS_BLOCKLIGHT		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define	SURF_LIGHT		0x0001		// value will hold the light strength
#define	SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define	SURF_SKY		0x0004		// don't draw, but add to skybox
#define	SURF_WARP		0x0008		// turbulent water warp
#define	SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define	SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define	SURF_NODRAW		0x0080	// don't bother referencing the texture

#define	SURF_HINT		0x0100	// make a primary bsp splitter

#define	SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOPAINT	SURF_NODECALS	// the surface can not have paint placed on it
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface 
#define SURF_HITBOX		0x8000	// surface is part of a hitbox



// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks fluid movement
#define	MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC_FLUID	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define	MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)


#define PHYSICS_MULTIPLAYER_AUTODETECT	0	// use multiplayer physics mode as defined in model prop data

#define PHYSICS_MULTIPLAYER_SOLID		1	// soild, pushes player away 

#define PHYSICS_MULTIPLAYER_NON_SOLID	2	// nonsolid, but pushed by player

#define PHYSICS_MULTIPLAYER_CLIENTSIDE	3	// Clientside only, nonsolid 	


// ---------------------------
//  Hit Group standards
// ---------------------------
#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10			// alerts NPC, but doesn't do damage or bleed (1/100th damage)

//USERCMD OFFSETS
#define USERCMDOFFSET 0xEC
#define VERIFIEDCMDOFFSET 0xF0
#define MULTIPLAYER_BACKUP 150

//LIFESTATE
#define	LIFE_ALIVE				0 
#define	LIFE_DYING				1 
#define	LIFE_DEAD				2 
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

//BIG TRIGGER CODENZ
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

//USERCMD BUTTONS
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2

//Player flags
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
#define	FL_INWATER				(1<<10)	// In water

inline PVOID*& getvtable( PVOID inst, size_t offset = 0 )
{
	return *reinterpret_cast< PVOID** >( ( size_t )inst + offset );
}
inline const PVOID* getvtable( const void* inst, size_t offset = 0 )
{
	return *reinterpret_cast< const PVOID** >( ( size_t )inst + offset );
}
template< typename Fn >
inline Fn CallVirtual( const void* inst, size_t index, size_t offset = 0 )
{
	return reinterpret_cast< Fn >( getvtable( inst, offset )[ index ] );
}

#define VirtualFn( cast )typedef cast( __thiscall* OriginalFn )

namespace ValveSDK
{	
	class CBaseEntity;
	class CBaseCombatWeapon;

	typedef ULONG EHANDLE;
	typedef ULONG HFont;
	typedef float matrix3x4[ 3 ][ 4 ];

	class ClientClass
	{
	public:
		std::string GetName( void )
		{
			return std::string( *( char** )( this + 0x8 ) );
		}
		RecvTable* GetTable( void )
		{
			return *( RecvTable** )( this + 0xC );
		}
		ClientClass* GetNextClass( void )
		{
			return *( ClientClass** )( this + 0x10 );
		}
		int GetClassID( void )
		{
			return *( int* )( this + 0x14 );
		}
	};

	class Color
	{
	private:
		UCHAR m_Color[ 4 ];

	public:
		Color( void )
		{
			*( ( int* )this ) = 0;
		}
		Color( int r, int g, int b, int a = 255 )
		{
			SetColor( r, g, b, a );
		}
		int r( void ) const
		{
			return m_Color[ 0 ];
		}
		int g( void ) const
		{
			return m_Color[ 1 ];
		}
		int b( void ) const
		{
			return m_Color[ 2 ];
		}
		int a( void ) const
		{
			return m_Color[ 3 ];
		}
		int GetRawColor( void ) const
		{
			return *( ( int* )this );
		}
		Color& operator = ( const Color& other )
		{
			SetRawColor( other.GetRawColor( ) );
			return *this;
		}
		bool operator == ( const Color& other ) const
		{
			return ( *( ( int * )this ) == *( ( int * )&other ) );
		}
		bool operator != ( const Color& other ) const
		{
			return !( operator == ( other ) );
		}
		UCHAR& operator [] ( int iIndex )
		{
			switch( iIndex )
			{
			case 1:
				return m_Color[ 1 ];
			case 2:
				return m_Color[ 2 ];
			case 3:
				return m_Color[ 3 ];
			default:
				return m_Color[ 0 ];
			}
		}
		const UCHAR& operator [] ( int iIndex ) const
		{
			switch( iIndex )
			{
			case 1:
				return m_Color[ 1 ];
			case 2:
				return m_Color[ 2 ];
			case 3:
				return m_Color[ 3 ];
			default:
				return m_Color[ 0 ];
			}
		}
		float* ToFloatPtr( void ) const
		{
			static float pflColor[ 4 ] = { 0.f };

			pflColor[ 0 ] = float( r( ) );
			pflColor[ 1 ] = float( g( ) );
			pflColor[ 2 ] = float( b( ) );
			pflColor[ 3 ] = float( a( ) );

			return pflColor;
		}
		void SetColor( int r, int g, int b, int a = 255 )
		{
			m_Color[ 0 ] = UCHAR( r );
			m_Color[ 1 ] = UCHAR( g );
			m_Color[ 2 ] = UCHAR( b );
			m_Color[ 3 ] = UCHAR( a );
		}
		void SetRawColor( int iColor32 )
		{
			*( ( int* )this ) = iColor32;
		}

	public:
		template< class T > T R( void ) const
		{
			return ( T )m_Color[ 0 ];
		}
		template< class T > T G( void ) const
		{
			return ( T )m_Color[ 1 ];
		}
		template< class T > T B( void ) const
		{
			return ( T )m_Color[ 2 ];
		}
		template< class T > T A( void ) const
		{
			return ( T )m_Color[ 3 ];
		}
	};

	enum BoneList
	{
		BONE_PELVIS,
		BONE_SPINE1,
		BONE_SPINE2,
		BONE_SPINE3,
		BONE_SPINE4,
		BONE_NECK,
		BONE_L_CLAVICLE,
		BONE_L_UPPER_ARM,
		BONE_L_FOREARM,
		BONE_L_HAND,
		BONE_HEAD,
		BONE_FORWARD,
		BONE_R_CLAVICLE,
		BONE_R_UPPER_ARM,
		BONE_R_FOREARM,
		BONE_R_HAND,
		BONE_WEAPON,
		BONE_WEAPON_SLIDE,
		BONE_WEAPON_R_HAND,
		BONE_WEAPON_L_HAND,
		BONE_WEAPON_CLIP1,
		BONE_WEAPON_CLIP2,
		BONE_SILENCER,
		BONE_R_THIGH,
		BONE_R_CALF,
		BONE_R_FOOT,
		BONE_L_THIGH,
		BONE_L_CALF,
		BONE_L_FOOT,
		BONE_L_WEAPON_HAND,
		BONE_R_WEAPON_HAND,
		BONE_L_FORETWIST,
		BONE_L_CALFTWIST,
		BONE_R_CALFTWIST,
		BONE_L_THIGHTWIST,
		BONE_R_THIGHTWIST,
		BONE_L_UPARMTWIST,
		BONE_R_UPARMTWIST,
		BONE_R_FORETWIST,
		BONE_R_TOE,
		BONE_L_TOE,
		BONE_R_FINGER01,
		BONE_R_FINGER02,
		BONE_R_FINGER03,
		BONE_R_FINGER04,
		BONE_R_FINGER05,
		BONE_R_FINGER06,
		BONE_R_FINGER07,
		BONE_R_FINGER08,
		BONE_R_FINGER09,
		BONE_R_FINGER10,
		BONE_R_FINGER11,
		BONE_R_FINGER12,
		BONE_R_FINGER13,
		BONE_R_FINGER14,
		BONE_L_FINGER01,
		BONE_L_FINGER02,
		BONE_L_FINGER03,
		BONE_L_FINGER04,
		BONE_L_FINGER05,
		BONE_L_FINGER06,
		BONE_L_FINGER07,
		BONE_L_FINGER08,
		BONE_L_FINGER09,
		BONE_L_FINGER10,
		BONE_L_FINGER11,
		BONE_L_FINGER12,
		BONE_L_FINGER13,
		BONE_L_FINGER14,
		BONE_L_FINGER15,
		BONE_R_FINGER15,
		BONE_MAX
	};

	enum ButtonCode_t
	{
		BUTTON_CODE_INVALID = -1,
		BUTTON_CODE_NONE = 0,
		KEY_FIRST = 0,
		KEY_NONE = KEY_FIRST,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_PAD_0,
		KEY_PAD_1,
		KEY_PAD_2,
		KEY_PAD_3,
		KEY_PAD_4,
		KEY_PAD_5,
		KEY_PAD_6,
		KEY_PAD_7,
		KEY_PAD_8,
		KEY_PAD_9,
		KEY_PAD_DIVIDE,
		KEY_PAD_MULTIPLY,
		KEY_PAD_MINUS,
		KEY_PAD_PLUS,
		KEY_PAD_ENTER,
		KEY_PAD_DECIMAL,
		KEY_LBRACKET,
		KEY_RBRACKET,
		KEY_SEMICOLON,
		KEY_APOSTROPHE,
		KEY_BACKQUOTE,
		KEY_COMMA,
		KEY_PERIOD,
		KEY_SLASH,
		KEY_BACKSLASH,
		KEY_MINUS,
		KEY_EQUAL,
		KEY_ENTER,
		KEY_SPACE,
		KEY_BACKSPACE,
		KEY_TAB,
		KEY_CAPSLOCK,
		KEY_NUMLOCK,
		KEY_ESCAPE,
		KEY_SCROLLLOCK,
		KEY_INSERT,
		KEY_DELETE,
		KEY_HOME,
		KEY_END,
		KEY_PAGEUP,
		KEY_PAGEDOWN,
		KEY_BREAK,
		KEY_LSHIFT,
		KEY_RSHIFT,
		KEY_LALT,
		KEY_RALT,
		KEY_LCONTROL,
		KEY_RCONTROL,
		KEY_LWIN,
		KEY_RWIN,
		KEY_APP,
		KEY_UP,
		KEY_LEFT,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_CAPSLOCKTOGGLE,
		KEY_NUMLOCKTOGGLE,
		KEY_SCROLLLOCKTOGGLE,
		KEY_LAST = KEY_SCROLLLOCKTOGGLE,
		KEY_COUNT = KEY_LAST - KEY_FIRST + 1,
		MOUSE_FIRST = KEY_LAST + 1,
		MOUSE_LEFT = MOUSE_FIRST,
		MOUSE_RIGHT,
		MOUSE_MIDDLE,
		MOUSE_4,
		MOUSE_5,
		MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
		MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

		MOUSE_LAST = MOUSE_WHEEL_DOWN,
		MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,
	};

	enum ClientClassID
	{
		CAK47 = 1,
		CBASECSGRENADEPROJECTILE = 9,
		CBASEENTITY = 11,
		CBASETRIGGER = 20,
		CCASCADELIGHT = 29,
		CCOLORCORRECTION = 31,
		CCSGAMERULESPROXY = 33,
		CCSPLAYER = 34,
		CCSPLAYERRESOURCE = 35,
		CCSRAGDOLL = 36,
		CCSTEAM = 37,
		CDEAGLE = 38,
		CDECOYGRENADE = 39,
		CDYNAMICPROP = 42,
		CENVTONEMAPCONTROLLER = 57,
		CFOGCONTROLLER = 64,
		CFUNC_DUST = 66,
		CFUNCBRUSH = 69,
		CFUNCOCCLUDER = 74,
		CFUNCROTATING = 76,
		CHEGRENADE = 81,
		CHOSTAGE = 82,
		CHOSTAGECARRIABLEPROP = 83,
		CKNIFE = 88,
		CLIGHTGLOW = 90,
		CPHYSICSPROP = 100,
		CPHYSICSPROPMULTIPLAYER = 101,
		CPOSTPROCESSCONTROLLER = 109,
		CPREDICTEDVIEWMODEL = 112,
		CPROPDOORROTATING = 114,
		CROPEKEYFRAME = 120,
		CSHADOWCONTROL = 123,
		CSMOKESTACK = 127,
		CSPRITE = 130,
		CSUN = 135,
		CVOTECONTROLLER = 192,
		CWEAPONAWP = 196,
		CWEAPONFAMAS = 202,
		CWEAPONGALILAR = 206,
		CWEAPONGLOCK = 207,
		CWEAPONHKP2000 = 208,
		CWEAPONM4A1 = 211,
		CWEAPONMAC10 = 212,
		CWEAPONMP7 = 215,
		CWEAPONMP9 = 216,
		CWEAPONNOVA = 218,
		CWEAPONP250 = 220,
		CWEAPONP90 = 221,
		CWEAPONSG556 = 227,
		CWEAPONSSG08 = 228,
		CWEAPONUMP45 = 232,
		CWEAPONXM1014 = 234,
		CWORLD = 235,
	};

	enum ClientFrameStage_t
	{
		FRAME_UNDEFINED = -1,
		FRAME_START,
		FRAME_NET_UPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_END,
		FRAME_NET_UPDATE_END,
		FRAME_RENDER_START,
		FRAME_RENDER_END
	};

	enum Collision_Group_t
	{
		COLLISION_GROUP_NONE = 0,
		COLLISION_GROUP_DEBRIS,				// Collides with nothing but world and static stuff
		COLLISION_GROUP_DEBRIS_TRIGGER,		// Same as debris, but hits triggers
		COLLISION_GROUP_INTERACTIVE_DEB,	// RIS, // Collides with everything except other interactive debris or debris
		COLLISION_GROUP_INTERACTIVE,		// Collides with everything except interactive debris or debris
		COLLISION_GROUP_PLAYER,
		COLLISION_GROUP_BREAKABLE_GLASS,
		COLLISION_GROUP_VEHICLE,
		COLLISION_GROUP_PLAYER_MOVEMENT,	// For HL2, same as Collision_Group_Player
		COLLISION_GROUP_NPC,				// Generic NPC group
		COLLISION_GROUP_IN_VEHICLE,			// for any entity inside a vehicle
		COLLISION_GROUP_WEAPON,				// for any weapons that need collision detection
		COLLISION_GROUP_VEHICLE_CLIP,		// vehicle clip brush to restrict vehicle movement
		COLLISION_GROUP_PROJECTILE,			// Projectiles!
		COLLISION_GROUP_DOOR_BLOCKER,		// Blocks entities not permitted to get near moving doors
		COLLISION_GROUP_PASSABLE_DOOR,		// Doors that the player shouldn't collide with
		COLLISION_GROUP_DISSOLVING,			// Things that are dissolving are in this group
		COLLISION_GROUP_PUSHAWAY,			// Nonsolid on client and server, pushaway in player code
		COLLISION_GROUP_NPC_ACTOR,			// Used so NPCs in scripts ignore the player.
		LAST_SHARED_COLLISION_GROUP
	};

	enum EFontFlags
	{
		FONTFLAG_NONE,
		FONTFLAG_ITALIC = 0x001,
		FONTFLAG_UNDERLINE = 0x002,
		FONTFLAG_STRIKEOUT = 0x004,
		FONTFLAG_SYMBOL = 0x008,
		FONTFLAG_ANTIALIAS = 0x010,
		FONTFLAG_GAUSSIANBLUR = 0x020,
		FONTFLAG_ROTARY = 0x040,
		FONTFLAG_DROPSHADOW = 0x080,
		FONTFLAG_ADDITIVE = 0x100,
		FONTFLAG_OUTLINE = 0x200,
		FONTFLAG_CUSTOM = 0x400,
		FONTFLAG_BITMAP = 0x800,
	};

	enum FontDrawType_t
	{
		FONT_DRAW_DEFAULT = 0,
		FONT_DRAW_NONADDITIVE,
		FONT_DRAW_ADDITIVE,
		FONT_DRAW_TYPE_COUNT = 2,
	};

	enum HitboxList
	{
		HITBOX_PELVIS,
		HITBOX_L_THIGH,
		HITBOX_L_CALF,
		HITBOX_L_FOOT,
		HITBOX_R_THIGH,
		HITBOX_R_CALF,
		HITBOX_R_FOOT,
		HITBOX_SPINE1,
		HITBOX_SPINE2,
		HITBOX_SPINE3,
		HITBOX_NECK,
		HITBOX_HEAD,
		HITBOX_L_UPPERARM,
		HITBOX_L_FOREARM,
		HITBOX_L_HAND,
		HITBOX_R_UPPERARM,
		HITBOX_R_FOREARM,
		HITBOX_R_HAND,
		HITBOX_L_CLAVICLE,
		HITBOX_R_CLAVICLE,
		HITBOX_HELMET,
		HITBOX_SPINE4,
		HITBOX_MAX,
	};

	enum ItemSchemaIndex
	{
		ITEM_NONE = 0,
		WEAPON_DEAGLE = 1,
		WEAPON_DUALS = 2,
		WEAPON_FIVE7 = 3,
		WEAPON_GLOCK = 4,
		WEAPON_AK47 = 7,
		WEAPON_AUG = 8,
		WEAPON_AWP = 9,
		WEAPON_FAMAS = 10,
		WEAPON_G3SG1 = 11,
		WEAPON_GALIL = 13,
		WEAPON_M249 = 14,
		WEAPON_M4A1 = 16,
		WEAPON_MAC10 = 17,
		WEAPON_P90 = 19,
		WEAPON_UMP45 = 24,
		WEAPON_XM1014 = 25,
		WEAPON_BIZON = 26,
		WEAPON_MAG7 = 27,
		WEAPON_NEGEV = 28,
		WEAPON_SAWEDOFF = 29,
		WEAPON_TEC9 = 30,
		WEAPON_TASER = 31,
		WEAPON_P2000 = 32,
		WEAPON_MP7 = 33,
		WEAPON_MP9 = 34,
		WEAPON_NOVA = 35,
		WEAPON_P250 = 36,
		WEAPON_SCAR20 = 38,
		WEAPON_SG553 = 39,
		WEAPON_SCOUT = 40,
		WEAPON_KNIFE_T = 42,
		WEAPON_FLASH = 43,
		WEAPON_HE = 44,
		WEAPON_SMOKE = 45,
		WEAPON_MOLOTOV = 46,
		WEAPON_DECOY = 47,
		WEAPON_INC = 48,
		WEAPON_C4 = 49,
		WEAPON_KNIFE_CT = 59,
		WEAPON_M4A1S = 60,
		WEAPON_USPS = 61,
		WEAPON_CZ75 = 63,
		WEAPON_MAX = 64,
		WEAPON_KNIFE_BAYONET = 500,
		WEAPON_KNIFE_FLIP = 505,
		WEAPON_KNIFE_GUT = 506,
		WEAPON_KNIFE_KARAMBIT = 507,
		WEAPON_KNIFE_M9BAYONET = 508,
		WEAPON_KNIFE_HUNTSMAN = 509,
		WEAPON_KNIFE_FALCHION = 512,
		WEAPON_KNIFE_BUTTERFLY = 515,
	};

	enum ItemSchemaWeaponType
	{
		WEAPON_TYPE_INVALID = -1,
		WEAPON_TYPE_PISTOLS,
		WEAPON_TYPE_TASER,
		WEAPON_TYPE_SHOTGUN,
		WEAPON_TYPE_SMG,
		WEAPON_TYPE_RIFLE,
		WEAPON_TYPE_MG,
		WEAPON_TYPE_SNIPER,
		WEAPON_TYPE_GRENADE,
		WEAPON_TYPE_KNIFE,
	};

	enum MaterialVarFlags_t
	{
		MATERIAL_VAR_DEBUG = ( 1 << 0 ),
		MATERIAL_VAR_NO_DEBUG_OVERRIDE = ( 1 << 1 ),
		MATERIAL_VAR_NO_DRAW = ( 1 << 2 ),
		MATERIAL_VAR_USE_IN_FILLRATE_MODE = ( 1 << 3 ),
		MATERIAL_VAR_VERTEXCOLOR = ( 1 << 4 ),
		MATERIAL_VAR_VERTEXALPHA = ( 1 << 5 ),
		MATERIAL_VAR_SELFILLUM = ( 1 << 6 ),
		MATERIAL_VAR_ADDITIVE = ( 1 << 7 ),
		MATERIAL_VAR_ALPHATEST = ( 1 << 8 ),
		MATERIAL_VAR_ZNEARER = ( 1 << 10 ),
		MATERIAL_VAR_MODEL = ( 1 << 11 ),
		MATERIAL_VAR_FLAT = ( 1 << 12 ),
		MATERIAL_VAR_NOCULL = ( 1 << 13 ),
		MATERIAL_VAR_NOFOG = ( 1 << 14 ),
		MATERIAL_VAR_IGNOREZ = ( 1 << 15 ),
		MATERIAL_VAR_DECAL = ( 1 << 16 ),
		MATERIAL_VAR_ENVMAPSPHERE = ( 1 << 17 ), // OBSOLETE
		MATERIAL_VAR_ENVMAPCAMERASPACE = ( 1 << 19 ), // OBSOLETE
		MATERIAL_VAR_BASEALPHAENVMAPMASK = ( 1 << 20 ),
		MATERIAL_VAR_TRANSLUCENT = ( 1 << 21 ),
		MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = ( 1 << 22 ),
		MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = ( 1 << 23 ), // OBSOLETE
		MATERIAL_VAR_OPAQUETEXTURE = ( 1 << 24 ),
		MATERIAL_VAR_ENVMAPMODE = ( 1 << 25 ), // OBSOLETE
		MATERIAL_VAR_SUPPRESS_DECALS = ( 1 << 26 ),
		MATERIAL_VAR_HALFLAMBERT = ( 1 << 27 ),
		MATERIAL_VAR_WIREFRAME = ( 1 << 28 ),
		MATERIAL_VAR_ALLOWALPHATOCOVERAGE = ( 1 << 29 ),
		MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = ( 1 << 30 ),
		MATERIAL_VAR_VERTEXFOG = ( 1 << 31 ),
	};

	enum MoveType
	{
		MOVETYPE_NONE = 0,            /**< never moves */
		MOVETYPE_ISOMETRIC,            /**< For players */
		MOVETYPE_WALK,                /**< Player only - moving on the ground */
		MOVETYPE_STEP,                /**< gravity, special edge handling -- monsters use this */
		MOVETYPE_FLY,                /**< No gravity, but still collides with stuff */
		MOVETYPE_FLYGRAVITY,        /**< flies through the air + is affected by gravity */
		MOVETYPE_VPHYSICS,            /**< uses VPHYSICS for simulation */
		MOVETYPE_PUSH,                /**< no clip to world, push and crush */
		MOVETYPE_NOCLIP,            /**< No gravity, no collisions, still do velocity/avelocity */
		MOVETYPE_LADDER,            /**< Used by players only when going onto a ladder */
		MOVETYPE_OBSERVER,            /**< Observer movement, depends on player's observer mode */
		MOVETYPE_CUSTOM,            /**< Allows the entity to describe its own physics */
	};

	enum mp_break_t
	{
		MULTIPLAYER_BREAK_DEFAULT,
		MULTIPLAYER_BREAK_SERVERSIDE,
		MULTIPLAYER_BREAK_CLIENTSIDE,
		MULTIPLAYER_BREAK_BOTH
	};

	enum OverrideType_t
	{
		OVERRIDE_NORMAL = 0,
		OVERRIDE_BUILD_SHADOWS,
		OVERRIDE_DEPTH_WRITE,
		OVERRIDE_SSAO_DEPTH_WRITE,
	};

	enum propdata_interactions_t
	{
		PROPINTER_PHYSGUN_WORLD_STICK,		// "onworldimpact"	"stick"
		PROPINTER_PHYSGUN_FIRST_BREAK,		// "onfirstimpact"	"break"
		PROPINTER_PHYSGUN_FIRST_PAINT,		// "onfirstimpact"	"paintsplat"
		PROPINTER_PHYSGUN_FIRST_IMPALE,		// "onfirstimpact"	"impale"
		PROPINTER_PHYSGUN_LAUNCH_SPIN_NONE,	// "onlaunch"		"spin_none"
		PROPINTER_PHYSGUN_LAUNCH_SPIN_Z,	// "onlaunch"		"spin_zaxis"
		PROPINTER_PHYSGUN_BREAK_EXPLODE,	// "onbreak"		"explode_fire"
		PROPINTER_PHYSGUN_DAMAGE_NONE,		// "damage"			"none"
		PROPINTER_FIRE_FLAMMABLE,			// "flammable"			"yes"
		PROPINTER_FIRE_EXPLOSIVE_RESIST,	// "explosive_resist"	"yes"
		PROPINTER_FIRE_IGNITE_HALFHEALTH,	// "ignite"				"halfhealth"
		PROPINTER_PHYSGUN_CREATE_FLARE,		// "onpickup"		"create_flare"
		PROPINTER_PHYSGUN_ALLOW_OVERHEAD,	// "allow_overhead"	"yes"
		PROPINTER_WORLD_BLOODSPLAT,			// "onworldimpact", "bloodsplat"
		PROPINTER_PHYSGUN_NOTIFY_CHILDREN,	// "onfirstimpact" cause attached flechettes to explode
		PROPINTER_NUM_INTERACTIONS,			// If we get more than 32 of these, we'll need a different system
	};

	enum TraceType_t
	{
		TRACE_EVERYTHING = 0,
		TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
		TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
		TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
	};

	template< class T > T* GetInterface( std::string szModuleName, std::string szInterfaceName, bool bSkip = false )
	{
		if( szModuleName.empty( ) || szInterfaceName.empty( ) )
			return nullptr;
		typedef PVOID( *CreateInterfaceFn )( const char* pszName, int* piReturnCode );
		CreateInterfaceFn hInterface = nullptr;
		while( !hInterface )
		{
			hInterface = ( CreateInterfaceFn )GetProcAddress( GetModuleHandleA( szModuleName.c_str( ) ), "CreateInterface" );
			Sleep( 5 );
		}

		char pszBuffer[ 256 ];
		for( int i = 0; i < 100; i++ )
		{
			sprintf_s( pszBuffer, "%s%0.3d", szInterfaceName.c_str( ), i );
			PVOID pInterface = hInterface( pszBuffer, nullptr );

			if( pInterface && pInterface != NULL )
			{
				if( bSkip )
					sprintf_s( pszBuffer, "%s%0.3d", szInterfaceName.c_str( ), i + 1 );

				Sleep( 5 );
				break;
			}
		}

		return ( T* )hInterface( pszBuffer, nullptr );
	}
}

#endif

