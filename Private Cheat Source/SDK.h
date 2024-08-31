#ifndef SDK_HEADER
#pragma once

#pragma warning( disable : 4819 )

#include <windows.h>
#include <math.h>
#include <xstring>
#include "Vector.h"
#include "Namespace.h"



//#include "public\steam\steam_api.h"


enum class SKINS : UINT {
	NONE = 0,
	STOCK,
	GROUNDWATER, // Groundwater
	CANDYAPPLE, // Candy Apple
	FORESTDDPAT = 5, // Forest DDPAT
	ARCTICCAMO, // Arctic Camo
	DESERTSTORM = 8, // Desert Storm
	BENGALTIGER, // Bengal Tiger
	COPPERHEAD, // Copperhead
	SKULLS, // Skulls
	CRIMSONWEB, // Crimson Web
	BLUESTREAK, // Blue Streak
	REDLAMINATE, // Red Laminate
	GUNSMOKE, // Gunsmoke
	JUNGLETIGER, // Jungle Tiger
	URBANDDPAT, // Urban DDPAT
	VIRUS = 20, // Virus
	GRANITE, // Granite Marbelized
	CONTRAST, // Contrast Spray
	FORESTLEAVES = 25, // Forest Leaves
	LICHEN, // Lichen Dashed
	BONEMASK, // Bone Mask
	ANODIZEDNAVY, // Anodized Navy
	SNAKECAMO = 30, // Snake Camo
	SILVER = 32, // Silver
	HOTROD, // Hot Rod
	METALLICDDPAT, // Metallic DDPAT
	OSSIFIED = 36, // Ossified
	BLAZE = 37, // Blaze
	FADE, // Fade
	BULLDOZER, // Bulldozer
	NIGHT, // Night
	COPPER, // Copper
	BLUESTEEL, // Blue Steel
	STAINED, // Stained
	CASEHARDENED, // Case Hardened
	CONTRACTOR = 46, // Contractor
	COLONY, // Colony
	DRAGONTATTOO, // Dragon Tattoo
	LightningStrike = 51, // Lightning Strike
	Slaughter = 59, // Slaughter
	DarkWater, // Dark Water
	Hypnotic = 61, // Hypnotic
	Bloomstick, // Bloomstick
	ColdBlooded = 67, // Cold Blooded
	CarbonFiber = 70, // Carbon Fiber
	Scorpion, // Scorpion
	SafariMesh, // Safari Mesh
	Wings, // Wings
	PolarCamo, // Polar Camo
	BlizzardMarbelized, // Blizzard Marbelized
	WinterForest, // Winter Forest
	BorealForest, // Boreal Forest
	ForestNight, // Forest Night
	OrangeDDPAT = 83, // Orange DDPAT
	PinkDDPAT, // Pink DDPAT
	Mudder = 90, // Mudder
	Cyanospatter = 92, // Cyanospatter
	Caramel, // Caramel
	Grassland = 95, // Grassland
	BlueSpruce, // Blue Spruce
	Ultraviolet = 98, // Ultraviolet
	SandDune, // Sand Dune
	Storm, // Storm
	Tornado, // Tornado
	Whiteout, // Whiteout
	GrasslandLeaves = 104, // Grassland Leaves
	PolarMesh = 107, // Polar Mesh
	Condemned = 110, // Condemned
	GlacierMesh, // Glacier Mesh
	SandMesh = 116, // Sand Mesh
	SageSpray = 119, // Sage Spray
	JungleSpray = 122, // Jungle Spray
	SandSpray = 124, // Sand Spray
	UrbanPerforated = 135, // Urban Perforated
	WavesPerforated, // Waves Perforated
	OrangePeel = 141, // Orange Peel
	UrbanMasked = 143, // Urban Masked
	JungleDashed = 147, // Jungle Dashed
	SandDashed, // Sand Dashed
	UrbanDashed, // Urban Dashed
	Jungle = 151, // Jungle
	Demolition = 153, // Demolition
	Afterimage, // Afterimage
	BulletRain, // Bullet Rain
	DeathByKitty, // Death By Kitty
	Palm, // Palm
	Walnut, // Walnut
	Brass, // Brass
	Splash = 162, // Splash
	ModernHunter = 164, // Modern Hunter
	SplashJam, // Splash Jam
	BlazeOrange, // Blaze Orange
	RadiationHazard, // Radiation Hazard
	NuclearThreat, // Nuclear Threat
	FalloutWarning, // Fallout Warning
	Predator, // Predator
	IrradiatedAlert, // Irradiated Alert
	BlackLaminate, // Black Laminate
	BOOM = 174, // BOOM
	Scorched, // Scorched
	FadedZebra, // Faded Zebra
	Memento, // Memento
	Doomkitty, // Doomkitty
	NuclearThreat2, // Nuclear Threat
	FireSerpent, // Fire Serpent
	Corticero, // Corticero
	EmeraldDragon, // Emerald Dragon
	Overgrowth, // Overgrowth
	Corticera, // Corticera
	GoldenKoi, // Golden Koi
	WaveSpray, // Wave Spray
	Zirka, // Zirka
	Graven, // Graven
	BrightWater, // Bright Water
	BlackLimba, // Black Limba
	Tempest, // Tempest
	Shattered, // Shattered
	BonePile, // Bone Pile
	Spitfire, // Spitfire
	Demeter, // Demeter
	Emerald, // Emerald
	AnodizedNavy, // Anodized Navy
	Hazard, // Hazard
	DrySeason, // Dry Season
	MayanDreams, // Mayan Dreams
	Palm2, // Palm
	JungleDDPAT, // Jungle DDPAT
	RustCoat, // Rust Coat
	Mosaico, // Mosaico
	Jungle2, // Jungle
	Tornado2, // Tornado
	Facets, // Facets
	SandDune2, // Sand Dune
	Groundwater, // Groundwater
	AnodizedGunmetal, // Anodized Gunmetal
	OceanFoamMP7, // Ocean Foam (MP7)
	Graphite2, // Graphite
	OceanFoamP2000, // Ocean Foam (P2000)
	Graphite, // Graphite
	XRay, // X-Ray
	BlueTitanium, // Blue Titanium
	BloodTiger, // Blood Tiger
	Hexane, // Hexane
	Hive, // Hive
	Hemoglobin, // Hemoglobin
	Serum, // Serum
	BloodInTheWater, // Blood in the Water
	Nightshade, // Nightshade
	WaterSigil, // Water Sigil
	GhostCamo, // Ghost Camo
	BlueLaminate, // Blue Laminate
	ElectricHive, // Electric Hive
	BlindSpot, // Blind Spot
	AzureZebra, // Azure Zebra
	SteelDisruption, // Steel Disruption
	CobaltDisruption, // Cobalt Disruption
	CrimsonWeb, // Crimson Web
	TropicalStorm, // Tropical Storm
	AshWood, // Ash Wood
	VariCamo, // VariCamo
	NightOps, // Night Ops
	UrbanRubble, // Urban Rubble
	VariCamoBlue, // VariCamo Blue
	CaliCamo = 240, // CaliCamo
	HuntingBlind,
	ArmyMesh,
	GatorMesh,
	Teardown,
	ArmyRecon,
	AmberFade,
	RedQuartz,
	CobaltQuartz,
	FullStop,
	PitViper,
	SilverQuartz,
	AcidFade,
	Nitro,
	AsiimovM4,
	Kraken, // The Kraken
	Guardian,
	Mehndi,
	RedlineAWP,
	Pulse,
	Marina,
	RoseIron,
	RisingSkull,
	Sandstorm,
	Kami,
	Magma,
	CobaltHalftone,
	TreadPlate,
	Fuschia, // The Fuschia Is Now
	Victoria,
	Undertow,
	TitaniumBit, // Titanium Bit
	Heirloom,
	CopperGalaxy,
	RedFragCam, // Red FragCam
	Panther, // Panther
	Stainless,
	BlueFissure,
	AsiimovAWP,
	Chameleon, // AUG Chameleon
	CorporalUMP,
	RedlineAK47,
	TrigonP90,
	HeatMAC10,
	Terrain,
	AntiqueNova, // Nova Antique
	PulseSG553, // SG553 Pulse
	Sergeant,
	Sandstorm3,
	HeavenGuardMAG7, // MAG-7 Heaven Guard
	DeathRattle = 293, // Sawed-Off Death Rattle
	GreenApple,
	Franklin,
	Meteorite,
	Tuxedo, // Galil Tuxedo
	ArmySheen,
	CagedSteel,
	EmeraldPinstripe, // AK-47 Emerald Pinstripe
	AtomicAlloy, // M4A1-S Atomic Alloy
	Vulcan, // AK-47 Vulcan
	Isaac, // Tec-9 Isaac
	Slashed, // SSG08 Slashed
	Torque, // AUG Torque
	AntiqueBizon, // PP-Bizon Antique
	Retribution, // Duals Retribution
	Howl,
	Curse,
	DesertWarfare,
	Cyrex,
	Orion,
	HeavenGuardXM1014,
	PoisonDart,
	Jaguar, // AK-47 Jaguar
	Bratatat, // Negev Bratatat
	RoadRash, // USP-S Road Rash
	Detour,
	RedPython,
	MasterPiece, // M4A1-S Master Piece
	NitroCZ, // CZ-75 Nitro
	
	Chalice = 325,
	Knight,
	Chainmail,
	HandCannon,
	DarkAge,
	Briar,
	RoyalBlue = 332,
	Indigo,
	Twist,
	Module,
	DesertStrike, // Desert-Strike
	Tatter,
	PulseP2000,
	Caiman,
	JetSet, // AK-47 Jet Set
	FirstClassAK47, // AK-47 First Class
	Leather, // P90 Leather
	Commuter,
	DragonLore, // AWP Dragon Lore
	FirstClassSawed, // Sawed-Off First Class
	CoachClass, // P2000 Coach Class
	Pilot,
	RedLeather,
	Osiris,
	Tigris, // CZ-75 Tigris
	Conspiracy,
	FowlPlay,
	WaterElemental, // Glock-18 Water Elemental
	UrbanHazard,
	DesertStrikeNegev, // Negev Desert-Strike
	Koi,
	Ivory,
	Supernova,
	AsiimovP90, // P90 Asiimov
	CyrexM4, // M4A1-S Cyrex
	Abyss,
	Labyrinth, // UMP Labyrinth
	Traveler, // SG553 Traveler
	BusinessClass, // USP-S Business Class
	OlivePlaid,
	GreenPlaid,
	Reactor,
	SettingSun,
	NuclearWaste,
	BoneMachine,
	Styx,
	NuclearGarden,
	Contamination,
	Toxic,
	
	ChemicalGreen,
	HotShot,
	Cerberus,
	WastelandRebel, // AK-47 Wasteland Rebel
	Grinder,
	Murky,
	Basilisk,
	Griffin,
	Firestarter,
	Dart,

	CartelP250, // P250 Cartel
	FireElemental,
	Highwayman, // Sawed-Off Highwayman
	Cardiac,
	Delusion,
	Tranquility,
	CartelAK, // AK-47 Cartel
	ManoWar, // Man-o'-War
	UrbanShock,
	Naga, // DEagle Naga
	Chatterbox, // Galil Chatterbox
	Catacombs,
	DragonKing, // Dragon King
	SystemLock,
	Malachite,
	DeadlyPoison,
	Muertos,
	Serenity,
	Grotto,
	Quicksilver,
	TigerTooth = 409,
	DamascusSteel,
	DamascusSteel2,
	MarbleFade = 413,
	Doppler,
	Doppler2,
	Doppler3,
	Doppler4,
	Doppler5,
	Doppler6,
	Doppler7,
};



#include "getvfunc.h"
#include "dt_recv2.h"
#include "CBaseAPI.h"
#include "WeaponList.h"
#include "CGlobalVars.h"
#include "VMT Hook.h"
#include "checksum_crc.h"
//#include "bspflags.h"
#include "Math.h"
#define MakePtr( Type, dwBase, dwOffset ) ( ( Type )( DWORD( dwBase ) + (DWORD)( dwOffset ) ) )





using namespace std;

typedef void* ( __cdecl* CreateInterface_t )( const char*, int* );
typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy",on)
#pragma warning( disable : 4244 ) // Possible loss of data
#pragma warning( disable : 4091 ) // typedef warning

typedef float matrix3x4[3][4];

#define	FL_ONGROUND (1<<0)
#define FL_DUCKING (1<<1)
#define CONTENTS_HITBOX 0x40000000
#define FLOW_OUTGOING 0
#define FLOW_INCOMING 1
#define PI 3.14159265358979323846f
//#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define RADPI 57.295779513082f // 180 / pi
#define SQUARE( a ) a*a

enum FontDrawType_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

class CPrediction
{
public:
	bool InPrediction()
	{
		typedef bool(__thiscall* oInPrediction)(void*);
		return getvfunc< oInPrediction >(this, 14)(this);
	}
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

template< class T > inline T* makeptr(void* pObj, unsigned int offset)
{
	return reinterpret_cast< T* >(reinterpret_cast< unsigned char* >(pObj)+offset);
}

class CGlobalVarsBase
{
public:
	CGlobalVarsBase(bool bIsClient);
	bool IsClient() const;
	int GetNetworkBase(int nTick, int nEntity);
	float   realtime;
	int    framecount;
	float   absoluteframetime;
	float   shit;
	float   curtime;
	float   frametime;
	int    maxClients;
	int    tickcount;
	float   interval_per_tick;
	float   interpolation_amount;
	int    simTicksThisFrame;
	int    network_protocol;
	void     *pSaveData;
	bool   m_bClient;
	int    nTimestampNetworkingBase;
	int    nTimestampRandomizeWindow;
};


class Color
{
public:
	// constructors
	Color()
	{
		*((int *)this) = 0;
	}
	Color(int r, int g, int b)
	{
		SetColor(r, g, b, 0);
	}
	Color(int r, int g, int b, int a)
	{
		SetColor(r, g, b, a);
	}
	void SetColor(int r, int g, int b, int a = 0)
	{
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)a;
	}

	void GetColor(int &r, int &g, int &b, int &a) const
	{
		r = _color[0];
		g = _color[1];
		b = _color[2];
		a = _color[3];
	}

	void SetRawColor(int color32)
	{
		*((int *)this) = color32;
	}

	int GetRawColor() const
	{
		return *((int *)this);
	}

	inline int r() const	{ return _color[0]; }
	inline int g() const	{ return _color[1]; }
	inline int b() const	{ return _color[2]; }
	inline int a() const	{ return _color[3]; }

	unsigned char &operator[](int index)
	{
		return _color[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const Color &rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator != (const Color &rhs) const
	{
		return !(operator==(rhs));
	}

	Color &operator=(const Color &rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

private:
	unsigned char _color[4];
};

class player_info_t
{
public:
	char unknown0[0x10];
	char name[32];
	char unknown2[0x200];
};

class ClientClass
{
public:
	const char* GetName( void )
	{
		return *(char**)(this+0x8);
	}
	RecvTable* GetTable( )
	{
		return *(RecvTable**)(this+0xC);
	}
	ClientClass* NextClass( )
	{
		return *(ClientClass**)(this+0x10);
	}
	int GetClassID( void )
	{
		return *(int*)(this+0x14);
	}
};

class IVModelInfo
{
public:
	const char* GetModelName( DWORD* model )
	{
		typedef const char* ( __thiscall* OriginalFn )( PVOID, DWORD* );
		return getvfunc<OriginalFn>( this, 3 )( this, model );
	}
};


class CHLClient
{
public:
	ClientClass* GetAllClasses( void )
	{
		typedef ClientClass* ( __thiscall* OriginalFn )( PVOID ); //Anything inside a VTable is a __thiscall unless it completly disregards the thisptr. You can also call them as __stdcalls, but you won't have access to the __thisptr.
		return getvfunc<OriginalFn>( this, 8 )( this ); //Return the pointer to the head CClientClass.
	}
};



class CGlobals
{
public:
	float realtime;
	int framecount;
	float absoluteframetime;
	float curtime;
	float frametime;
	int maxclients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,	// never moves
	MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,				// Player only - moving on the ground
	MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,				// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
	MOVETYPE_PUSH,				// no clip to world, push and crush
	MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,			// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

	// should always be defined as the last item in the list
	MOVETYPE_LAST = MOVETYPE_CUSTOM,

	MOVETYPE_MAX_BITS = 4
};

#define    HITGROUP_GENERIC    0
#define    HITGROUP_HEAD        1
#define    HITGROUP_CHEST        2
#define    HITGROUP_STOMACH    3
#define HITGROUP_LEFTARM    4    
#define HITGROUP_RIGHTARM    5
#define HITGROUP_LEFTLEG    6
#define HITGROUP_RIGHTLEG    7
#define HITGROUP_GEAR        10            // alerts NPC, but doesn't do damage or bleed 


#include "checksum_crc.h"

class CEntityGroundContact
{
public:
	int                             entindex;
	float                           minheight;
	float                           maxheight;
};

class CUserCmd
{
public:
	CUserCmd()
	{
		Reset();
	}

	virtual ~CUserCmd();

	void Reset()
	{
		command_number = 0;
		tick_count = 0;
		viewangles.Init();
		forwardmove = 0.0f;
		sidemove = 0.0f;
		upmove = 0.0f;
		buttons = 0;
		impulse = 0;
		weaponselect = 0;
		weaponsubtype = 0;
		random_seed = 0;
		mousedx = 0;
		mousedy = 0;
		headangles.Init();
		headoffset.Init();

		hasbeenpredicted = false;
#if defined( HL2_DLL ) || defined( HL2_CLIENT_DLL )
		entitygroundcontact.RemoveAll();
#endif
	}

	CUserCmd& operator =(const CUserCmd& src)
	{
		if (this == &src)
			return *this;

		command_number = src.command_number;
		tick_count = src.tick_count;
		viewangles = src.viewangles;
		forwardmove = src.forwardmove;
		sidemove = src.sidemove;
		upmove = src.upmove;
		buttons = src.buttons;
		impulse = src.impulse;
		weaponselect = src.weaponselect;
		weaponsubtype = src.weaponsubtype;
		random_seed = src.random_seed;
		mousedx = src.mousedx;
		mousedy = src.mousedy;

		hasbeenpredicted = src.hasbeenpredicted;
		headangles = src.headangles;
		headoffset = src.headoffset;

#if defined( HL2_DLL ) || defined( HL2_CLIENT_DLL )
		entitygroundcontact = src.entitygroundcontact;
#endif

		return *this;
	}

	CUserCmd(const CUserCmd& src)
	{
		*this = src;
	}

	CRC32_t GetChecksum(void) const
	{
		CRC32_t crc;

		CRC32_Init(&crc);
		CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
		CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
		CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
		CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
		CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
		CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
		CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
		CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
		CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
		CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
		CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
		CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
		CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
		CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));
		//CRC32_ProcessBuffer( &crc, &hasbeenpredicted, sizeof( hasbeenpredicted ) );
		//CRC32_ProcessBuffer( &crc, &headangles, sizeof( headangles ) );
		//CRC32_ProcessBuffer( &crc, &headoffset, sizeof( headoffset ) );        
		CRC32_Final(&crc);

		return crc;
	}

	int        command_number;
	int        tick_count;
	Vector  viewangles;
	Vector    aimdirection;
	float    forwardmove;
	float    sidemove;
	float    upmove;
	int        buttons;
	BYTE    impulse;
	int        weaponselect;
	int        weaponsubtype;
	int        random_seed;
	short    mousedx;
	short    mousedy;
	bool    hasbeenpredicted;
	Vector  headangles;
	Vector    headoffset;

#if defined( HL2_DLL ) || defined( HL2_CLIENT_DLL )
	CUtlVector< CEntityGroundContact > entitygroundcontact;
#endif
};

class CInput
{
public:
	virtual        void        Init_All(void);
	virtual        void        Shutdown_All(void);
	virtual        int            GetButtonBits(int);
	virtual        void        CreateMove(int sequence_number, float input_sample_frametime, bool active);
	virtual        void        ExtraMouseSample(float frametime, bool active);
	virtual        bool        WriteUsercmdDeltaToBuffer(int *buf, int from, int to, bool isnewcommand);
	virtual        void        EncodeUserCmdToBuffer(int buf, int slot);
	virtual        void        DecodeUserCmdFromBuffer(int buf, int slot);
	virtual        CUserCmd    *GetUserCmd(int uk, int sequence_number);

	class CVerifiedUserCmd
	{
	public:
		CUserCmd        m_cmd;
		CRC32_t         m_crc;
	};
};



class CBaseEntity
{
public:

	bool IsProtected()
	{
		return *reinterpret_cast< bool* >((DWORD)this + 0x1C04);
	}

	Vector GetOrigin()
	{
		return *reinterpret_cast< Vector* >(reinterpret_cast< int >(this)+0x134);
	}
	Vector& GetAbsOrigin( )
	{
		typedef Vector& ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>(this, 10)(this);
	}
	Vector& GetAbsAngles( )
	{
		typedef Vector& ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>(this, 11)(this);
	}
	ClientClass* GetClientClass( )
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef ClientClass* ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( pNetworkable, 2 )( pNetworkable );
	}

	bool IsDormant( )
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( pNetworkable, 9 )( pNetworkable );
	}

	

	bool IsDefusing()
	{
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)ALX.pPlayerVariables->m_bIsDefusing);
	}

	int m_iShotsFired()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x1D58);
	}


	int GetIndex( )
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef int ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( pNetworkable, 10 )( pNetworkable );	
	}
	bool SetupBones( matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
	{
		PVOID pRenderable = (PVOID)(this + 0x4);
		typedef bool ( __thiscall* OriginalFn )( PVOID, matrix3x4*, int, int, float );
		return getvfunc<OriginalFn>( pRenderable, 13 )( pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime );
	}

	DWORD* GetModel( )
	{
		PVOID pRenderable = (PVOID)(this + 0x4);
		typedef DWORD* ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( pRenderable, 8 )( pRenderable );
	}
	const char* GetModelName()
	{
		return ALX.pModelInfo->GetModelName(this->GetModel());
	}
	int GetCrosshairID()
	{
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x23F8);
	}
	int GetTeamNum()
	{
		return *reinterpret_cast< int* >((DWORD)this + (DWORD)0xF0);
	}
	int State()
	{
		return *reinterpret_cast< int* >((DWORD)this + 0x15B4);
	}
	
	float C4Timer()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xA7BA14);
	}
	int GetFlags()
	{
		return *reinterpret_cast< int* >((DWORD)this + (DWORD)0x100);
	}

	int m_flnextprimaryattack()
	{
		 return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x159C);
		//return *MakePtr(int*, BaseEnt(), 0x159C);
	}

	 int m_Clip()
	 {
		 return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x15C0);
		//return *MakePtr(int*, BaseEnt(), 0x15C0);
	 }

	Vector GetAngles()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x189C);
	}

	Vector GetEyeAngles()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x239C);

	}
	Vector GetVisualPunch()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x64);
	}

	Vector GetAimPunch()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x70);
	}

	Vector* GetAnglesPLUS()
	{
		return *reinterpret_cast<Vector**>((DWORD)this + (DWORD)0x189C);
	}

	int WeaponID()
	{
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x1684);
	}
	Vector GetPunchAngle()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)+0x13DC);
	}

	Vector* GetPunchAnglePLUS()
	{
		return *reinterpret_cast<Vector**>((DWORD)this + (DWORD)+0x13DC);
	} 

	Vector* GetPunchAngles()
	{
		return (Vector*)((DWORD)this + 0x13DC);
	}

	Vector GetVelocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)+0x110);
	}

	Vector PunchAngle(CBaseEntity* pEntity)
	{
		return *reinterpret_cast<Vector*>(reinterpret_cast<int>(pEntity)+0x13DC);
	}
	Vector PunchVisualAngle(CBaseEntity* pEntity)
	{


		return *reinterpret_cast<Vector*>(reinterpret_cast<int>(pEntity)+0x13D0);
	}

	int GetHealth()
	{
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)ALX.pPlayerVariables->m_iHealth);
	}

	float fNextAttack()
	{
		int offset = 0x159C;
		//float NextAttack = *MakePtr< float >(this, offset);

		return *reinterpret_cast<float*>((DWORD)this + offset); 
	}

	void GetRenderBounds(Vector& mins, Vector& maxs)
	{
		PVOID pRenderable = (PVOID)(this + 0x4);
		typedef void(__thiscall* OriginalFn)(PVOID, Vector&, Vector&);
		getvfunc<OriginalFn>(pRenderable, 20)(pRenderable, mins, maxs);
	}


	int GetTickBase()
	{
		int offset = 0x17C0;
		int ServerTime = *makeptr< int >(this, offset);

		return ServerTime;
	}

};



class CNetChannelInfo
{
public:
	virtual const char  *GetName(void) const = 0;
	virtual const char  *GetAddress(void) const = 0;
	virtual float		GetTime(void) const = 0;
	virtual float		GetTimeConnected(void) const = 0;
	virtual int			GetBufferSize(void) const = 0;
	virtual int			GetDataRate(void) const = 0;

	virtual bool		IsLoopback(void) const = 0;
	virtual bool		IsTimingOut(void) const = 0;
	virtual bool		IsPlayback(void) const = 0;

	virtual float		GetLatency(int flow) const = 0;
	virtual float		GetAvgLatency(int flow) const = 0;
	virtual float		GetAvgLoss(int flow) const = 0;
	virtual float		GetAvgChoke(int flow) const = 0;
	virtual float		GetAvgData(int flow) const = 0;
	virtual float		GetAvgPackets(int flow) const = 0;
	virtual int			GetTotalData(int flow) const = 0;
	virtual int			GetTotalPackets(int flow) const = 0;
	virtual int			GetSequenceNr(int flow) const = 0;
	virtual bool		IsValidPacket(int flow, int frame_number) const = 0;
	virtual float		GetPacketTime(int flow, int frame_number) const = 0;
	virtual int			GetPacketBytes(int flow, int frame_number, int group) const = 0;
	virtual bool		GetStreamProgress(int flow, int *received, int *total) const = 0;
	virtual float		GetTimeSinceLastReceived(void) const = 0;
	virtual	float		GetCommandInterpolationAmount(int flow, int frame_number) const = 0;
	virtual void		GetPacketResponseLatency(int flow, int frame_number, int *pnLatencyMsecs, int *pnChoke) const = 0;
	virtual void		GetRemoteFramerate(float *pflFrameTime, float *pflFrameTimeStdDeviation) const = 0;

	virtual float		GetTimeoutSeconds() const = 0;
};

class CViewSetup
{
private:
	char pad[0xC4];
public:

	Vector angles;

};

class EngineClient
{
public:

	void GetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* oGetViewAngles)(PVOID, Vector&);
		return getvfunc< oGetViewAngles >(this, 18)(this, vAngles);
	}

	void SetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* oSetViewAngles)(PVOID, Vector&);
		return getvfunc< oSetViewAngles >(this, 19)(this, vAngles);
	}
	// 5	CEngineClient::GetScreenSize(int &,int &)
	void GetScreenSize( int& width, int& height )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int& , int& );
		return getvfunc<OriginalFn>( this, 5 )( this, width, height );
	}
	// 8	CEngineClient::GetPlayerInfo(int,player_info_s *)
	bool GetPlayerInfo( int ent_num, player_info_t *pinfo )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID, int, player_info_t * );
		return getvfunc<OriginalFn>(this, 8)(this, ent_num, pinfo );
	}
	// 11	CEngineClient::Con_IsVisible(void)
	bool Con_IsVisible( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 11 )( this );
	}
	// 12	CEngineClient::GetLocalPlayer(void)
	int GetLocalPlayer( void )
	{
		typedef int ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 12 )( this );
	}
	// 14	CEngineClient::Time(void)
	float Time( void )
	{
		typedef float ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 14 )( this );
	}
	// 26	CEngineClient::IsInGame(void)
	// 27	CEngineClient::IsConnected(void)
	// 28	CEngineClient::IsDrawingLoadingImage(void)
	bool IsInGame( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 26 )( this );
	}
	bool IsConnected( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 27 )( this );
	}
	bool IsDrawingLoadingImage( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 28 )( this );
	}
	// 37	CEngineClient::WorldToScreenMatrix(void)
	const matrix3x4& WorldToScreenMatrix( void )
	{
		typedef const matrix3x4& ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>(this, 37)(this);
	}
	// 89	CEngineClient::IsTakingScreenshot(void)
	bool IsTakingScreenshot( void )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 89 )( this );
	}

	CNetChannelInfo* GetNetChannelInfo()
	{
		typedef CNetChannelInfo* (__thiscall* oFunc)(void*);
		return getvfunc< oFunc >(this, 78)(this);//not 75
	}

	// Not recommended to use this
	// 110	CEngineClient::ClientCmd_Unrestricted(char  const*)
	void ClientCmd_Unrestricted( const char* chCommandString )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, const char * );
		return getvfunc<OriginalFn>( this, 113 )( this, chCommandString );
	}
	// Safe, but was hugely restricted
	// 105	CEngineClient::ExecuteClientCmd(char  const*)
	void ExecuteClientCmd( const char* chCommandString )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, const char * );
		return getvfunc<OriginalFn>( this, 108 )( this, chCommandString );
	}
};

class IPanel
{
public:
	const char *GetName(unsigned int vguiPanel)
	{
		typedef const char* ( __thiscall* OriginalFn )( PVOID, unsigned int );
		return getvfunc<OriginalFn>( this, 36 )( this, vguiPanel );
	}
	// 41	VPanelWrapper::PaintTraverse(unsigned int,bool,bool)
	void PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
	{
		typedef void (__thiscall* OriginalFn) (PVOID, unsigned int,bool,bool);
		return getvfunc<OriginalFn> (this , 41) (this,vguiPanel,forceRepaint,allowForce);
	}
};

class ISurface
{
public:

	void DrawSetColor( int r, int g, int b, int a )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int, int, int );
		getvfunc<OriginalFn>( this, 13 )( this, r,g,b,a);
	}
	void DrawSetColor(DWORD colorcode)
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, DWORD );
		getvfunc<OriginalFn>( this, 13 )( this, colorcode);
	}
	void DrawSetColor(Color colour)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Color);
		getvfunc<OriginalFn>(this, 13)(this, colour);
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int, int, int );
		getvfunc<OriginalFn>( this, 15 )( this, x0, y0, x1, y1 );	
	}
	// 17	CMatSystemSurface::DrawOutlinedRect(int,int,int,int)
	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int, int, int );
		getvfunc<OriginalFn>( this, 17 )( this, x0, y0, x1, y1 );
	}
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* oDrawLine)(PVOID, int, int, int, int);
		return getvfunc< oDrawLine >(this, 18)(this, x0, y0, x1, y1);
	}

	void DrawSetTextFont(unsigned long font)
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, unsigned long );
		getvfunc<OriginalFn>( this, 22 )( this, font );
	}
	void DrawSetTextColor(DWORD colorcode )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, DWORD );
		getvfunc<OriginalFn>( this, 23 )( this, colorcode);
	}
	void DrawSetTextColor1(Color colorcode)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Color);
		getvfunc<OriginalFn>(this, 23)(this, colorcode);
	}
	void DrawSetTextColor( int r, int g, int b, int a )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int, int, int );
		getvfunc<OriginalFn>( this, 23 )( this, r,g,b,a);
	}
	// 25	CMatSystemSurface::DrawSetTextPos(int,int)
	void DrawSetTextPos(int x, int y )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, int, int );
		getvfunc<OriginalFn>( this, 25 )( this, x, y );
	}
	// 27	CMatSystemSurface::DrawPrintText(wchar_t  const*,int,FontDrawType_t)
	void DrawPrintText(const wchar_t *text, int textLen )
	{
		typedef void ( __thiscall* OriginalFn )( PVOID, const wchar_t *, int, int );
		return getvfunc<OriginalFn>( this, 27 )( this, text, textLen, 0 );
	}

	bool GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
	{
		typedef bool(__thiscall* oGetTextSize)(PVOID, unsigned long, const wchar_t*, int&, int&);
		return getvfunc< oGetTextSize >(this, 78)(this, font, text, wide, tall);
	}

	void DrawPrintText1(wchar_t *text, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT)
	{
		typedef void(__thiscall* oDrawPrintText)(PVOID, wchar_t*, int, FontDrawType_t);
		return getvfunc< oDrawPrintText >(this, 27)(this, text, textLen, drawType);
	}
	// 70	CMatSystemSurface::CreateFont(void)
	// 71	CMatSystemSurface::SetFontGlyphSet(unsigned long,char  const*,int,int,int,int,int,int,int)
	unsigned long CreateFont( )
	{
		typedef unsigned long ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 70 )( this );
	}
	bool SetFontGlyphSet (unsigned long &font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags )
	{
		typedef bool ( __thiscall* OriginalFn )( PVOID, unsigned long, const char*, int, int, int, int, int, int, int );
		return getvfunc<OriginalFn>( this, 71 )( this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0 );
	}
	void DrawOutlinedCircle(int x, int y, int radius, int segments)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		return getvfunc<OriginalFn>(this, 102)(this, x, y, radius, segments);
	}
	void UnlockCursor()
	{
		typedef void(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 60)(this);
	}
	void LockCursor()
	{
		typedef void(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 61)(this);
	}
};



class CEntList
{
public:
	CBaseEntity* GetClientEntity( int entnum )	
	{
		typedef CBaseEntity* ( __thiscall* OriginalFn )( PVOID, int );
		return getvfunc<OriginalFn>( this, 3 )( this, entnum );
	}
	CBaseEntity* GetClientEntityFromHandle( int hEnt )
	{
		typedef CBaseEntity* ( __thiscall* OriginalFn )( PVOID, int );
		return getvfunc<OriginalFn>( this, 4 )( this, hEnt );
	}
	int GetHighestEntityIndex(void)
	{
		typedef int ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 6 )( this );
	}
};

enum playercontrols
{
	IN_ATTACK = (1 << 0),
	IN_JUMP	= (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_ALT1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),	// Used by client.dll for when scoreboard is held down
	IN_SPEED = (1 << 17),	// Player is holding the speed key
	IN_WALK = (1 << 18),	// Player holding walk key
	IN_ZOOM	= (1 << 19),	// Zoom key for HUD zoom
	IN_WEAPON1 = (1 << 20),	// weapon defines these bits
	IN_WEAPON2 = (1 << 21),	// weapon defines these bits
	IN_BULLRUSH = (1 << 22),
};

enum bones_t {
	Bone_Pelvis, // Kreutz
	Bone_Spine_1,//wirbelsäule
	Bone_Spine_2,//wirbelsäule
	Bone_Spine_3,//wirbelsäule
	Bone_Spine_4,//wirbelsäule
	Bone_Neck,//nacken
	Bone_Left_Clavicle,//schlüsselbein
	Bone_Left_UpperArm,
	Bone_Left_ForeArm,
	Bone_Left_Hand,
	Bone_Head,
	Bone_forward,
	Bone_Right_Clavicle, //schlüsselbein
	Bone_Right_UpperArm, //unterarm kp
	Bone_Right_ForeArm, //vorderarm
	Bone_Right_Hand,
	Bone_weapon,
	Bone_weapon_slide,
	Bone_weapon_Right_Hand,
	Bone_weapon_Left_Hand,
	Bone_weapon_Clip1,
	Bone_weapon_Clip2,
	Bone_Right_Thigh,//schenkel
	Bone_Right_Calf,//hüfte
	Bone_Right_Foot,
	Bone_Left_Thigh, //schenkel
	Bone_Left_Calf,//hüfte
	Bone_Left_Foot, //fuß
	Bone_Left_ForeTwist,
	Bone_Left_CalfTwist,//Ende der hände  und spackt rum auf gewisse distanz
	Bone_Right_CalfTwist, //Ende der hände  und spackt rum auf gewisse distanz
	Bone_Left_ThighTwist,
	Bone_Right_ThighTwist,
	Bone_Left_UpArmTwist,
	Bone_Right_UpArmTwist,
	Bone_Right_ForeTwist,
	Bone_Right_Toe, //zeh
	Bone_Left_Toe,//zeh
	Bone_Right_Finger01,
	Bone_Right_Finger02,
	Bone_Right_Finger03,
	Bone_Right_Finger04,
	Bone_Right_Finger05,
	Bone_Right_Finger06,
	Bone_Right_Finger07,
	Bone_Right_Finger08,
	Bone_Right_Finger09,
	Bone_Right_Finger10,
	Bone_Right_Finger11,
	Bone_Right_Finger12,
	Bone_Right_Finger13,
	Bone_Right_Finger14,
	Bone_Left_Finger01,
	Bone_Left_Finger02,
	Bone_Left_Finger03,
	Bone_Left_Finger04,
	Bone_Left_Finger05,
	Bone_Left_Finger06,
	Bone_Left_Finger07,
	Bone_Left_Finger08,
	Bone_Left_Finger09,
	Bone_Left_Finger10,
	Bone_Left_Finger11,
	Bone_Left_Finger12,
	Bone_Left_Finger13,
	Bone_Left_Finger14,
	Bone_Left_Finger15,
	Bone_Right_Finger15
};

enum source_lifestates
{
	LIFE_ALIVE,
	LIFE_DYING, // Bodies was not hitting to the ground
	LIFE_DEAD, // Bodies that touched the ground, and was waiting for discard
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY, // Model discarded,
};


/*class CInput
{
public:
	virtual		void		Init_All(void);
	virtual		void		Shutdown_All(void);
	virtual		int			GetButtonBits(int);
	virtual		void		CreateMove(int sequence_number, float input_sample_frametime, bool active);
	virtual		void		ExtraMouseSample(float frametime, bool active);
	virtual		bool		WriteUsercmdDeltaToBuffer( /*bf_write*//*int *buf, int from, int to, bool isnewcommand);*/
	//virtual		void		EncodeUserCmdToBuffer( /*bf_write&*/ int buf, int slot);
	//virtual		void		DecodeUserCmdFromBuffer( /*bf_read&*/int buf, int slot);
	/*
	CUserCmd* GetUserCmd(int nSlot, int seq)
	{
		typedef CUserCmd* (__thiscall* OriginalFn)(PVOID, int, int);
		return getvfunc<OriginalFn>(this, 8)(this, nSlot, seq);
	}

	class CVerifiedUserCmd
	{
	public:
		CUserCmd        m_cmd;
		CRC32_t         m_crc;
	};

	CUserCmd         *m_pCommands;
	CVerifiedUserCmd *m_pVerifiedCommands;
};*/

#define MakePtr( Type, dwBase, dwOffset ) ( ( Type )( DWORD( dwBase ) + (DWORD)( dwOffset ) ) )

struct GlowObjectDefinition_t
{
	CBaseEntity *pEntity;
	float r;
	float g;
	float b;
	float a;
	byte unk1[16];
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloom;
	byte unk2[10];
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



struct Hitbox_t
{
	int       iBone;
	Vector    vMin;
	Vector    vMax;
	void Setup(int bone, Vector min, Vector max)
	{
		iBone = bone;
		vMin = min;
		vMax = max;
	}
};

extern Hitbox_t    Hitbox[21];


class C_BaseCombatWeapon : public CBaseEntity
{
private:
	DWORD    dwBase;

public:
	C_BaseCombatWeapon(DWORD dwAddr);
	DWORD    GetCombatWeapon();
	int      GetWeaponID();

	int m_Clip()
	{
		int offset = 0x15c0;
		int clip = *makeptr< float >(this, offset);

		return offset;
	}

	float fNextAttack2()
	{
		int offset = 0x159C;
		float NextAttack = *makeptr< float >(this, offset);

		return NextAttack;
	}

	int getweaponid()
	{
		int offset = 0x1148 + 0x40 + 0x194;

		int weaponid = *makeptr<int>(this, offset);
		return weaponid;
	}


	void PaintKit1(int t)
	{
		int* PaintKit1 = makeptr< int >(this, ALX.pPlayerVariables->m_kit1);

		*PaintKit1 = t;
	}

	void PaintKit2(int t)
	{
		int* PaintKit2 = makeptr< int >(this, ALX.pPlayerVariables->m_kit2);

		*PaintKit2 = t;
	}

	int getweaponid2()
	{
		
		int offset = 0x1148 + 0x40 + 0x194;
		int PaintKit = *makeptr< int >(this, offset);
		return PaintKit;
	}

	void SetPaintKit(int arg)
	{
		int something = 0x0;
		
		int offset = 0x14F8 + 0x40 + something;
		int* PaintKit = makeptr< int >(this, offset);

		*PaintKit = arg;
	}

	void SetweaponidB(int arg)
	{
		int offset = 0x1148 + 0x40 + 0x194;
		int* PaintKit = makeptr< int >(this, offset);

		*PaintKit = arg;
	}

	void SetPaintKitNew(int arg)
	{
		int offset = 0x14F8 + 0x40 + 0x194;
		int* PaintKit = makeptr< int >(this, offset);

		*PaintKit = arg;
	}

	int      GetClip();
};

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};
struct cplane_t
{
	Vector  normal;
	float   dist;
	BYTE    type;
	BYTE    signbits;
	BYTE    pad[2];
};
struct csurface_t
{
	const char*             name;
	short                   surfaceProps;
	unsigned short  flags;
};


class CBaseTrace
{
public:
	Vector                  startpos;
	Vector                 endpos;
	cplane_t                plane;
	float                   fraction;
	int                             contents;
	unsigned short  dispFlags;
	bool                    allsolid;
	bool                    startsolid;
};



class CGameTrace : public CBaseTrace
{
public:


	float			fractionleftsolid;	// time we left a solid, only valid if we started in solid
	csurface_t		surface;			// surface hit (impact surface)

	int				hitgroup;			// 0 == generic, non-zero is specific body part

	short			physicsbone;		// physics bone hit by trace in studio
	unsigned short	worldSurfaceIndex;	// Index of the msurface2_t, if applicable

	CBaseEntity*  m_pEnt;
	int			hitbox;

	bool DidHitWorld() const
	{
		return m_pEnt == (CBaseEntity*)ALX.pEntList->GetClientEntity(0);
	}

	bool DidHitNonWorldEntity() const
	{
		return m_pEnt != (CBaseEntity*)ALX.pEntList->GetClientEntity(0);
	}

};




typedef CGameTrace trace_t;

struct Ray_t
{
	VectorAligned   m_Start;
	VectorAligned   m_Delta;
	VectorAligned   m_StartOffset;
	VectorAligned   m_Extents;

	const   matrix3x4* m_pWorldAxisTransform;

	bool    m_IsRay;
	bool    m_IsSwept;

	Ray_t() : m_pWorldAxisTransform(NULL) { }

	void Init(Vector& vecStart, Vector& vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;

		m_pWorldAxisTransform = NULL;

		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart;
	}
};
class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CBaseEntity *pEntity, int contentsMask) = 0;
	virtual TraceType_t    GetTraceType() const = 0;
};



class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};
class IEngineTrace
{
public:

	void TraceRay(const Ray_t &ray, unsigned int fMask, CTraceFilter *pTraceFilter, trace_t *pTrace)
	{
		typedef void(__thiscall* oTraceRay)(PVOID, const Ray_t&, unsigned int, CTraceFilter *, trace_t*);
		getvfunc<oTraceRay>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
};


#define XASSERT( x ) if( !x ) MessageBoxW( 0, L#x, 0, 0 );


/*extern ISteamClient*				g_pSteamClient;
extern ISteamFriends*				g_pSteamFriends;
extern ISteamUtils*					g_pSteamUtils;
extern ISteamUser*					g_pSteamUser;
extern ISteamUserStats*				g_pSteamStats;
extern ISteamMatchmaking*			g_pMatchMaking;
extern ISteamMatchmakingServers*	g_pMatchMakingSvr;
extern ISteamApps*					g_pSteamApps;*/


#define streql(x,y) strcmp( (x) , (y) ) == 0


#endif