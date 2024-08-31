class Entity;

struct PlayerInfo // oomg fucking sdk less
{

	// scoreboard information
	char			name[32];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[32 + 1];
	// friends identification number
	unsigned int	friendsID;
	// friends name
	char			friendsName[32];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
	// custom files CRC for this player
	unsigned long	customFiles[4];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
};

struct EntClass
{
	char pad[8];
	const char* name;
};

struct UserCmd
{
	int vmt;
	int index;
	int ticks;
	vec3 ang;
	vec3 move;
	int	buttons;
	char pad1[9];
	int seed;
	char pad2[4];
	bool predicted;
	char keyboard[284];
};

struct HitBBox
{
	int bone;
	int group;
	vec3 min;
	vec3 max;
	int unused[9];
};

struct HitboxSet
{
	char pad[8];
	int hitboxindex;
	inline HitBBox* GetHitbox(int index)
	{
		return (HitBBox*)((byte*)this + hitboxindex) + index;
	}
};
 
struct StudioHDR
{
	char pad1[176];
	int hitboxsetindex;
	inline HitBBox* GetHitbox(int index)
	{
		return ((HitboxSet*)((byte*)this + hitboxsetindex))->GetHitbox(index);
	}
	char pad2[24];
	int numtextures;
};


struct TraceResult
{
	char pad1[43];
	float fraction;
	char pad2[26];
	Entity* ent;
	int hitbox;
};

struct RayData
{
	vec3 base;
	int pad1;
	vec3 delta;
	int pad2;
	vec3 offset;
	int pad3;
	vec3 extents;
	int pad4;
	bool isray;
	bool hasdelta;
};

struct RenderInfo
{
	char pad[48];
	int index;
};