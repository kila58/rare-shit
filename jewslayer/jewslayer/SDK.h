#ifndef __SDK_H__
#define __SDK_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "checksum_crc.h"
#include "const.h"
#include "NetVars.h"
#include "Vector.h"
#include "Offsets.h"

namespace ValveSDK
{
	class model_t;
	struct mstudiobbox_t;
	struct mstudiohitboxset_t;
	struct mstudiobone_t;
	struct studiohdr_t;
	struct DrawModelState_t;
	struct ModelRenderInfo_t;
	struct surfacephysicsparams_t;
	struct surfaceaudioparams_t;
	struct surfacesoundnames_t;
	struct surfacegameprops_t;
	struct surfacedata_t;
	class CEntityList;
	class CGlobalVarsBase;
	class IGameMovement;
	class CGlowObjectManager;
	class CHLClient;
	class CUserCmd;
	class CInput;
	class IMoveHelper;
	class IPrediction;
	class IDebugOverlay;
	class IEngineClient;
	class IEngineTrace;
	struct FireBulletData;
	class IGameEvent;
	class IGameEventListner2;
	class IGameEventManager2;
	class KeyValues;
	class IMaterial;
	class IModelInfo;
	class IModelRender;
	class IRenderView;
	class IPanel;
	class ISurface;
	class CRenderSurface;
	class IMultiplayerPhysics;
	class IBreakableWithPropData;
	class IPhysicsSurfaceProps;
	class IMaterialSystem;
	class CHudTexture;
	class CWeaponData;
	class CBaseCombatWeapon;
	class CBaseEntity;
	class PlayerData;
	class CTools;
}

extern ValveSDK::CEntityList* g_pEntityList;
extern ValveSDK::CGlobalVarsBase* g_pGlobalVarsBase;
extern ValveSDK::IGameMovement* g_pGameMovement;
extern ValveSDK::CGlowObjectManager* g_pGlowObjectManager;
extern ValveSDK::CHLClient* g_pClient;
extern ValveSDK::CInput* g_pInput;
extern ValveSDK::IMoveHelper* g_pMoveHelper;
extern ValveSDK::IPrediction* g_pPrediction;
extern ValveSDK::IDebugOverlay* g_pDebugOverlay;
extern ValveSDK::IEngineClient* g_pEngine;
extern ValveSDK::IEngineTrace* g_pEngineTrace;
extern ValveSDK::IGameEventManager2* g_pGameEventManager;
extern ValveSDK::IModelInfo* g_pModelInfo;
extern ValveSDK::IModelRender* g_pModelRender;
extern ValveSDK::IRenderView* g_pRenderView;
extern ValveSDK::IMaterialSystem* g_pMaterialSystem;
extern ValveSDK::IPhysicsSurfaceProps* g_pPhysSurface;
extern ValveSDK::IPanel* g_pPanel;
extern ValveSDK::ISurface* g_pSurface;
extern ValveSDK::CRenderSurface* g_pRenderSurface;
extern ValveSDK::CTools* g_pTools;

namespace ValveSDK
{
	struct mstudiobbox_t
	{
		int				bone;				// 0x0
		int				group;				// 0x4
		Vector	bbmin;				// 0x8
		Vector	bbmax;				// 0x14
		int				szhitboxnameindex;	// 0x18
		PAD( 0x8 );							// 0x1C	
		char* GetHitboxName( void )
		{
			if( szhitboxnameindex == 0 )
				return "";

			return ( ( char* )this ) + szhitboxnameindex;
		} // 0x28 
		PAD( 0x18 );

	};
	struct mstudiohitboxset_t
	{
		int						sznameindex;
		inline char* const		GetName( void ) const { return ( ( char* )this ) + sznameindex; }
		int						numhitboxes;
		int						hitboxindex;
		inline mstudiobbox_t*	pHitbox( int i ) const { return ( mstudiobbox_t* )( ( ( BYTE* )this ) + hitboxindex ) + i; };
	};
	struct mstudiobone_t
	{
		int					sznameindex;
		inline char * const GetName( void ) const { return ( ( char * )this ) + sznameindex; }
		int		 			parent;
		int					bonecontroller[ 6 ];

		Vector				pos;
		float				quat[ 4 ];
		Vector				rot;
		Vector				posscale;
		Vector				rotscale;

		matrix3x4			poseToBone;
		float				qAlignment[ 4 ];
		int					flags;
		int					proctype;
		int					procindex;		// procedural rule
		mutable int			physicsbone;	// index into physically simulated bone
		inline void *		GetProcedure( ) const { if( procindex == 0 ) return NULL; else return  ( void * )( ( ( BYTE * )this ) + procindex ); };
		int					surfacepropidx;	// index into string tablefor property name
		inline char * const GetSurfaceProps( void ) const { return ( ( char * )this ) + surfacepropidx; }
		int					contents;		// See BSPFlags.h for the contents flags

		int					unused[ 8 ];		// remove as appropriate
	};
	struct studiohdr_t
	{
		int					id;
		int					version;
		int					checksum;
		char				name[ 64 ];
		int					length;
		Vector				eyeposition;
		Vector				illumposition;
		Vector				hull_min;
		Vector				hull_max;
		Vector				view_bbmin;
		Vector				view_bbmax;
		int					flags;
		int					numbones;
		int					boneindex;

		inline mstudiobone_t *pBone( int i ) const { return ( mstudiobone_t * )( ( ( BYTE * )this ) + boneindex ) + i; };

		int					numbonecontrollers;
		int					bonecontrollerindex;
		int					numhitboxsets;
		int					hitboxsetindex;

		mstudiohitboxset_t* pHitboxSet( int i ) const
		{
			return ( mstudiohitboxset_t* )( ( ( BYTE* )this ) + hitboxsetindex ) + i;
		}

		inline mstudiobbox_t* pHitbox( int i, int set ) const
		{
			mstudiohitboxset_t const* s = pHitboxSet( set );

			if( !s )
				return NULL;

			return s->pHitbox( i );
		}

		inline int GetHitboxCount( int set ) const
		{
			mstudiohitboxset_t const* s = pHitboxSet( set );

			if( !s )
				return 0;

			return s->numhitboxes;
		}

		int					numlocalanim;
		int					localanimindex;
		int					numlocalseq;
		int					localseqindex;
		mutable int			activitylistversion;
		mutable int			eventsindexed;
		int					numtextures;
		int					textureindex;
		int					numcdtextures;
		int					cdtextureindex;
		int					numskinref;
		int					numskinfamilies;
		int					skinindex;
		int					numbodyparts;
		int					bodypartindex;
		int					numlocalattachments;
		int					localattachmentindex;
		int					numlocalnodes;
		int					localnodeindex;
		int					localnodenameindex;
		int					numflexdesc;
		int					flexdescindex;
		int					numflexcontrollers;
		int					flexcontrollerindex;
		int					numflexrules;
		int					flexruleindex;
		int					numikchains;
		int					ikchainindex;
		int					nummouths;
		int					mouthindex;
		int					numlocalposeparameters;
		int					localposeparamindex;
		int					surfacepropindex;
		int					keyvalueindex;
		int					keyvaluesize;
		int					numlocalikautoplaylocks;
		int					localikautoplaylockindex;
		float				mass;
		int					contents;
		int					numincludemodels;
		int					includemodelindex;
		mutable void		*virtualModel;
		int					szanimblocknameindex;
		int					numanimblocks;
		int					animblockindex;
		mutable void		*animblockModel;
		int					bonetablebynameindex;
		void				*pVertexBase;
		void				*pIndexBase;
		BYTE				constdirectionallightdot;
		BYTE				rootLOD;
		BYTE				numAllowedRootLODs;
		PAD( 0x5 );
		int					numflexcontrollerui;
		int					flexcontrolleruiindex;
		float				flVertAnimFixedPointScale;
		PAD( 0x4 );
		int					studiohdr2index;
		PAD( 0x4 );
	};
	struct DrawModelState_t
	{
		studiohdr_t*		m_pStudioHdr;
		unsigned long		m_pStudioHWData;
		CBaseEntity*		m_pRenderable;
		const matrix3x4*	m_pModelToWorld;
		unsigned long		m_decals;
		int					m_drawFlags;
		int					m_lod;
	};
	struct ModelRenderInfo_t
	{
		Vector				origin;
		QAngle				angles;
		CBaseEntity*		pRenderable;
		const model_t*		pModel;
		const matrix3x4*	pModelToWorld;
		const matrix3x4*	pLightingOffset;
		const Vector*		pLightingOrigin;
		int					flags;
		int					entity_index;
		int					skin;
		int					body;
		int					hitboxset;
		unsigned short		instance;
		ModelRenderInfo_t( void )
		{
			pModelToWorld = NULL;
			pLightingOffset = NULL;
			pLightingOrigin = NULL;
		}
	};
	struct surfacephysicsparams_t
	{
		float   friction;
		float   elasticity; // collision elasticity - used to compute coefficient of restitution
		float   density;        // physical density (in kg / m^3)
		float   thickness;      // material thickness if not solid (sheet materials) in inches
		float   dampening;
	};
	struct surfaceaudioparams_t
	{
		float   reflectivity;                   // like elasticity, but how much sound should be reflected by this surface
		float   hardnessFactor;                 // like elasticity, but only affects impact sound choices
		float   roughnessFactor;                // like friction, but only affects scrape sound choices
		float   roughThreshold;                 // surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
		float   hardThreshold;                  // surface hardness > this causes "hard" impacts, < this causes "soft" impacts
		float   hardVelocityThreshold;  // collision velocity > this causes "hard" impacts, < this causes "soft" impacts       
	};
	struct surfacesoundnames_t
	{
		unsigned short  stepleft;
		unsigned short  stepright;
		unsigned short  impactSoft;
		unsigned short  impactHard;
		unsigned short  scrapeSmooth;
		unsigned short  scrapeRough;
		unsigned short  bulletImpact;
		unsigned short  rolling;
		unsigned short  breakSound;
		unsigned short  strainSound;
	};
	struct surfacegameprops_t
	{
	public:
		float   maxSpeedFactor;
		float   jumpFactor; 
		PAD( 0x4 );
		float   flPenetrationModifier;
		float   flDamageModifier;
		unsigned short  material;
		PAD( 0x3 );

	};
	struct surfacedata_t
	{
		surfacephysicsparams_t	physics;
		surfaceaudioparams_t	audio;
		surfacesoundnames_t		sounds;
		surfacegameprops_t		game;
	};
	class CEntityList
	{
	public:
		CBaseEntity* GetBaseEntity( int iIndex )
		{
			VirtualFn( CBaseEntity* )( PVOID, int );
			return CallVirtual< OriginalFn >( this, 3 )( this, iIndex );
		}
		CBaseEntity* GetBaseEntityFromHandle( EHANDLE hEntity )
		{
			VirtualFn( CBaseEntity* )( PVOID, EHANDLE );
			return CallVirtual< OriginalFn >( this, 4 )( this, hEntity );
		}
		int GetHighestEntityIndex( void )
		{
			VirtualFn( int )( PVOID );
			return CallVirtual< OriginalFn >( this, 6 )( this );
		}
	};
	class CGlobalVarsBase
	{
	public:
		float	realtime;
		int		framecount;
		float	absoluteframetime;
		float	unknown;
		float	curtime;
		float	frametime;
		int		maxclients;
		int		tickcount;
		float	interval_per_tick;
		float	interpolation_amount;
	};
	class IGameMovement
	{
	public:
		void ProcessMovement( CBaseEntity* pBaseEntity, PVOID pMoveData )
		{
			VirtualFn( void )( PVOID, CBaseEntity*, PVOID );
			CallVirtual< OriginalFn >( this, 1 )( this, pBaseEntity, pMoveData );
		}
	};
	class CGlowObjectManager
	{
	public:
		struct GlowObjectDefinition_t
		{
			CBaseEntity*	m_pEntity;
			Vector			m_vecGlowColor;
			float			m_flGlowAlpha;
			PAD( 0x10 );
			bool			m_bShouldGlow;
			bool			m_bUnknown;
			bool			m_bFullBloomRender;
			PAD( 0xD );
		};

	public:
		std::vector< GlowObjectDefinition_t >	m_vGlowObjectDefinitions;
		int										m_iFirstFreeSlot;
	};
	class CHLClient
	{
	public:
		ClientClass* GetAllClasses(VOID)
		{
			typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
			return CallVirtual<OriginalFn>(this, 8)(this);
			//don't forget the return here for all type except void!
			// oki <3
		}
		ClientClass* GetFirstClass( void )
		{
			VirtualFn( ClientClass* )( PVOID );
			return CallVirtual< OriginalFn >( this, 8 )( this );
		}
	};
	class CUserCmd
	{
	public:
		PAD( 0x4 );
		int				command_number;
		int				tick_count;
		QAngle			viewangles;
		Vector			aimdirection;
		float			forwardmove;
		float			sidemove;
		float			upmove;
		int				buttons;
		BYTE			impulse;
		int				weaponselect;
		int				weaponsubtype;
		int				random_seed;
		short			mousedx;
		short			mousedy;
		bool			hasbeenpredicted;
		QAngle			headangles;
		Vector			headoffset;

	public:
		CRC32_t GetChecksum( void ) const
		{
			CRC32_t crc;
			CRC32_Init( &crc );
			CRC32_ProcessBuffer( &crc, &command_number, sizeof( command_number ) );
			CRC32_ProcessBuffer( &crc, &tick_count, sizeof( tick_count ) );
			CRC32_ProcessBuffer( &crc, &viewangles, sizeof( viewangles ) );
			CRC32_ProcessBuffer( &crc, &aimdirection, sizeof( aimdirection ) ); //new
			CRC32_ProcessBuffer( &crc, &forwardmove, sizeof( forwardmove ) );
			CRC32_ProcessBuffer( &crc, &sidemove, sizeof( sidemove ) );
			CRC32_ProcessBuffer( &crc, &upmove, sizeof( upmove ) );
			CRC32_ProcessBuffer( &crc, &buttons, sizeof( buttons ) );
			CRC32_ProcessBuffer( &crc, &impulse, sizeof( impulse ) );
			CRC32_ProcessBuffer( &crc, &weaponselect, sizeof( weaponselect ) );
			CRC32_ProcessBuffer( &crc, &weaponsubtype, sizeof( weaponsubtype ) );
			CRC32_ProcessBuffer( &crc, &random_seed, sizeof( random_seed ) );
			CRC32_ProcessBuffer( &crc, &mousedx, sizeof( mousedx ) );
			CRC32_ProcessBuffer( &crc, &mousedy, sizeof( mousedy ) );
			CRC32_Final( &crc );
			return crc;
		}
	};
	class CInput
	{
	public:
		class CVerifiedUserCmd
		{
		public:
			CUserCmd	m_cmd;
			CRC32_t		m_crc;
		};

	public:
		CUserCmd* GetUserCmd( int slot, int sequence_number )
		{
			VirtualFn( CUserCmd* )( PVOID, int, int );
			return CallVirtual< OriginalFn >( this, 8 )( this, slot, sequence_number );
		}
	};
	class IMoveHelper
	{
	public:
		void SetHost( CBaseEntity* pBaseEntity )
		{
			VirtualFn( void )( PVOID, CBaseEntity* );
			CallVirtual< OriginalFn >( this, 1 )( this, pBaseEntity );
		}
	};
	class IPrediction
	{
	public:
		bool InPrediction( void )
		{
			VirtualFn( bool )( PVOID );
			return CallVirtual< OriginalFn >( this, 14 )( this );
		}
		void RunCommand( CBaseEntity* pBaseEntity, CUserCmd* pCmd, PVOID pMoveHelper )
		{
			VirtualFn( void )( PVOID, CBaseEntity*, CUserCmd*, PVOID );
			CallVirtual< OriginalFn >( this, 19 )( this, pBaseEntity, pCmd, pMoveHelper );
		}
		void SetupMove( CBaseEntity* pBaseEntity, CUserCmd* pCmd, PVOID pEmpty, PVOID pMoveData )
		{
			VirtualFn( void )( PVOID, CBaseEntity*, CUserCmd*, PVOID, PVOID );
			CallVirtual< OriginalFn >( this, 20 )( this, pBaseEntity, pCmd, pEmpty, pMoveData );
		}
		void FinishMove( CBaseEntity* pBaseEntity, CUserCmd* pCmd, PVOID pMoveData )
		{
			VirtualFn( void )( PVOID, CBaseEntity*, CUserCmd*, PVOID );
			CallVirtual< OriginalFn >( this, 21 )( this, pBaseEntity, pCmd, pMoveData );
		}
	};
	class IDebugOverlay
	{
	public:
		int ScreenPoint( const Vector& vecOrigin, Vector& vecScreen )
		{
			VirtualFn( int )( PVOID, const Vector&, Vector& );
			return CallVirtual< OriginalFn >( this, 13 )( this, vecOrigin, vecScreen );
		}
	};
	class IEngineClient
	{
	public:
		class player_info_t
		{
		public:
			PAD( 0x8 );
			unsigned long long      xuid;
			char                    name[ 128 ];
			int                     userID;
			char                    guid[ 32 + 1 ];
			unsigned int            friendsID;
			char                    friendsName[ 128 ];
			bool                    fakeplayer;
			bool                    ishltv;
			unsigned long           customFiles[ 4 ];
			unsigned char           filesDownloaded;
		};
	public:
		void GetScreenSize( int& iWidth, int& iHeight )
		{
			VirtualFn( void )( PVOID, int&, int& );
			CallVirtual< OriginalFn >( this, 5 )( this, iWidth, iHeight );
		}
		void GetScreenSize( int* piScreenSize )
		{
			GetScreenSize( piScreenSize[ 0 ], piScreenSize[ 1 ] );
		}
		void ClientCmd( const char* pszCmd, ... )
		{
			VirtualFn( void )( PVOID, const char* );
			CallVirtual< OriginalFn >( this, 7 )( this, pszCmd );
		}
		bool GetPlayerInfo( int iIndex, player_info_t* pInfo )
		{
			VirtualFn( bool )( PVOID, int, player_info_t* );
			return CallVirtual< OriginalFn >( this, 8 )( this, iIndex, pInfo );
		}
		int GetPlayerForUserID( int iUserId )
		{
			VirtualFn( int )( PVOID, int );
			return CallVirtual< OriginalFn >( this, 9 )( this, iUserId );
		}
		int GetLocalPlayer( void )
		{
			VirtualFn( int )( PVOID );
			return CallVirtual< OriginalFn >( this, 12 )( this );
		}
		float GetLastTimeStamp( void )
		{
			VirtualFn( float )( PVOID );
			return CallVirtual< OriginalFn >( this, 14 )( this );
		}
		void GetViewAngles( QAngle& qViewAngles )
		{
			VirtualFn( void )( PVOID, QAngle& );
			CallVirtual< OriginalFn >( this, 18 )( this, qViewAngles );
		}
		void SetViewAngles( QAngle& qViewAngles )
		{
			VirtualFn( void )( PVOID, QAngle& );
			CallVirtual< OriginalFn >( this, 19 )( this, qViewAngles );
		}
		int GetMaxClients( void )
		{
			VirtualFn( int )( PVOID );
			return CallVirtual< OriginalFn >( this, 20 )( this );
		}
		bool IsIngame( void )
		{
			VirtualFn( bool )( PVOID );
			return CallVirtual< OriginalFn >( this, 26 )( this );
		}
		bool IsConnected( void )
		{
			VirtualFn( bool )( PVOID );
			return CallVirtual< OriginalFn >( this, 27 )( this );
		}
		std::string GetGameDirectory( void )
		{
			VirtualFn( const char* )( PVOID );
			return std::string( CallVirtual< OriginalFn >( this, 36 )( this ) );
		}
		void ExecuteClientCmd( const char* pszCmd )
		{
			VirtualFn( void )( PVOID, const char* );
			CallVirtual< OriginalFn >( this, 108 )( this, pszCmd );
		}
	};
	class IEngineTrace
	{
	public:
		struct cplane_t
		{
			Vector normal;
			float dist;
			BYTE type;
			BYTE signBits;
			BYTE pad[ 2 ];
		};
		struct csurface_t
		{
			const char*		name;
			short			surfaceProps;
			unsigned short	flags;
		};
		struct Ray_t
		{
			VectorAligned  m_Start;	// starting point, centered within the extents
			VectorAligned  m_Delta;	// direction + length of the ray
			VectorAligned  m_StartOffset;	// Add this to m_Start to get the actual ray start
			VectorAligned  m_Extents;	// Describes an axis aligned box extruded along a ray
			const matrix3x4 *m_pWorldAxisTransform;
			bool	m_IsRay;	// are the extents zero?
			bool	m_IsSwept;	// is delta != 0?

			Ray_t( ) : m_pWorldAxisTransform( NULL )	{}

			void Init( Vector const& start, Vector const& end )
			{
				Assert( &end );
				VectorSubtract( end, start, m_Delta );

				m_IsSwept = ( m_Delta.LengthSqr( ) != 0 );

				VectorClear( m_Extents );
				m_pWorldAxisTransform = NULL;
				m_IsRay = true;

				// Offset m_Start to be in the center of the box...
				VectorClear( m_StartOffset );
				VectorCopy( start, m_Start );
			}

			void Init( Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs )
			{
				Assert( &end );
				VectorSubtract( end, start, m_Delta );

				m_pWorldAxisTransform = NULL;
				m_IsSwept = ( m_Delta.LengthSqr( ) != 0 );

				VectorSubtract( maxs, mins, m_Extents );
				m_Extents *= 0.5f;
				m_IsRay = ( m_Extents.LengthSqr( ) < 1e-6 );

				// Offset m_Start to be in the center of the box...
				VectorAdd( mins, maxs, m_StartOffset );
				m_StartOffset *= 0.5f;
				VectorAdd( start, m_StartOffset, m_Start );
				m_StartOffset *= -1.0f;
			}

			// compute inverse delta
			Vector InvDelta( ) const
			{
				Vector vecInvDelta;
				for( int iAxis = 0; iAxis < 3; ++iAxis )
				{
					if( m_Delta[ iAxis ] != 0.0f )
					{
						vecInvDelta[ iAxis ] = 1.0f / m_Delta[ iAxis ];
					}
					else
					{
						vecInvDelta[ iAxis ] = FLT_MAX;
					}
				}
				return vecInvDelta;
			}

		private:
		};
		struct trace_t
		{
			Vector	start;
			Vector	endpos;
			cplane_t	plane;
			float		fraction;
			int			contents;
			WORD		dispFlags;
			bool		allSolid;
			bool		startSolid;
			float		fractionLeftSolid;
			csurface_t	surface;
			int			hitgroup;
			short		physicsBone;
			WORD		m_nWorldSurfaceIndex;
			CBaseEntity* m_pEnt;
			int			hitbox;
		};
		class ITraceFilter
		{
		public:
			virtual bool ShouldHitEntity( PVOID pEntity, int contentsMask ) = 0;
			virtual TraceType_t	GetTraceType( ) const = 0;
		};
		class CTraceFilter : public ITraceFilter
		{
		public:
			CTraceFilter( PVOID pEntToSkip = NULL )
			{
				pSkip = pEntToSkip;
			}
			bool ShouldHitEntity( PVOID pEntityHandle, int contentsMask )
			{
				return !( pEntityHandle == pSkip );
			}
			virtual TraceType_t GetTraceType( ) const
			{
				return TRACE_EVERYTHING;
			}
			void* pSkip;
		};

	public:
		int GetPointContents( const Vector& vecAbsPosition, UINT nMask, CBaseEntity** ppEntity = NULL )
		{
			VirtualFn( int )( PVOID, const Vector&, UINT, CBaseEntity** );
			return CallVirtual< OriginalFn >( this, 0 )( this, vecAbsPosition, nMask, ppEntity );
		}
		void TraceRay( const Ray_t& ray, unsigned int nMask, ITraceFilter* pTraceFilter, trace_t* pTrace )
		{
			VirtualFn( void )( PVOID, const Ray_t&, unsigned int, ITraceFilter*, trace_t* );
			CallVirtual< OriginalFn >( this, 5 )( this, ray, nMask, pTraceFilter, pTrace );
		}
		void ClipRayToEntity( const Ray_t& ray, unsigned int nMask, CBaseEntity* pEntity, trace_t* pTrace )
		{
			VirtualFn( void )( PVOID, const Ray_t&, unsigned int, CBaseEntity*, trace_t* );
			CallVirtual< OriginalFn >( this, 3 )( this, ray, nMask, pEntity, pTrace );
		}

	};
	struct FireBulletData
	{
		FireBulletData( const Vector &eye_pos )	: src( eye_pos )
		{
		}

		Vector						src;
		IEngineTrace::trace_t       enter_trace;
		Vector						direction;
		IEngineTrace::CTraceFilter  filter;
		float						trace_length;
		float						trace_length_remaining;
		float						current_damage;
		int							penetrate_count;
	};
	class IGameEvent
	{
	public:
		std::string GetName( void )
		{
			VirtualFn( const char* )( PVOID );
			return std::string( CallVirtual< OriginalFn >( this, 1 )( this ) );
		}
		bool GetBool( std::string strKeyName, bool bDefaultValue = false )
		{
			VirtualFn( bool )( PVOID, const char*, bool );
			const char* c = strKeyName.c_str( );
			return CallVirtual< OriginalFn >( this, 5 )( this, c, bDefaultValue );
		}
		int GetInt( std::string strKeyName, int iDefaultValue = 0 )
		{
			VirtualFn( int )( PVOID, const char*, int );
			const char* c = strKeyName.c_str( );
			return CallVirtual< OriginalFn >( this, 6 )( this, c, iDefaultValue );
		}
		std::string GetString( std::string strKeyName, int iDefaultValue = 0 )
		{
			VirtualFn( const char* )( PVOID, const char*, int );
			const char* c = strKeyName.c_str( );
			return std::string( CallVirtual< OriginalFn >( this, 9 )( this, c, iDefaultValue ) );
		}
	};
	class IGameEventListener2
	{
	public:
		virtual ~IGameEventListener2( void ){}
		virtual void FireGameEvent( IGameEvent* pGameEvent ) = 0;
		virtual int GetEventDebugID( void )
		{
			return m_nDebugId;
		}

	public:
		int	m_nDebugId;
	};
	class IGameEventManager2
	{
	public:
		bool AddListener( IGameEventListener2* pListener, std::string strName, bool bServerSide )
		{
			VirtualFn( bool )( PVOID, IGameEventListener2*, const char*, bool );
			const char* c = strName.c_str( );
			return CallVirtual< OriginalFn >( this, 3 )( this, pListener, c, bServerSide );
		}
		bool FireEventClientSide( IGameEvent* pGameEvent )
		{
			VirtualFn( bool )( PVOID, IGameEvent* );
			return CallVirtual< OriginalFn >( this, 8 )( this, pGameEvent );
		}
	};
	class IMaterial
	{
	public:
		std::string GetName( void )
		{
			VirtualFn( const char* )( PVOID );
			return std::string( CallVirtual< OriginalFn >( this, 0 )( this ) );
		}
		std::string GetTextureGroupName( void )
		{
			VirtualFn( const char* )( PVOID );
			return std::string( CallVirtual< OriginalFn >( this, 1 )( this ) );
		}
		void IncrementReferenceCount( void )
		{
			VirtualFn( void )( PVOID );
			CallVirtual< OriginalFn >( this, 12 )( this );
		}
		void AlphaModulate( float alpha )
		{
			VirtualFn( void )( PVOID, float );
			CallVirtual< OriginalFn >( this, 27 )( this, alpha );
		}
		void ColorModulate( float r, float g, float b )
		{
			VirtualFn( void )( PVOID, float, float, float );
			CallVirtual< OriginalFn >( this, 28 )( this, r, g, b );
		}
		void SetMaterialVarFlag( MaterialVarFlags_t flag, bool on )
		{
			VirtualFn( void )( PVOID, MaterialVarFlags_t, bool );
			CallVirtual< OriginalFn >( this, 29 )( this, flag, on );
		}
	};
	class IModelInfo
	{
	public:
		int GetModelIndex( std::string strModelName )
		{
			const char* c = strModelName.c_str( );
			VirtualFn( int )( PVOID, const char* );
			return CallVirtual< OriginalFn >( this, 2 )( this, c );
		}
		std::string GetModelName( const model_t* pModel )
		{
			VirtualFn( const char* )( PVOID, const model_t* );
			return std::string( CallVirtual< OriginalFn >( this, 3 )( this, pModel ) );
		}
		int GetInt( std::string strKeyName, int iDefaultValue = 0 )
		{
			const char* c = strKeyName.c_str( );
			VirtualFn( int )( PVOID, const char*, int );
			return CallVirtual< OriginalFn >( this, 6 )( this, c, iDefaultValue );
		}
		void GetModelMaterials( const model_t* pModel, int iCount, IMaterial** ppMaterial )
		{
			VirtualFn( void )( PVOID, const model_t*, int, IMaterial** );
			CallVirtual< OriginalFn >( this, 17 )( this, pModel, iCount, ppMaterial );
		}
		studiohdr_t* GetStudioModel( const model_t* pModel )
		{
			VirtualFn( studiohdr_t* )( PVOID, const model_t* );
			return CallVirtual< OriginalFn >( this, 30 )( this, pModel );
		}
	};
	class IModelRender
	{
	public:
		void DrawModelExecute( PVOID pContext, const DrawModelState_t& pState, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld )
		{
			VirtualFn( void )( PVOID, PVOID, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4* );
			CallVirtual< OriginalFn >( this, 21 )( this, pContext, pState, pInfo, pCustomBoneToWorld );
		}
		void ForcedMaterialOverride( IMaterial *newMaterial, int nOverrideType = 0, int iUnknown = 0 )
		{
			VirtualFn( void )( PVOID, IMaterial*, int, int );
			CallVirtual< OriginalFn >( this, 1 )( this, newMaterial, nOverrideType, iUnknown );
		}
	};
	class IRenderView
	{
	public:
		void SetBlend( float blend )
		{
			VirtualFn( void )( PVOID, float );
			CallVirtual< OriginalFn >( this, 4 )( this, blend );
		}
		void SetColorModulation( float const* blend )
		{
			VirtualFn( void )( PVOID, float const* );
			CallVirtual< OriginalFn >( this, 6 )( this, blend );
		}
	};
	class IPanel
	{
	public:
		std::string GetName( unsigned int VGUIPanel )
		{
			VirtualFn( const char* )( PVOID, unsigned int );
			return std::string( CallVirtual< OriginalFn >( this, 36 )( this, VGUIPanel ) );
		}
	};
	class ISurface
	{
	public:
		void DrawSetColor( Color color )
		{
			VirtualFn( void )( PVOID, Color );
			CallVirtual< OriginalFn >( this, 14 )( this, color );
		}
		void DrawFilledRect( int x0, int y0, int x1, int y1 )
		{
			VirtualFn( void )( PVOID, int, int, int, int );
			CallVirtual< OriginalFn >( this, 16 )( this, x0, y0, x1, y1 );
		}
		void DrawOutlinedRect( int x0, int y0, int x1, int y1 )
		{
			VirtualFn( void )( PVOID, int, int, int, int );
			CallVirtual< OriginalFn >( this, 18 )( this, x0, y0, x1, y1 );
		}
		void DrawLine( int x0, int y0, int x1, int y1 )
		{
			VirtualFn( void )( PVOID, int, int, int, int );
			CallVirtual< OriginalFn >( this, 19 )( this, x0, y0, x1, y1 );
		}
		void DrawSetTextFont( HFont font )
		{
			VirtualFn( void )( PVOID, HFont );
			CallVirtual< OriginalFn >( this, 23 )( this, font );
		}
		void DrawSetTextColor( Color color )
		{
			VirtualFn( void )( PVOID, Color );
			CallVirtual< OriginalFn >( this, 24 )( this, color );
		}
		void DrawSetTextPos( int x, int y )
		{
			VirtualFn( void )( PVOID, int, int );
			CallVirtual< OriginalFn >( this, 26 )( this, x, y );
		}
		void DrawPrintText( const wchar_t* pwszText, int nLenght, FontDrawType_t drawType = FONT_DRAW_DEFAULT )
		{
			VirtualFn( void )( PVOID, const wchar_t*, int, FontDrawType_t );
			CallVirtual< OriginalFn >( this, 28 )( this, pwszText, nLenght, drawType );
		}
		HFont FontCreate( void )
		{
			VirtualFn( HFont )( PVOID );
			return CallVirtual< OriginalFn >( this, 71 )( this );
		}
		bool SetFontGlyphSet( HFont font, std::string szWindowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin, int nRangeMax )
		{
			VirtualFn( bool )( PVOID, HFont, const char*, int, int, int, int, int, int, int );
			return CallVirtual< OriginalFn >( this, 72 )( this, font, szWindowsFontName.c_str( ), tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax );
		}
		bool GetTextSize( HFont font, std::string szText, int& width, int& tall )
		{
			std::wstring wszString( szText.begin( ), szText.end( ) );

			VirtualFn( bool )( PVOID, HFont, const wchar_t*, int&, int& );
			return CallVirtual< OriginalFn >( this, 79 )( this, font, wszString.c_str( ), width, tall );
		}
		void GetCursorPos( int& x, int& y )
		{
			VirtualFn( void )( PVOID, int&, int& );
			CallVirtual< OriginalFn >( this, 100 )( this, x, y );
		}
		void GetCursorPos( int* piOut )
		{
			GetCursorPos( piOut[ 0 ], piOut[ 1 ] );
		}
		void DrawOutlinedCircle( int x, int y, int radius, int segments )
		{
			VirtualFn( void )( PVOID, int, int, int, int );
			CallVirtual< OriginalFn >( this, 103 )( this, x, y, radius, segments );
		}
	};
	class CRenderSurface
	{
	private:
		class CSurfaceFont
		{
		public:
			std::string	m_strName;
			std::string m_strWindowsFontName;
			int			m_iTall;
			int			m_iWeight;
			int			m_iBlur;
			int			m_iScanlines;
			int			m_iFlags;
			int			m_iRangeMin;
			int			m_iRangeMax;
			ULONG		m_Font;
		};
		typedef struct
		{
			int x, y, w, h;
		}Corner_t;

		Corner_t					m_Corner[ 8 ];
		bool						m_bSurfaceFontsCreated;
		ISurface*					m_pSurface;
		std::vector< CSurfaceFont >	m_vSurfaceFonts;

	private:
		int TweakColor( int c1, int c2, int variation )
		{
			if( c1 == c2 )
				return c1;
			else if( c1 < c2 )
				c1 += variation;
			else
				c1 -= variation;
			return c1;
		}
		std::size_t GetSurfaceFontIndex( std::string strName )
		{
			if( strName.empty( ) )
				return -1;

			for( std::size_t i = 0; i < m_vSurfaceFonts.size( ); i++ )
				if( !m_vSurfaceFonts[ i ].m_strName.compare( strName ) )
					return i;

			return -1;
		}
	public:
		CRenderSurface( ISurface* pSurface )
		{
			m_bSurfaceFontsCreated = false;
			SetSurface( pSurface );
		}
		ULONG GetSurfaceFont( std::string strName )
		{
			std::size_t nSurfaceFont = GetSurfaceFontIndex( strName );
			if( nSurfaceFont != -1 )
				return m_vSurfaceFonts[ nSurfaceFont ].m_Font;

			return NULL;
		}
		void AddFont( std::string strName, std::string strFont, int iWidth, int iWeight, int iBlur, int iScanLines, int iFlags, int iRangeMin = 0, int iRangeMax = 0 )
		{
			if( !m_bSurfaceFontsCreated )
			{
				if( GetSurfaceFontIndex( strName ) != -1 )
					return;

				CSurfaceFont font;
				font.m_strName = strName;
				font.m_strWindowsFontName = strFont;
				font.m_iTall = iWidth;
				font.m_iWeight = iWeight;
				font.m_iBlur = iBlur;
				font.m_iScanlines = iScanLines;
				font.m_iFlags = iFlags;
				font.m_iRangeMin = iRangeMin;
				font.m_iRangeMax = iRangeMax;

				m_vSurfaceFonts.push_back( font );
			}
		}
		void BorderBox( int x, int y, int w, int h, int thickness, Color color )
		{
			this->Rect( x, y, w, thickness, color );
			this->Rect( x, y, thickness, h, color );
			this->Rect( x + w, y, thickness, h, color );
			this->Rect( x, y + h, w + thickness, thickness, color );
		}
		void BorderBoxOutlined( int x, int y, int w, int h, int thickness, Color color, Color outlined )
		{
			this->BorderBox( x, y, w, h, thickness, color );
			this->BorderBox( x - 1, y - 1, w + 2, h + 2, 1, outlined );
			this->BorderBox( x + 1, y + 1, w - 2, h - 2, 1, outlined );
		}
		void Circle( int x, int y, int radius, int segments, Color color )
		{
			m_pSurface->DrawSetColor( color );
			m_pSurface->DrawOutlinedCircle( x, y, radius, segments );
		}
		void CornerBox( int x, int y, int w, int h, Color color, bool outlined, int indicatorH = 5, int indicatorW = 5 )
		{
			m_Corner[ 0 ].x = x;
			m_Corner[ 0 ].y = y;
			m_Corner[ 0 ].w = w / indicatorW;
			m_Corner[ 0 ].h = 1;

			m_Corner[ 1 ].x = x + w - ( w / indicatorW );
			m_Corner[ 1 ].y = y;
			m_Corner[ 1 ].w = w / indicatorW;
			m_Corner[ 1 ].h = 1;

			m_Corner[ 2 ].x = x;
			m_Corner[ 2 ].y = y + h;
			m_Corner[ 2 ].w = w / indicatorW;
			m_Corner[ 2 ].h = 1;

			m_Corner[ 3 ].x = x + w - ( w / indicatorW );
			m_Corner[ 3 ].y = y + h;
			m_Corner[ 3 ].w = w / indicatorW;
			m_Corner[ 3 ].h = 1;

			m_Corner[ 4 ].x = x;
			m_Corner[ 4 ].y = y;
			m_Corner[ 4 ].w = 1;
			m_Corner[ 4 ].h = h / indicatorH;

			m_Corner[ 5 ].x = x + w - 1;
			m_Corner[ 5 ].y = y;
			m_Corner[ 5 ].w = 1;
			m_Corner[ 5 ].h = h / indicatorH;

			m_Corner[ 6 ].x = x;
			m_Corner[ 6 ].y = y + h - ( h / indicatorH );
			m_Corner[ 6 ].w = 1;
			m_Corner[ 6 ].h = h / indicatorH;

			m_Corner[ 7 ].x = x + w - 1;
			m_Corner[ 7 ].y = y + h - ( h / indicatorH ) + 1;
			m_Corner[ 7 ].w = 1;
			m_Corner[ 7 ].h = h / indicatorH;

			if( outlined )
				for( int i = 0; i < 8; i++ )
				{
					Rect( m_Corner[ i ].x - 1, m_Corner[ i ].y - 1, m_Corner[ i ].w + 2, m_Corner[ i ].h + 2, Color( 0, 0, 0, 255 ) );
					Rect( m_Corner[ i ].x + 1, m_Corner[ i ].y + 1, m_Corner[ i ].w - 2, m_Corner[ i ].h - 2, Color( 0, 0, 0, 255 ) );
				}

			for( int i = 0; i < 8; i++ )
				Rect( m_Corner[ i ].x, m_Corner[ i ].y, m_Corner[ i ].w, m_Corner[ i ].h, color );
		}
		void GardientRect( int x, int y, int w, int h, Color color1, Color color2, int variation )
		{
			int r1 = color1.r( );
			int g1 = color1.g( );
			int b1 = color1.b( );
			int a1 = color1.a( );

			int r2 = color2.r( );
			int g2 = color2.g( );
			int b2 = color2.b( );
			int a2 = color2.a( );

			for( int i = 0; i <= w; i++ )
			{
				Rect( x + i, y, 1, h, Color( r1, g1, b1, a1 ) );
				r1 = TweakColor( r1, r2, variation );
				g1 = TweakColor( g1, g2, variation );
				b1 = TweakColor( b1, b2, variation );
				a1 = TweakColor( a1, a2, variation );
			}
		}
		void GetTextSize( std::string szFontWrapperName, std::string szString, int& iWidth, int& iHeight )
		{
			if( szFontWrapperName.empty( ) || szString.empty( ) )
				return;

			UINT nFont = GetSurfaceFont( szFontWrapperName );
			if( !nFont )
				return;

			GetTextSize( nFont, szString, iWidth, iHeight );
		}
		void GetTextSize( ULONG Font, std::string szString, int& iWidth, int& iHeight )
		{
			if( szString.empty( ) )
				return;

			if( !Font )
				return;

			m_pSurface->GetTextSize( Font, szString, iWidth, iHeight );
		}
		void GetTextSize( std::string szFontWrapperName, std::string szString, int* iTextSize )
		{
			GetTextSize( szFontWrapperName, szString, iTextSize[ 0 ], iTextSize[ 1 ] );
		}
		void Line( int x0, int y0, int x1, int y1, Color color )
		{
			m_pSurface->DrawSetColor( color );
			m_pSurface->DrawLine( x0, y0, x1, y1 );
		}
		void Rect( int x, int y, int w, int h, Color color )
		{
			m_pSurface->DrawSetColor( color );
			m_pSurface->DrawFilledRect( x, y, x + w, y + h );
		}
		void RectOutlined( int x, int y, int w, int h, int thickness, Color color, Color outlined )
		{
			this->Rect( x, y, w, h, color );
			this->BorderBox( x - thickness, y - thickness, w + thickness, h + thickness, thickness, outlined );
		}
		void StringOutlined( int x, int y, Color color, std::string szFontWrapperName, const char* fmt, ... )
		{
			ULONG SurfaceFont = GetSurfaceFont( szFontWrapperName );
			if( !SurfaceFont )
				return;

			va_list args;
			va_start( args, fmt );
			char szBuffer[ 1024 ];
			vsprintf_s( szBuffer, fmt, args );
			va_end( args );

			this->StringOutlined( x, y, color, SurfaceFont, szBuffer );

		}
		void String( int x, int y, Color color, ULONG font, const char* fmt, ... )
		{
			va_list args;
			va_start( args, fmt );
			char szBuffer[ 1024 ];
			vsprintf_s( szBuffer, fmt, args );

			m_pSurface->DrawSetTextPos( x, y );
			m_pSurface->DrawSetTextFont( font );
			m_pSurface->DrawSetTextColor( color );

			int nChars = MultiByteToWideChar( CP_ACP, 0, szBuffer, -1, NULL, 0 );

			const WCHAR *pwcsName;
			pwcsName = new WCHAR[ nChars ];
			MultiByteToWideChar( CP_ACP, 0, szBuffer, -1, ( LPWSTR )pwcsName, nChars );

			va_end( args );

			m_pSurface->DrawPrintText( pwcsName, wcslen( pwcsName ) );
		}
		void String( int x, int y, Color color, std::string szFontWrapperName, const char* fmt, ... )
		{
			ULONG SurfaceFont = GetSurfaceFont( szFontWrapperName );
			if( !SurfaceFont )
				return;

			va_list args;
			va_start( args, fmt );
			char szBuffer[ 1024 ];
			vsprintf_s( szBuffer, fmt, args );

			this->String( x, y, color, SurfaceFont, szBuffer );
		}
		void StringOutlined( int x, int y, Color color, ULONG font, const char* fmt, ... )
		{
			std::string szBuffer;
			va_list args;
			va_start( args, fmt );
			int iSize = _vscprintf( fmt, args );
			szBuffer.resize( iSize );
			vsnprintf_s( ( char* )szBuffer.data( ), iSize, _TRUNCATE, fmt, args );
			va_end( args );


			this->String( x - 1, y, Color( 0, 0, 0, 255 ), font, szBuffer.c_str( ) );
			this->String( x, y - 1, Color( 0, 0, 0, 255 ), font, szBuffer.c_str( ) );

			this->String( x + 1, y, Color( 0, 0, 0, 255 ), font, szBuffer.c_str( ) );
			this->String( x, y + 1, Color( 0, 0, 0, 255 ), font, szBuffer.c_str( ) );
			this->String( x, y, color, font, szBuffer.c_str( ) );

			va_end( args );
		}
		void CreateAllFonts( void )
		{
			if( !m_bSurfaceFontsCreated )
			{
				for( std::size_t i = 0; i < m_vSurfaceFonts.size( ); i++ )
				{
					m_vSurfaceFonts.at( i ).m_Font = m_pSurface->FontCreate( );
					m_pSurface->SetFontGlyphSet( m_vSurfaceFonts.at( i ).m_Font,
						m_vSurfaceFonts.at( i ).m_strWindowsFontName.c_str( ),
						m_vSurfaceFonts.at( i ).m_iTall,
						m_vSurfaceFonts.at( i ).m_iWeight,
						m_vSurfaceFonts.at( i ).m_iBlur,
						m_vSurfaceFonts.at( i ).m_iScanlines,
						m_vSurfaceFonts.at( i ).m_iFlags,
						m_vSurfaceFonts.at( i ).m_iRangeMin,
						m_vSurfaceFonts.at( i ).m_iRangeMax );
				}


				m_bSurfaceFontsCreated = true;
			}
		}
		void SetSurface( ISurface* pSurface )
		{
			m_pSurface = pSurface;
		}
	};
	class IMultiplayerPhysics
	{
	public:
		virtual int		GetMultiplayerPhysicsMode( void ) = 0;
		virtual float	GetMass( void ) = 0;
		virtual bool	IsAsleep( void ) = 0;
	};
	class IBreakableWithPropData
	{
	public:
		// Damage modifiers
		virtual void            SetDmgModBullet( float flDmgMod ) = 0;
		virtual void            SetDmgModClub( float flDmgMod ) = 0;
		virtual void            SetDmgModExplosive( float flDmgMod ) = 0;
		virtual float           GetDmgModBullet( void ) = 0;
		virtual float           GetDmgModClub( void ) = 0;
		virtual float           GetDmgModExplosive( void ) = 0;
		// Explosive
		virtual void            SetExplosiveRadius( float flRadius ) = 0;
		virtual void            SetExplosiveDamage( float flDamage ) = 0;
		virtual float           GetExplosiveRadius( void ) = 0;
		virtual float           GetExplosiveDamage( void ) = 0;
		// Physics damage tables
		virtual void            SetPhysicsDamageTable( char* iszTableName ) = 0;
		virtual char*           GetPhysicsDamageTable( void ) = 0;
		// Breakable chunks
		virtual void            SetBreakableModel( char* iszModel ) = 0;
		virtual char*           GetBreakableModel( void ) = 0;
		virtual void            SetBreakableSkin( int iSkin ) = 0;
		virtual int                     GetBreakableSkin( void ) = 0;
		virtual void            SetBreakableCount( int iCount ) = 0;
		virtual int                     GetBreakableCount( void ) = 0;
		virtual void            SetMaxBreakableSize( int iSize ) = 0;
		virtual int                     GetMaxBreakableSize( void ) = 0;
		// LOS blocking
		virtual void            SetPropDataBlocksLOS( bool bBlocksLOS ) = 0;
		virtual void            SetPropDataIsAIWalkable( bool bBlocksLOS ) = 0;
		// Interactions
		virtual void            SetInteraction( propdata_interactions_t Interaction ) = 0;
		virtual bool            HasInteraction( propdata_interactions_t Interaction ) = 0;
		// Multi player physics mode
		virtual void            SetPhysicsMode( int iMode ) = 0;
		virtual int                     GetPhysicsMode( ) = 0;
		// Multi player breakable spawn behavior
		virtual void            SetMultiplayerBreakMode( mp_break_t mode ) = 0;
		virtual mp_break_t      GetMultiplayerBreakMode( void ) const = 0;
		// Used for debugging
		virtual void            SetBasePropData( char* iszBase ) = 0;
		virtual char*           GetBasePropData( void ) = 0;
	};
	class IPhysicsSurfaceProps
	{
	public:
		virtual ~IPhysicsSurfaceProps( void ) {}
		virtual int				ParseSurfaceData( const char *pFilename, const char *pTextfile ) = 0;
		virtual int				SurfacePropCount( void ) const = 0;
		virtual int				GetSurfaceIndex( const char *pSurfacePropName ) const = 0;
		virtual void			GetPhysicsProperties( int surfaceDataIndex, float *density, float *thickness, float *friction, float *elasticity ) const = 0;
		virtual surfacedata_t*	GetSurfaceData( int surfaceDataIndex ) = 0;
		virtual const char*		GetString( unsigned short stringTableIndex ) const = 0;
		virtual const char*		GetPropName( int surfaceDataIndex ) const = 0;
		virtual void			SetWorldMaterialIndexTable( int *pMapArray, int mapSize ) = 0;
		virtual void			GetPhysicsParameters( int surfaceDataIndex, surfacephysicsparams_t *pParamsOut ) const = 0;
	};
	class KeyValues
	{
	public:
		static void SetUseGrowableStringTable( bool bUseGrowableTable );

		KeyValues( const char *setName )
		{
			Init( );
			SetName( setName );
		}

		class AutoDelete
		{
		public:
			explicit inline AutoDelete( KeyValues *pKeyValues ) : m_pKeyValues( pKeyValues ) {}
			explicit inline AutoDelete( const char *pchKVName ) : m_pKeyValues( new KeyValues( pchKVName ) ) {}
			inline ~AutoDelete( void ) { if( m_pKeyValues ) m_pKeyValues->deleteThis( ); }
			inline void Assign( KeyValues *pKeyValues ) { m_pKeyValues = pKeyValues; }
			KeyValues *operator->( )	{ return m_pKeyValues; }
			operator KeyValues *( )	{ return m_pKeyValues; }
		private:
			AutoDelete( AutoDelete const &x ); // forbid
			AutoDelete & operator= ( AutoDelete const &x ); // forbid
			KeyValues *m_pKeyValues;
		};

		const char *GetName( ) const;
		void SetName( const char *setName )
		{
			m_iKeyName = 2;
		}

		int GetNameSymbol( ) const { return m_iKeyName; }

		void UsesEscapeSequences( bool state ); // default false
		void UsesConditionals( bool state ); // default true

		KeyValues *FindKey( const char *keyName, bool bCreate = false );
		KeyValues *FindKey( int keySymbol ) const;
		KeyValues *CreateNewKey( );		// creates a new key, with an autogenerated name.  name is guaranteed to be an integer, of value 1 higher than the highest other integer key name
		void AddSubKey( KeyValues *pSubkey );	// Adds a subkey. Make sure the subkey isn't a child of some other keyvalues
		void RemoveSubKey( KeyValues *subKey );	// removes a subkey from the list, DOES NOT DELETE IT

		KeyValues *GetFirstSubKey( ) { return m_pSub; }	// returns the first subkey in the list
		KeyValues *GetNextKey( ) { return m_pPeer; }		// returns the next subkey
		void SetNextKey( KeyValues * pDat );
		KeyValues *FindLastSubKey( );	// returns the LAST subkey in the list.  This requires a linked list iteration to find the key.  Returns NULL if we don't have any children

		KeyValues* GetFirstTrueSubKey( );
		KeyValues* GetNextTrueSubKey( );

		KeyValues* GetFirstValue( );	// When you get a value back, you can use GetX and pass in NULL to get the value.
		KeyValues* GetNextValue( );

		// Data access
		int   GetInt( const char *keyName = NULL, int defaultValue = 0 );
		float GetFloat( const char *keyName = NULL, float defaultValue = 0.0f );
		const char *GetString( const char *keyName = NULL, const char *defaultValue = "" );
		const wchar_t *GetWString( const char *keyName = NULL, const wchar_t *defaultValue = L"" );
		void *GetPtr( const char *keyName = NULL, void *defaultValue = ( void* )0 );
		bool GetBool( const char *keyName = NULL, bool defaultValue = false );
		bool  IsEmpty( const char *keyName = NULL );

		// Data access
		int   GetInt( int keySymbol, int defaultValue = 0 );
		float GetFloat( int keySymbol, float defaultValue = 0.0f );
		const char *GetString( int keySymbol, const char *defaultValue = "" );
		const wchar_t *GetWString( int keySymbol, const wchar_t *defaultValue = L"" );
		void *GetPtr( int keySymbol, void *defaultValue = ( void* )0 );
		bool  IsEmpty( int keySymbol );

		// Key writing
		void SetWString( const char *keyName, const wchar_t *value );
		void SetString( const char *keyName, const char *value );
		void SetInt( const char *keyName, int value );
		void SetUint64( const char *keyName, UINT value );
		void SetFloat( const char *keyName, float value );
		void SetPtr( const char *keyName, void *value );
		void SetBool( const char *keyName, bool value ) { SetInt( keyName, value ? 1 : 0 ); }

		KeyValues& operator=( KeyValues& src );

		// Adds a chain... if we don't find stuff in this keyvalue, we'll look
		// in the one we're chained to.
		void ChainKeyValue( KeyValues* pChain );

		// Allocate & create a new copy of the keys
		KeyValues *MakeCopy( void ) const;

		// Make a new copy of all subkeys, add them all to the passed-in keyvalues
		void CopySubkeys( KeyValues *pParent ) const;

		// Clear out all subkeys, and the current value
		void Clear( void );

		// Data type
		enum types_t
		{
			TYPE_NONE = 0,
			TYPE_STRING,
			TYPE_INT,
			TYPE_FLOAT,
			TYPE_PTR,
			TYPE_WSTRING,
			TYPE_COLOR,
			TYPE_UINT64,
			TYPE_NUMTYPES,
		};
		types_t GetDataType( const char *keyName = NULL );

		// Virtual deletion function - ensures that KeyValues object is deleted from correct heap
		void deleteThis( );

		void SetStringValue( char const *strValue );

		// unpack a key values list into a structure
		void UnpackIntoStructure( struct KeyValuesUnpackStructure const *pUnpackTable, void *pDest, size_t DestSizeInBytes );

		// Process conditional keys for widescreen support.
		bool ProcessResolutionKeys( const char *pResString );

		// Dump keyvalues recursively into a dump context
		bool Dump( class IKeyValuesDumpContext *pDump, int nIndentLevel = 0 );

		// Merge in another KeyValues, keeping "our" settings
		void RecursiveMergeKeyValues( KeyValues *baseKV );

	public:
		KeyValues( KeyValues& );	// prevent copy constructor being used

		// prevent delete being called except through deleteThis()
		~KeyValues( );

		KeyValues* CreateKey( const char *keyName );

		KeyValues* CreateKeyUsingKnownLastChild( const char *keyName, KeyValues *pLastChild );
		void AddSubkeyUsingKnownLastChild( KeyValues *pSubKey, KeyValues *pLastChild );

		void RecursiveCopyKeyValues( KeyValues& src );
		void RemoveEverything( );

		void Init( )
		{
			m_iKeyName = -1;
			m_iDataType = TYPE_NONE;

			m_pSub = NULL;
			m_pPeer = NULL;
			m_pChain = NULL;

			m_sValue = NULL;
			m_wsValue = NULL;
			m_pValue = NULL;

			m_bHasEscapeSequences = false;

			// for future proof
			memset( unused, 0, sizeof( unused ) );
		}

		void FreeAllocatedValue( );
		void AllocateValueBlock( int size );

		int m_iKeyName;	// keyname is a symbol defined in KeyValuesSystem

		// These are needed out of the union because the API returns string pointers
		char *m_sValue;
		wchar_t *m_wsValue;

		// we don't delete these
		union
		{
			int m_iValue;
			float m_flValue;
			void *m_pValue;
			unsigned char m_Color[ 4 ];
		};

		char	   m_iDataType;
		char	   m_bHasEscapeSequences; // true, if while parsing this KeyValue, Escape Sequences are used (default false)
		char	   m_bEvaluateConditionals; // true, if while parsing this KeyValue, conditionals blocks are evaluated (default true)
		char	   unused[ 1 ];

		KeyValues *m_pPeer;	// pointer to next key in list
		KeyValues *m_pSub;	// pointer to Start of a new sub key list
		KeyValues *m_pChain;// Search here if it's not in our list

	private:
		// Statics to implement the optional growable string table
		// Function pointers that will determine which mode we are in
		static int( *s_pfGetSymbolForString )( const char *name, bool bCreate );
		static const char *( *s_pfGetStringForSymbol )( int symbol );

	public:
		// Functions that invoke the default behavior
		static int GetSymbolForStringClassic( const char *name, bool bCreate = true );
		static const char *GetStringForSymbolClassic( int symbol );

		// Functions that use the growable string table
		static int GetSymbolForStringGrowable( const char *name, bool bCreate = true );
		static const char *GetStringForSymbolGrowable( int symbol );

		// Functions to get external access to whichever of the above functions we're going to call.
		static int CallGetSymbolForString( const char *name, bool bCreate = true ) { return s_pfGetSymbolForString( name, bCreate ); }
		static const char *CallGetStringForSymbol( int symbol ) { return s_pfGetStringForSymbol( symbol ); }

		bool LoadFromBuffer( KeyValues *pThis, const char *pszFirst, const char *pszSecond, PVOID pSomething = 0, PVOID pAnother = 0, PVOID pLast = 0 )
		{
			typedef bool( __thiscall *LoadFromBuffer_t )( KeyValues*, const char*, const char*, PVOID, PVOID, PVOID );

			static LoadFromBuffer_t callLoadBuff = ( LoadFromBuffer_t )( Offsets::m_dwLoadFromBuffer );

			return callLoadBuff( pThis, pszFirst, pszSecond, pSomething, pAnother, pLast );
		}//wait i will check my code
	};
	class IMaterialSystem
	{
	public:
		IMaterial* CreateMaterial( const char* pMaterialName, KeyValues* pVMTKeyValues )
		{
			VirtualFn( IMaterial* )( PVOID, const char*, KeyValues* );
			return CallVirtual< OriginalFn >( this, 83 )( this, pMaterialName, pVMTKeyValues );
		}
		IMaterial* FindMaterial( const char* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = 0 )
		{
			VirtualFn( IMaterial* )( PVOID, const char*, const char*, bool, const char* );
			return CallVirtual< OriginalFn >( this, 84 )( this, pMaterialName, pTextureGroupName, complain, pComplainPrefix );
		}
	};
	class CHudTexture
	{
	public:
		PAD( 0x82 );
		char	m_szCharacter;
	};
	class CWeaponData
	{
	public:
		char			m_szPrintName[ 32 ];				// 0x0000 
		PAD( 0x158 );
		int				m_iBucket;							// 0x0178 
		int				m_iBucketPosition;					// 0x017C 
		int				m_iClipSize;						// 0x0180 
		int				m_iDefaultClip1;					// 0x0184 
		int				m_iDefaultClip2;					// 0x0188 
		PAD( 0x4 );
		int				m_iWeight;							// 0x0190 
		int				m_iRumble;							// 0x0194 
		PAD( 0x78 );
		char			m_szEmpty[ 80 ];					// 0x0210 
		char			m_szSingleShot[ 80 ];				// 0x0260 
		PAD( 0x140 );
		char			m_szReload[ 80 ];					// 0x03F0 
		PAD( 0x2E0 );
		CHudTexture*	m_pWeaponIcon;						// 0x0720 
		CHudTexture*	m_pWeaponSIcon;						// 0x0724 
		CHudTexture*	m_pAmmoIcon;						// 0x0728 
		PAD( 0x2C );
		float			m_flHeatPerShot;					// 0x0758 
		int				m_iWeaponPrice;						// 0x075C 
		float			m_flWeaponArmorRatio;				// 0x0760 
		float			m_flMaxPlayerSpeed;					// 0x0764 
		float			m_flMaxPlayerSpeed2;				// 0x0768 
		int				m_iCrosshairMinDist;				// 0x076C 
		int				m_iCrosshairDeltaDist;				// 0x0770 
		float			m_flPenetration;					// 0x0774 
		int				m_iDamage;							// 0x0778 
		float			m_flRange;							// 0x077C 
		float			m_flRangeModifier;					// 0x0780 
		int				m_iBullet;							// 0x0784 
		float			m_flCycleTime;						// 0x0788 
		PAD( 0x184 );
		char			m_szViewModel[ 32 ];				// 0x0910 
		float			m_flSpread;							// 0x0930 
		float			m_flSpreadAlt;						// 0x0934 
		float			m_flInacurracyCrouch;				// 0x0938 
		float			m_flInaccuracyCrouchAlt;			// 0x093C 
		float			m_flInaccuracyStand;				// 0x0940 
		float			m_flInaccuracyStandAlt;				// 0x0944 
		float			m_flInaccuracyJump;					// 0x0948 
		float			m_flInaccuracyJumpAlt;				// 0x094C 
		float			m_flInaccuracyLand;					// 0x0950 
		float			m_flInaccuracyLandAlt;				// 0x0954 
		float			m_flInaccuracyLadder;				// 0x0958 
		float			m_flInaccuracyLadderAlt;			// 0x095C 
		float			m_flInaccuracyFire;					// 0x0960 
		float			m_flInaccuracyFireAlt;				// 0x0964 
		float			m_flInaccuracyMove;					// 0x0968 
		float			m_flInaccuracyMoveAlt;				// 0x096C 
		PAD( 0x10 );
		float			m_flRecoilAngle;					// 0x0980 
		PAD( 0x4 );
		float			m_flRecoilAngleVariance;			// 0x0988 
		PAD( 0x4 );
		float			m_flRecoilMagnitude;				// 0x0990 
		PAD( 0x4 );
		float			m_flRecoilMagnitudeVariance;		// 0x0998 
		PAD( 0x8 );
		float			m_flFlinchVelocityModifierLarge;	// 0x09A4 
		float			m_flFlinchVelocityModifierSmall;	// 0x09A8 
		PAD( 0x408 );
		int				m_iZoomLevels;						// 0x0DB4 
		PAD( 0x4 );
		int				m_iZoomFov1;						// 0x0DBC 
		int				m_iZoomFov2;						// 0x0DC0 
		float			m_flZoomTime0;						// 0x0DC4 
		float			m_flZoomTime1;						// 0x0DC8 
		float			m_flZoomTime2;						// 0x0DCC 
		PAD( 0x220 );
	};
	class CBaseCombatWeapon
	{
	public:
		bool IsPistol( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_PISTOLS ? true : false;
		}
		bool IsTaser( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_TASER ? true : false;
		}
		bool IsShotgun( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_SHOTGUN ? true : false;
		}
		bool IsSMG( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_SMG ? true : false;
		}
		bool IsRifle( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_RIFLE ? true : false;
		}
		bool IsMG( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_MG ? true : false;
		}
		bool IsSniper( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_SNIPER ? true : false;
		}
		bool IsGrenade( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_GRENADE;
		}
		bool IsKnife( void )
		{
			return GetItemSchemaWeaponType( ) == WEAPON_TYPE_KNIFE ? true : false;
		}
		bool IsValid( bool bTaserIsValid = false )
		{
			int iItemSchemaWeaponType = GetItemSchemaWeaponType( );

			switch( iItemSchemaWeaponType )
			{
			case WEAPON_TYPE_PISTOLS:
				break;
			case WEAPON_TYPE_SHOTGUN:
				break;
			case WEAPON_TYPE_SMG:
				break;
			case WEAPON_TYPE_RIFLE:
				break;
			case WEAPON_TYPE_MG:
				break;
			case WEAPON_TYPE_SNIPER:
				break;
			case WEAPON_TYPE_TASER:
				if( bTaserIsValid )
					break;
				else return false;
			default:
				return false;
			}

			return( GetClip1( ) > 0 );
		}
		bool IsAutomatic( bool bAutoSniper = false )
		{
			if( bAutoSniper )
			{
				int iItemSchemaId = GetItemDefinitionIndex( );
				if( iItemSchemaId == WEAPON_SCAR20 || WEAPON_G3SG1 )
					return true;
			}

			int iItemSchemaWeaponType = GetItemSchemaWeaponType( );
			switch( iItemSchemaWeaponType )
			{
			case WEAPON_TYPE_SMG:
				return true;
			case WEAPON_TYPE_RIFLE:
				return true;
			case WEAPON_TYPE_MG:
				return true;
			default:
				break;
			}

			return false;
		}
		bool HitChance( float flChance )
		{
			if( flChance >= 99.f )
				flChance = 99.f;

			if( flChance < 1 )
				flChance = 1;

			float flSpread = GetSpread( );
			return( ( ( ( 100.f - flChance ) * 0.65f ) * 0.01125 ) >= flSpread );
		}
		CWeaponData* GetWeaponData( void )
		{
			VirtualFn( CWeaponData* )( PVOID );
			return CallVirtual< OriginalFn >( this, 450 )( this );
		}
		float GetSpread( void )
		{
			VirtualFn( float )( PVOID );
			return CallVirtual< OriginalFn >( this, 478 )( this );
		}
		float GetInaccuracy( void )
		{
			VirtualFn( float )( PVOID );
			return CallVirtual< OriginalFn >( this, 479 )( this );
		}
		float GetNextPrimaryAttack( void )
		{
			return *( float* )( ( DWORD )this + Offsets::m_flNextPrimaryAttack );
		}
		int GetClip1( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iClip1 );
		}
		int GetItemDefinitionIndex( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iItemDefinitionIndex );
		}
		int GetItemSchemaWeaponType( void )
		{
			int iItemSchemaId = GetItemDefinitionIndex( );

			switch( iItemSchemaId )
			{
			case WEAPON_DEAGLE:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_DUALS:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_FIVE7:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_GLOCK:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_AK47:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_AUG:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_AWP:
				return WEAPON_TYPE_SNIPER;
			case WEAPON_FAMAS:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_G3SG1:
				return WEAPON_TYPE_SNIPER;
			case WEAPON_GALIL:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_M249:
				return WEAPON_TYPE_MG;
			case WEAPON_M4A1:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_MAC10:
				return WEAPON_TYPE_SMG;
			case WEAPON_P90:
				return WEAPON_TYPE_SMG;
			case WEAPON_UMP45:
				return WEAPON_TYPE_SMG;
			case WEAPON_XM1014:
				return WEAPON_TYPE_SHOTGUN;
			case WEAPON_BIZON:
				return WEAPON_TYPE_SMG;
			case WEAPON_MAG7:
				return WEAPON_TYPE_SHOTGUN;
			case WEAPON_NEGEV:
				return WEAPON_TYPE_MG;
			case WEAPON_SAWEDOFF:
				return WEAPON_TYPE_SHOTGUN;
			case WEAPON_TEC9:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_TASER:
				return WEAPON_TYPE_TASER;
			case WEAPON_P2000:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_MP7:
				return WEAPON_TYPE_SMG;
			case WEAPON_MP9:
				return WEAPON_TYPE_SMG;
			case WEAPON_NOVA:
				return WEAPON_TYPE_SHOTGUN;
			case WEAPON_P250:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_SCAR20:
				return WEAPON_TYPE_SNIPER;
			case WEAPON_SG553:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_SCOUT:
				return WEAPON_TYPE_SNIPER;
			case WEAPON_KNIFE_T:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_FLASH:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_HE:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_SMOKE:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_MOLOTOV:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_DECOY:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_INC:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_C4:
				return WEAPON_TYPE_GRENADE;
			case WEAPON_KNIFE_CT:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_M4A1S:
				return WEAPON_TYPE_RIFLE;
			case WEAPON_USPS:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_CZ75:
				return WEAPON_TYPE_PISTOLS;
			case WEAPON_KNIFE_BAYONET:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_FLIP:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_GUT:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_KARAMBIT:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_M9BAYONET:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_FALCHION:
				return WEAPON_TYPE_KNIFE;
			case WEAPON_KNIFE_BUTTERFLY:
				return WEAPON_TYPE_KNIFE;
			default:
				break;
			}

			return WEAPON_TYPE_INVALID;
		}
		int GetWeaponId( void )
		{
			return GetItemDefinitionIndex( );
		}
		void UpdateAccuracyPenalty( void )
		{
			VirtualFn( void )( PVOID );
			CallVirtual< OriginalFn >( this, 480 )( this );
		}
		void SetPattern( const int skin, float condition, int seed, bool bIsKnife = false, int StatTrak = -1 )
		{
			if( condition > 99.f )
				condition = 99.f;

			*( int* )( ( DWORD )this + Offsets::m_OriginalOwnerXuidLow ) = 0;
			*( int* )( ( DWORD )this + Offsets::m_OriginalOwnerXuidHigh ) = 0;
			*( int* )( ( DWORD )this + Offsets::m_nFallbackSeed ) = seed;
			*( int* )( ( DWORD )this + Offsets::m_nFallbackPaintKit ) = skin;
			*( float* )( ( DWORD )this + Offsets::m_flFallbackWear ) = 0.99f - ( condition / 100.f );
			*( int* )( ( DWORD )this + Offsets::m_iItemIDHigh ) = 1;

			if( StatTrak > 0 || bIsKnife )
				* ( int* )( ( DWORD )this + Offsets::m_iItemIDHigh - 0x10 ) = bIsKnife ? 3 : 1;
			*( int* )( ( DWORD )this + Offsets::m_nFallbackStatTrak ) = ( StatTrak > 0 ) ? StatTrak : -1;

			if( *( int* )( ( DWORD )this + Offsets::m_iItemIDHigh ) > 1 )
				* ( int* )( ( DWORD )this + Offsets::m_iItemIDHigh ) = 0;
		}
	};
	class CBaseEntity
	{
	public:
		CBaseCombatWeapon* GetWeapon( void )
		{
			EHANDLE hWeapon = GetActiveWeapon( );
			if( !hWeapon )
				return nullptr;

			return ( CBaseCombatWeapon* )g_pEntityList->GetBaseEntityFromHandle( hWeapon );
		}
		bool IsValid( bool bIsProtected = false )
		{
			bool bRetVal = ( GetLifeState( ) == LIFE_ALIVE && GetHealth( ) >= 1 && !IsDormant( ) ) ? true : false;
			if( bIsProtected && IsProtected( ) )
				bRetVal = false;

			return bRetVal;
		}
		bool IsDormant( void )
		{
			VirtualFn( bool )( PVOID );
			PVOID pNetworkable = GetNetworkable( );
			return CallVirtual< OriginalFn >( pNetworkable, 9 )( pNetworkable );
		}
		bool IsScoped( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bIsScoped );
		}
		bool HasHelmet( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bHasHelmet );
		}
		bool IsBroken( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bIsBroken );
		}
		bool IsDefusing( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bIsDefusing );
		}
		bool IsProtected( void )
		{
			return *( bool* )( ( DWORD )this + Offsets::m_bGunGameImmunity );
		}
		bool SetupBones( matrix3x4* pBoneToWorldOut, int iMaxBones, int iBoneMask, float flCurrentTime )
		{
			VirtualFn( bool )( PVOID, matrix3x4*, int, int, float );
			PVOID pRenderable = GetRenderable( );
			return CallVirtual< OriginalFn >( pRenderable, 13 )( pRenderable, pBoneToWorldOut, iMaxBones, iBoneMask, flCurrentTime );
		}
		BYTE GetFlags( void )
		{
			return *( BYTE* )( ( DWORD )this + Offsets::m_fFlags );
		}
		BYTE GetLifeState( void )
		{
			return *( BYTE* )( ( DWORD )this + Offsets::m_lifeState );
		}
		BYTE GetMoveType( void )
		{
			return *( BYTE* )( ( DWORD )this + Offsets::m_moveType );
		}
		Color GetTeamColor( bool bIsVisible = false )
		{
			int iTeam = GetTeam( );

			Color color = ( iTeam == 2 ) ? Color( 255, 0, 0 ) : Color( 0, 176, 255 );
			if( bIsVisible )
				color = ( iTeam == 2 ) ? Color( 255, 201, 14 ) : Color( 0, 255, 0 );

			return color;
		}
		Color GetHealthColor( void )
		{
			float flHealth = ( float )GetHealth( );
			float r = 255.f - flHealth * 2.55f;
			float g = flHealth * 2.55f;
			return Color( int( r ), int( g ), 0 );
		}
		ClientClass* GetClientClass( void )
		{
			VirtualFn( ClientClass* )( PVOID );
			PVOID pNetworkable = GetNetworkable( );
			return CallVirtual< OriginalFn >( pNetworkable, 2 )( pNetworkable );
		}
		EHANDLE GetActiveWeapon( void )
		{
			return *( EHANDLE* )( ( DWORD )this + Offsets::m_hActiveWeapon );
		}
		int GetArmorValue( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_ArmorValue );
		}
		int GetCollisionGroup( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_CollisionGroup );
		}
		int GetMoney( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iAccount );
		}
		int GetHealth( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iHealth );
		}
		int GetTeam( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iTeamNum );
		}
		int GetTickBase( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_nTickBase );
		}
		int GetShotsFired( void )
		{
			return *( int* )( ( DWORD )this + Offsets::m_iShotsFired );
		}
		int GetIndex( void )
		{
			VirtualFn( int )( PVOID );
			PVOID pNetworkable = GetNetworkable( );
			return CallVirtual< OriginalFn >( pNetworkable, 10 )( pNetworkable );
		}
		model_t* GetModel( void )
		{
			VirtualFn( model_t* )( PVOID );
			PVOID pRenderable = GetRenderable( );
			return CallVirtual< OriginalFn >( pRenderable, 8 )( pRenderable );
		}
		PVOID GetRenderable( void )
		{
			return ( PVOID )( ( DWORD )this + 0x4 );
		}
		PVOID GetNetworkable( void )
		{
			return ( PVOID )( ( DWORD )this + 0x8 );
		}
		UINT PhysicsSolidMaskForEntity( void )
		{
			VirtualFn( UINT )( PVOID );
			return CallVirtual< OriginalFn >( this, 148 )( this );
		}
		QAngle& GetAbsAngles( void )
		{
			VirtualFn( QAngle& )( PVOID );
			return CallVirtual< OriginalFn >( this, 11 )( this );
		}
		Vector& GetAbsOrigin( void )
		{
			VirtualFn( Vector& )( PVOID );
			return CallVirtual< OriginalFn >( this, 10 )( this );
		}
		Vector GetEyePosition( void )
		{
			return GetAbsOrigin( ) + *( Vector* )( ( DWORD )this + Offsets::m_vecViewOffset );
		}
		Vector GetVelocity( void )
		{
			return *( Vector* )( ( DWORD )this + Offsets::m_vecVelocity );
		}
		QAngle GetViewPunch( void )
		{
			return *( QAngle* )( ( DWORD )this + Offsets::m_viewPunchAngle );
		}
		QAngle GetAimPunch( void )
		{
			return *( QAngle* )( ( DWORD )this + Offsets::m_aimPunchAngle );
		}
	};
	class PlayerData
	{
	public:
		bool		m_bActive;					// enable list for this player
		std::string	m_strName;					// entity name
		int			m_iIndex;					// entity index
		bool		m_bFriend;					// Is a friend? ignore him
		int			m_iCustomHitbox;			// Custom aim hitbox
		int			m_iCustomSmartAim;			// Number of bullets needed to enable smart aim
		int			m_iCustomSmartAimHitbox;	// Custom aim smart hitbox
		int			m_iTotalHits;				// Number of total hits
		int			m_iTotalMisses;				// Number of total misses
		int			m_iCurrentHits;				// current shots hit since last change
		int			m_iCurrentMisses;			// current shots missed since the last change
		float		m_flPitch;					// custom pitch
		float		m_flYaw;					// custom yaw

	public:
		void Reset( void )
		{
			m_bActive = false;
			m_strName.clear( );
			m_iIndex = 0;
			m_bFriend = false;
			m_iCustomHitbox = 0;
			m_iCustomSmartAim = 0;
			m_iCustomSmartAimHitbox = 0;
			m_iTotalHits = 0;
			m_iTotalMisses = 0;
			m_iCurrentHits = 0;
			m_iCurrentMisses = 0;
			m_flPitch = 0.f;
			m_flYaw = 0.f;
		}
	};
	class CTools
	{
	private:
		PlayerData	m_PlayerData[ 128 ];

	public:
		CTools( void );
		bool 			GetHitboxVector( CBaseEntity* pBaseEntity, int iHitbox, Vector& vecHitbox );
		bool			IsAbleToShoot( CBaseEntity* pBaseEntity, CBaseCombatWeapon* pWeapon );
		bool			IsBreakableEntity( CBaseEntity* pBaseEntity );
		bool 			IsVisible( const Vector& vecStart, const Vector& vecEnd, CBaseEntity* pIgnore, CBaseEntity* pEntity );
		bool			HandleBulletPenetration( CWeaponData* pWeaponData, FireBulletData& BulletData );
		bool			PenetrateWall( CBaseEntity* pBaseEntity, CBaseCombatWeapon* pWeapon, const Vector& vecPoint, float& flDamage );
		bool			SimulateFireBullet( CBaseEntity* pBaseEntity, CBaseCombatWeapon* pWeapon, FireBulletData& BulletData );
		bool 			TraceDidHitWorld( IEngineTrace::trace_t* pTrace );
		bool 			TraceDidHitNonWorldEntity( IEngineTrace::trace_t* pTrace );
		bool			TraceToExit( Vector& vecEnd, IEngineTrace::trace_t* pEnterTrace, Vector vecStart, Vector vecDir, IEngineTrace::trace_t* pExitTrace );
		bool			WorldToScreen( const Vector& vecOrigin, Vector& vecScreen );
		CBaseEntity*	GetLocalPlayer( void );
		DWORD_PTR		FindPattern( std::string strModuleName, PBYTE pbPattern, std::string strMask, DWORD_PTR nCodeBase = 0, DWORD_PTR nSizeOfCode = 0 );
		float			DotProduct( const float *v1, const float *v2 );
		float			DotProduct( const Vector& v1, const Vector& v2 );
		float			GetDistance( const Vector& vecOrigin, const Vector& vecOther );
		float			GetFoV( QAngle qAngles, Vector vecSource, Vector vecDestination, bool bDistanceBased = false );
		float			GetHitgroupDamageMult( int iHitgroup );
		IMaterial*		CreateMaterial( bool bFullbright, bool bIgnorez );
		IMaterial*		CreateMaterial( bool bShouldIgnoreZ, bool bFullBright, bool bIsWireframe );
		mstudiobbox_t*	GetHitboxData( CBaseEntity* pBaseEntity, int iHitbox );
		PlayerData*		GetPlayerData( int iIndex );
		QAngle			GetAntiAimAngles( CBaseEntity* pBaseEntity, bool bEnemyOnly = true );
		void			AngleVectors( const QAngle& qAngles, Vector& vecForward );
		void 			CalcAngle( const Vector& vecSource, const Vector& vecDestination, QAngle& qAngles );
		void 			ClampAngles( QAngle& qAngles );
		void 			UTIL_TraceLine( const Vector& vecStart, const Vector& vecEnd, unsigned int nMask, CBaseEntity* pCSIgnore, IEngineTrace::trace_t* pTrace );
		void 			ForceFullUpdate( void );
		void			ForceMaterial( Color color, IMaterial* material, bool useColor = true, bool forceMaterial = true );
		void 			MakeVector( QAngle qAngles, Vector& vecOut );
		void			MatrixToVector( const matrix3x4& pMatrix, Vector& out );
		void			NormalizeVector( Vector& vecIn );
		void 			ScaleDamage( int iHitgroup, CBaseEntity* pBaseEntity, float flWeaponArmorRatio, float& flDamage );
		void 			SinCos( float flRadians, float* pflSine, float* pflCosine );
		void			VectorAngles( const Vector &vecForward, Vector &vecAngles );
		void 			VectorTransform( const float *in1, const matrix3x4& in2, float *out );
		void 			VectorTransform( const Vector& in1, const matrix3x4& in2, Vector& out );
		void			ClearPlayerData( void );

	};
}

#endif