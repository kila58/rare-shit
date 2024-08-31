/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

/*void HideCvar(const char* origCvarName, const char* defaultValue, int origFlags)
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

	ran = true;
}*/