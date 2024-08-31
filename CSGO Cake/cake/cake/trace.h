struct cplane_t
{
	vector	normal;
	float	dist;
	byte	type;			// for fast side tests
	byte	signbits;		// signx + (signy<<1) + (signz<<1)
	byte	pad[2];

#ifdef VECTOR_NO_SLOW_OPERATIONS
	cplane_t() {}

private:
	// No copy constructors allowed if we're in optimal mode
	cplane_t(const cplane_t& vOther);
#endif
};

class CBaseTrace
{
public:

	// Displacement flags tests.

public:

	// these members are aligned!!
	vectoraligned			startpos;				// start position
	vectoraligned			endpos;					// final position
	cplane_t		plane;					// surface normal at impact

	float			fraction;				// time completed, 1.0 = didn't hit anything

	int				contents;				// contents on other side of surface hit
	unsigned short	dispFlags;				// displacement flags for marking surfaces with data

	bool			allsolid;				// if true, plane is not valid
	bool			startsolid;				// if true, the initial point was in a solid area

	CBaseTrace() {}

};

struct csurface_t
{
	const char	*name;
	short		surfaceProps;
	unsigned short	flags;		// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};


class CGameTrace : public CBaseTrace
{
public:

	// Returns true if hEnt points at the world entity.
	// If this returns true, then you can't use GetHitBoxIndex().
	bool DidHitWorld() const;

	// Returns true if we hit something and it wasn't the world.
	bool DidHitNonWorldEntity() const;

	// Gets the entity's network index if the trace has hit an entity.
	// If not, returns -1.
	int GetEntityIndex() const;

	// Returns true if there was any kind of impact at all
	bool DidHit() const;
	bool IsVisible() const;
	// The engine doesn't know what a CBaseEntity is, so it has a backdoor to 
	// let it get at the edict.
#if defined( ENGINE_DLL )
	void SetEdict(edict_t *pEdict);
	edict_t* GetEdict() const;
#endif	

public:

	float			fractionleftsolid;	// time we left a solid, only valid if we started in solid
	csurface_t		surface;			// surface hit (impact surface)
	int				hitgroup;			// 0 == generic, non-zero is specific body part
	short			physicsbone;		// physics bone hit by trace in studio
	unsigned short	worldSurfaceIndex;	// Index of the msurface2_t, if applicable
#if defined( CLIENT_DLL )
	C_BaseEntity *m_pEnt;
#else
	icliententity *m_pEnt;
#endif
	// NOTE: this member is overloaded.
	// If hEnt points at the world entity, then this is the static prop index.
	// Otherwise, this is the hitbox index.
	int			hitbox;					// box hit by trace in studio

	CGameTrace() {}

	//private:
	// No copy constructors allowed
	CGameTrace(const CGameTrace& other) :
		fractionleftsolid(other.fractionleftsolid),
		surface(other.surface),
		hitgroup(other.hitgroup),
		physicsbone(other.physicsbone),
		worldSurfaceIndex(other.worldSurfaceIndex),
		m_pEnt(other.m_pEnt),
		hitbox(other.hitbox)
	{
		startpos = other.startpos;
		endpos = other.endpos;
		plane = other.plane;
		fraction = other.fraction;
		contents = other.contents;
		dispFlags = other.dispFlags;
		allsolid = other.allsolid;
		startsolid = other.startsolid;
	}

	CGameTrace& CGameTrace::operator=(const CGameTrace& other)
	{
		startpos = other.startpos;
		endpos = other.endpos;
		plane = other.plane;
		fraction = other.fraction;
		contents = other.contents;
		dispFlags = other.dispFlags;
		allsolid = other.allsolid;
		startsolid = other.startsolid;
		fractionleftsolid = other.fractionleftsolid;
		surface = other.surface;
		hitgroup = other.hitgroup;
		physicsbone = other.physicsbone;
		worldSurfaceIndex = other.worldSurfaceIndex;
		m_pEnt = other.m_pEnt;
		hitbox = other.hitbox;
		return *this;
	}
};

typedef CGameTrace trace_t;

struct Ray_t
{
	vectoraligned  m_Start;	// starting point, centered within the extents
	vectoraligned  m_Delta;	// direction + length of the ray
	vectoraligned  m_StartOffset;	// Add this to m_Start to get the actual ray start
	vectoraligned  m_Extents;	// Describes an axis aligned box extruded along a ray
	//const matrix3x4_t *m_pWorldAxisTransform;
	bool	m_IsRay;	// are the extents zero?
	bool	m_IsSwept;	// is delta != 0?

	//Ray_t() : m_pWorldAxisTransform(NULL)	{}

	void Init(vector start, vector end)
	{
		m_Delta = (end - start);

		m_IsSwept = (m_Delta.length_sqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;
		//m_pWorldAxisTransform = NULL;
		m_IsRay = true;

		// Offset m_Start to be in the center of the box...
		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;
		m_Start = start;
	}
private:
};