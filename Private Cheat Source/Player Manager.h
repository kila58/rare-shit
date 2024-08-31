#ifndef _LOCAL_PLAYER_H_
#define _LOCAL_PLAYER_H_

#include "SDK.h"

#define me 1337
#define m_hActiveWeapon 0x12C0  
#define m_iClip1 0x15C0
#define m_iAccount 0x1C20

class CSetupPlayer
{
public:

	inline void Initialize( unsigned int nIndex ) 
	{ 
		m_nIndex		= nIndex;
	}

	inline CBaseEntity *BaseEnt( void ) const
	{
		return ALX.pEntList->GetClientEntity( m_nIndex );
	}
	
	
	inline CBaseEntity* GetActiveWeapon( void )
	{
		return ALX.pEntList->GetClientEntityFromHandle(*MakePtr(int*,BaseEnt(), m_hActiveWeapon));
	}



	inline CBaseEntity* GetWeaponFromSlot( int slot )
	{
		return ALX.pEntList->GetClientEntityFromHandle(*MakePtr(int*,BaseEnt(),ALX.pPlayerVariables->m_hMyWeapons + slot * 4));
	}
	
	inline int GetTeam( void )
	{
		return *MakePtr(int*,BaseEnt(),ALX.pPlayerVariables->m_iTeamNum);
	}

	inline byte GetLifeState( void )
	{
		return *MakePtr(byte*,BaseEnt(),ALX.pPlayerVariables->m_lifeState);
	}

	inline int GetHealth( void )
	{
		return *MakePtr(int*,BaseEnt(),ALX.pPlayerVariables->m_iHealth);
	}
	inline int GetFlags (void)
	{
		return *MakePtr(int*, BaseEnt(), ALX.pPlayerVariables->m_fFlags);
	}
	
	inline int GetArmor()
	{
		return *MakePtr(int*, BaseEnt(), ALX.pPlayerVariables->m_ArmorValue);
	}
	inline bool IsDefusing()
	{
		return *MakePtr(bool*, BaseEnt(), ALX.pPlayerVariables->m_bIsDefusing);
	}
	inline int GetClip()
	{
		return *MakePtr(int*, GetActiveWeapon(), m_iClip1);
	}
	inline int GetMoney()
	{
		return *MakePtr(int*, BaseEnt(), m_iAccount);
	}

private:
	int m_nIndex;
};

class CPlayers
{
public:
	inline CPlayers( void ) 
	{
		pPlayers = new CSetupPlayer[65];

		for ( unsigned int i = 0; i <= 64; i++)
			pPlayers[i].Initialize( i );
	}

	inline ~CPlayers( )
	{
		delete [] pPlayers;
	}

	inline CSetupPlayer& operator [] ( unsigned int i ) const
	{
		if( i == me )
			return pPlayers[ ALX.pEngine->GetLocalPlayer( ) ];

		else if( i > 64 || i <= 0 ) 
			return pPlayers[0];


		return pPlayers[i];
	}

private:
	CSetupPlayer *pPlayers;
}; 

extern CPlayers gPlayers;

#endif