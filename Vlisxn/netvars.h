#pragma once

#include "main.h"

struct RecvProp;

struct DVariant {
	union {
		float	m_Float;
		long	m_Int;
		char	*m_pString;
		void	*m_pData;
		float	m_Vector[3];
		__int64	m_Int64;
	};
	int	m_Type;
};

struct CRecvProxyData {
	const RecvProp *m_pRecvProp;
	DVariant m_Value;
	int m_iElement;
	int m_ObjectID;
};

struct RecvTable {
	RecvProp *m_pProps;
	int m_nProps;
	void *m_pDecoder;
	char *m_pNetTableName;
	char pad00[ 2 ];
};

typedef void (__cdecl *RecvVarProxyFn)( const CRecvProxyData *, void *, void * );
struct RecvProp {
	char *m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void *m_pExtraData;
	RecvProp *m_pArrayProp;
	void *m_ArrayLengthProxy;
	RecvVarProxyFn m_ProxyFn;
	void *m_DataTableProxyFn;
	RecvTable *m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char *m_pParentArrayPropName;
};

struct ClientClass {
	char pad00[ 8 ];
	char *m_pNetworkName;
	RecvTable *m_pRecvTable;
	ClientClass	*m_pNext;
	int m_ClassID;
};

class Netvars {
private:
	int lookupNetvar( RecvTable *table, const char *pszProp, RecvProp **out = 0 ) {
		int off = 0;
	
		for( int i = 0; i < table->m_nProps; i++ ) {
			RecvProp *prop = &table->m_pProps[ i ];
			if( !prop || prop->m_pVarName[0] == '0' )
				continue;
	
			if( prop->m_pDataTable ) { // table, recursive
				int extra = lookupNetvar( prop->m_pDataTable, pszProp, out );
	
				if( extra )
					off = prop->m_Offset + extra;
			}
	
			if( !strcmp(prop->m_pVarName, pszProp) ) {
				if( out )
					*out = prop;

				return prop->m_Offset + off;
			}
		}
	
		return off;
	}

	//int lookupNetvar( RecvTable *table, const char *pszProp ) {
	//	for( int i = 0; i < table->m_nProps; i++ ) {
	//		RecvProp *prop = &table->m_pProps[ i ];
	//		if( !prop )
	//			continue;
	//
	//		if( prop->m_pVarName[0] == '0' )
	//			continue;
	//
	//		if( prop->m_pDataTable ) { // table, recursive
	//			int off = lookupNetvar( prop->m_pDataTable, pszProp );
	//
	//			if( off )
	//				return prop->m_Offset + off;
	//		}
	//
	//		if( !strcmp(prop->m_pVarName, pszProp) )
	//			return prop->m_Offset;
	//	}
	//
	//	return 0;
	//}

	int getOffset( const char *pszTable, const char *pszProp ) {
		ClientClass *clientClass = engine->GetAllClasses();

		do {
			if( !strcmp(clientClass->m_pRecvTable->m_pNetTableName, pszTable) )
				return lookupNetvar( clientClass->m_pRecvTable, pszProp );
		}while( clientClass = clientClass->m_pNext );

		return 0;
	}

	void dumpTable( RecvTable *table, FILE *f ) {
		for( int i = 0; i < table->m_nProps; i++ ) {
			RecvProp *prop = &table->m_pProps[ i ];
			if( !prop || prop->m_pVarName[0] == '0' )
				continue;
			
			fprintf_s( f, "\t%s -> 0x%x\n", prop->m_pVarName, prop->m_Offset );
			if( prop->m_pDataTable )
				dumpTable( prop->m_pDataTable, f );
		}
	}
public:
	int m_iHealth;
	int m_iTeamNum;
	int m_fFlags;
	int m_hActiveWeapon;
	int m_iArmor;
	int m_bHasHelmet;
	int m_iShotsFired;
	int m_bIsScoped;
	int m_clrRender;
	int m_vecVelocity;
	int m_Local;
	int m_aimPunchAngle;
	int m_viewPunchAngle;
	int m_iClip1;
	int m_nTickBase;
	int m_flNextAttack;
	int m_flNextPrimaryAttack;
	int m_vecViewOffset;
	int m_vecMins;
	int m_vecMaxs;
	int m_iPrimaryAmmoType;
	int m_iItemDefinitionIndex;
	int m_hOwnerEntity;
	int m_flC4Blow;

	Netvars() {
		m_iHealth				= getOffset( "DT_BasePlayer", "m_iHealth" );
		m_iTeamNum				= getOffset( "DT_BasePlayer", "m_iTeamNum" );
		m_fFlags				= getOffset( "DT_BasePlayer", "m_fFlags" );
		m_hActiveWeapon			= getOffset( "DT_BaseCombatCharacter", "m_hActiveWeapon" );
		m_hOwnerEntity			= getOffset( "DT_CSPlayer", "m_hOwnerEntity" );
		m_iArmor				= getOffset( "DT_CSPlayer", "m_iArmor" );
		m_bHasHelmet			= getOffset( "DT_CSPlayer", "m_bHasHelmet" );
		m_iShotsFired			= getOffset( "DT_CSPlayer", "m_iShotsFired" );
		m_bIsScoped				= getOffset( "DT_CSPlayer", "m_bIsScoped" );
		m_clrRender				= getOffset( "DT_BaseEntity", "m_clrRender" );
		m_vecVelocity			= getOffset( "DT_BasePlayer", "m_vecVelocity[0]" );
		m_Local					= getOffset( "DT_BasePlayer", "m_Local" );
		m_aimPunchAngle			= getOffset( "DT_BasePlayer", "m_aimPunchAngle" );
		m_viewPunchAngle		= getOffset( "DT_BasePlayer", "m_viewPunchAngle" );
		m_iClip1				= getOffset( "DT_BaseCombatWeapon", "m_iClip1" );
		m_nTickBase				= getOffset( "DT_BasePlayer", "m_nTickBase" );
		m_flNextAttack			= getOffset( "DT_BaseCombatCharacter", "m_flNextAttack" );
		m_flNextPrimaryAttack	= getOffset( "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" );
		m_vecViewOffset			= getOffset( "DT_BasePlayer", "m_vecViewOffset[0]" );
		m_vecMins				= getOffset( "DT_BaseEntity", "m_vecMins" );
		m_vecMaxs				= getOffset( "DT_BaseEntity", "m_vecMaxs" );
		m_iPrimaryAmmoType		= getOffset( "DT_BaseCombatWeapon", "m_iPrimaryAmmoType" );
		m_iItemDefinitionIndex	= getOffset( "DT_BaseAttributableItem", "m_iItemDefinitionIndex" );
		m_flC4Blow				= getOffset( "DT_PlantedC4", "m_flC4Blow" );
		
		msg( "Got netvars. 0x%x\n", m_iShotsFired );
	}

	void hookProp( const char *pszTable, const char *pszProp, RecvVarProxyFn hooked ) {
		ClientClass *clientClass = engine->GetAllClasses();
		
		RecvProp *prop = 0;
		do {
			if( !strcmp(clientClass->m_pRecvTable->m_pNetTableName, pszTable) )
				lookupNetvar( clientClass->m_pRecvTable, pszProp, &prop );
				
			clientClass = clientClass->m_pNext;
		}while( clientClass );
	
		if( !prop )
			return;
		
		//msg( "proxy: 0x%x\n", prop->m_ProxyFn );
		prop->m_ProxyFn = hooked;
		//msg( "proxy after: 0x%x, %s\n", prop->m_ProxyFn, prop->m_pVarName );
	}

	void dumpNetvars() {
		ClientClass *clientClass = engine->GetAllClasses();

		FILE *f;
		fopen_s( &f, "C:\\nabe\\netvars.txt", "wb+" );

		fprintf_s( f, "nabeFramework CSGO netvar dump // %s\n\n", __DATE__ );
		
		do {
			RecvTable *table = clientClass->m_pRecvTable;
			
			fprintf_s( f, "[ %s ]\n", table->m_pNetTableName );
			dumpTable( table, f );
			fprintf_s( f, "\n" );
		}while( clientClass = clientClass->m_pNext );

		fclose( f );
	}
}; extern Netvars *netvars;