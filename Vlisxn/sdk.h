/*
	This is for other 'sdk' stuff
*/
#pragma once

class CBaseEntity;

#define IN_ATTACK		(1 << 0)
#define IN_ATTACK2		(1 << 11)
#define IN_JUMP			(1 << 1)
#define	FL_ONGROUND		(1<<0)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)

typedef float VMatrix[4][4];

struct WeaponInfo {
	float pen;
	int damage;
	float range;
	float rangeModifier;
	float ratio;
	float cycleTime;
	char pad[500];
};

class IMaterial {
public:
	inline void AddReference() {
		typedef void (__thiscall *OrigFn)( void * );
		getvFunc<OrigFn>(this, 12)( this );
	}
	inline void SetAlpha( float a ) {
		typedef void (__thiscall *OrigFn)( void *, float );
		getvFunc<OrigFn>(this, 27)( this, a );
	}
	inline void SetColor( float r, float g, float b ) {
		typedef void (__thiscall *OrigFn)( void *, float, float, float );
		getvFunc<OrigFn>(this, 28)( this, r, g, b );
	}
	inline void SetVarFlag( int flag, bool setting ) {
		typedef void (__thiscall *OrigFn)( void *, int, bool );
		getvFunc<OrigFn>(this, 29)( this, flag, setting );
	}
	inline bool IsErrorMaterial() {
		typedef bool(__thiscall *OrigFn)( void * );
		return getvFunc<OrigFn>(this, 42)( this );
	}
};

// structs
struct CUserCmd {
	char pad00[ 4 ];
	int command_number;
	int tick_count;
	Vector viewangles;   
	Vector aimdir;
	Vector move;       
	int buttons;
	char impulse;        
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
	char pad01[ 24 ];
};

struct player_info {
	char pad00[ 16 ];
	char name[ 32 ];
	int userID;
	char guid[ 33 ];
	unsigned int friendsID;
	char friendsName[ 32 ];
	bool fakeplayer;
	bool ishltv;
	unsigned int customFiles[ 4 ];
	unsigned char filesDownloaded;
	char pad01[ 256 ];
};

struct ConVar {
	char pad1[36];
	char* svalue;
	char pad2[4];
	float fvalue;
	int ivalue;
	char pad3[14];
	int callback;
};

struct CGlobalVarsBase {
	float realtime;
	int framecount;
	float absoluteframetime;
	float absoluteframestarttimestddev;
	float curtime;
	float frametime;
	int maxClients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
	int simTicksThisFrame;
	int network_protocol;
	char pad00[ 14 ];
};

struct Ray_t {
	void init( Vector s, Vector e ) {
		m_Start = s;
		m_Delta = e - s;
		m_IsRay = true;
		m_IsSwept = true;
	}

	Vector m_Start; // These are vector aligned ( 16b )
	char pad00[ 4 ];
	Vector m_Delta;
	char pad01[ 4 ];
	Vector m_StartOffset;
	char pad02[ 4 ];
	Vector m_Extents;
	char pad03[ 4 ];
	const matrix3x4_t *m_pWorldAxisTransform;
	bool m_IsRay;
	bool m_IsSwept;
	char pad04[ 4 ];
};

struct CTraceFilter {
	virtual bool ShouldHitEntity( CBaseEntity *ent, int ) {
		if( ent == pSkip )
			return false;

		if( ent == pSkip2 )
			return false;

		return true;
	}

	virtual int GetTraceType() {
		return 0;
	}

	char pad00[ 8 ];

	void *pSkip;
	void *pSkip2;
};

struct cplane_t {
	Vector normal;
	float dist;
	char type;
	char signbits;
	char pad[2];
};

struct CGameTrace {
	Vector startPos;
	Vector endPos;
	cplane_t plane;
	//char pad00[ 19 ]; // this was the cplane_t struct
	float fraction;
	int contents;
	char pad01[ 8 ]; // 16 ( - 4 )
	int hitgroup;
	short props;
	char pad02[ 8 ];
	CBaseEntity *m_pEnt;
	int hitbox;
};

struct surfacegameprops_t {
	float maxSpeedFactor;
	float jumpFactor;
	char pad00[ 4 ];
	float penMod;
	float damageMod;
	unsigned short mat;
	char pad01[ 3 ];
};

struct surfacedata_t {
	surfacegameprops_t game;
};

struct mstudiobbox_t {
	int bone;
	int group;
	Vector min;
	Vector max;
	int unused[ 9 ];
};

struct mstudiobone_t {
	char pad00[ 4 ];
	int parent;
	char pad01[ 152 ];
	int flags;
	char pad02[ 52 ]; 
};

struct mstudiohitboxset_t {
	char pad[ 8 ];
	int hitboxindex;
	inline mstudiobbox_t* GetHitbox(int index) { return (mstudiobbox_t*)((BYTE *)this + hitboxindex) + index; }
};

/*
	struct studiohdr_t {
	char pad00[ 104 ];
	Vector min;
	Vector max;
	char pad01[ 28 ];
	int numbones;
	int boneindex;
	inline mstudiobone_t *getBone( int i ) { return (mstudiobone_t *)(((BYTE *)this) + boneindex) + i; }
	char pad02[ 12 ];
	int hitboxsetindex;
	inline mstudiobbox_t* GetHitbox(int index) { return ((mstudiohitboxset_t*)((BYTE *)this + hitboxsetindex))->GetHitbox(index); }
};
*/

struct studiohdr_t {
	char pad00[ 156 ];
	int numbones;
	int boneindex;
	inline mstudiobone_t *getBone( int i ) { return (mstudiobone_t *)(((BYTE *)this) + boneindex) + i; }
	char pad01[ 12 ];
	int hitboxsetindex;
	inline mstudiobbox_t* GetHitbox(int index) { return ((mstudiohitboxset_t*)((BYTE *)this + hitboxsetindex))->GetHitbox(index); }
};

struct CViewSetup {
	char pad00[ 176 ];	// 176b
	float fov;			// 180b
	char pad01[ 16 ];	// 196b
	Vector angles;		// 208b
};

enum moveTypes {
	MOVETYPE_NONE		= 0,			// never moves
	MOVETYPE_ISOMETRIC,					// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,						// Player only - moving on the ground
	MOVETYPE_STEP,						// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,						// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,				// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,					// uses VPHYSICS for simulation
	MOVETYPE_PUSH,						// no clip to world, push and crush
	MOVETYPE_NOCLIP,					// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,					// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,					// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,					// Allows the entity to describe its own physics
	MOVETYPE_LAST = MOVETYPE_CUSTOM,	// should always be defined as the last item in the list
	MOVETYPE_MAX_BITS	= 4
};

enum matFlags {
	MATERIAL_VAR_DEBUG						= 1,
	MATERIAL_VAR_NO_DEBUG_OVERRIDE			= 2,
	MATERIAL_VAR_NO_DRAW					= 4,
	MATERIAL_VAR_USE_IN_FILLRATE_MODE		= 8,
	MATERIAL_VAR_VERTEXCOLOR				= 16,
	MATERIAL_VAR_VERTEXALPHA				= 32,
	MATERIAL_VAR_SELFILLUM					= 64,
	MATERIAL_VAR_ADDITIVE					= 128,
	MATERIAL_VAR_ALPHATEST					= 256,
//	MATERIAL_VAR_UNUSED						= 512,
	MATERIAL_VAR_ZNEARER					= 1024,
	MATERIAL_VAR_MODEL						= 2048,
	MATERIAL_VAR_FLAT						= 4096,
	MATERIAL_VAR_NOCULL						= 8192,
	MATERIAL_VAR_NOFOG						= 16384,
	MATERIAL_VAR_IGNOREZ					= 32768,
	MATERIAL_VAR_DECAL						= 65536,
	MATERIAL_VAR_ENVMAPSPHERE				= 131072, // OBSOLETE
//	MATERIAL_VAR_UNUSED						= 262144,
	MATERIAL_VAR_ENVMAPCAMERASPACE			= 524288, // OBSOLETE
	MATERIAL_VAR_BASEALPHAENVMAPMASK		= 1048576,
	MATERIAL_VAR_TRANSLUCENT				= 2097152,
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK	= 4194304,
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING	= 8388608, // OBSOLETE
	MATERIAL_VAR_OPAQUETEXTURE				= 16777216,
	MATERIAL_VAR_ENVMAPMODE					= 33554432, // OBSOLETE
	MATERIAL_VAR_SUPPRESS_DECALS			= 67108864,
	MATERIAL_VAR_HALFLAMBERT				= 134217728,
	MATERIAL_VAR_WIREFRAME					= 268435456,
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE		= 536870912,
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY	= 1073741824,
	//MATERIAL_VAR_VERTEXFOG					= -2147483648,
};

enum weapons {
	weapon_none,
	weapon_deagle,
	weapon_elite,
	weapon_fiveseven,
	weapon_glock,
	weapon_ak47 = 7,
	weapon_aug,
	weapon_awp,
	weapon_famas,
	weapon_g3sg1,
	weapon_galilar = 13,
	weapon_m249,
	weapon_m4a4 = 16,
	weapon_mac10,
	weapon_p90 = 19,
	weapon_ump45 = 24,
	weapon_xm1014,
	weapon_bizon,
	weapon_mag7,
	weapon_negev,
	weapon_sawedoff,
	weapon_tec9,
	weapon_taser,
	weapon_p2000,
	weapon_mp7,
	weapon_mp9,
	weapon_nova,
	weapon_p250,
	weapon_scar20 = 38,
	weapon_sg553,
	weapon_ssg08,
	weapon_knife_ct = 42,
	weapon_flashbang,
	weapon_hegrenade,
	weapon_smokegrenade,
	weapon_molotov,
	weapon_decoy,
	weapon_incgrenade,
	weapon_c4,
	weapon_knife_t = 59,
	weapon_m4a1s = 60,
	weapon_usp = 61,
	weapon_cz75 = 63,
	weapon_bayonet = 500,
	weapon_flip = 505,
	weapon_gut,
	weapon_karambit,
	weapon_m9bayonet,
	weapon_huntsman,
	weapon_falchion = 512,
	weapon_butterfly = 515
};