/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

void HideCvar(const char* origCvarName, const char* defaultValue, int origFlags)
{
	ConVar* pCvar = m_pCVar->FindVar( origCvarName );
	if (!pCvar)
	{
		ConColorMsg( Color( 255, 0, 0, 255 ), "ERROR: Could not find cvar %s\n", origCvarName );
		return;
	}
	ConVar* pNewVar = (ConVar*)malloc( sizeof ConVar );

	memcpy( pNewVar, pCvar,sizeof( ConVar ));
	pNewVar->m_pNext = 0;
	m_pCVar->RegisterConCommand( pNewVar );
	pCvar->m_pszName = new char[50];
	
	char tmp[50];
	Q_snprintf(tmp, sizeof(tmp), "__%s", origCvarName);

	strcpy((char*)pCvar->m_pszName, tmp);
	pCvar->m_nFlags = FCVAR_NONE;

	new ConVar(origCvarName, defaultValue, origFlags, "Renamed");

	ConColorMsg( Color( 0, 255, 0, 255 ), "Successfully created cvar bypass %s from %s\n", tmp, origCvarName );
}

void ReplicateVars()
{
	static bool ran = false;
	if( ran )
		return;

	/*HideCvar("sv_cheats", "0", FCVAR_NOTIFY | FCVAR_REPLICATED | FCVAR_CHEAT);
	HideCvar("host_timescale", "1.0", FCVAR_NOTIFY | FCVAR_REPLICATED | FCVAR_CHEAT);
	HideCvar("r_drawparticles", "1", FCVAR_CLIENTDLL | FCVAR_CHEAT);
	HideCvar("r_drawothermodels", "1", FCVAR_CLIENTDLL | FCVAR_CHEAT);
	HideCvar("sv_consistency", "1", FCVAR_REPLICATED);
	HideCvar("fog_enable", "1", FCVAR_CLIENTDLL | FCVAR_CHEAT);
	HideCvar("fog_enable_water_fog", "1", FCVAR_CHEAT);
	HideCvar("mat_fullbright", "0", FCVAR_CHEAT);
	HideCvar("r_drawskybox", "1", FCVAR_NONE);
	HideCvar("r_3dsky", "1", FCVAR_NONE);

	HideCvar("sv_allow_voice_from_file", "1", FCVAR_REPLICATED);
	HideCvar("voice_inputfromfile", "0", FCVAR_NONE);*/

	ran = true;
}