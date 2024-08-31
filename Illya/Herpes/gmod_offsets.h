/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

// Offsets (GMOD)
#define gmodHEALTH		0x90
#define gmodLIFESTATE	0x8F
#define gmodPUNCHANGLE	0x6C

QAngle *GetPlayerPunchAngleGMOD( C_BaseEntity* pEnt )
{
	return ( QAngle* )( ( DWORD )pEnt + gmodPUNCHANGLE );
}