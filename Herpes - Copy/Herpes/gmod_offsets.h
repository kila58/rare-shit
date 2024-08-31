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
#define gmodHEALTH		0x09
#define gmodLIFESTATE	0xF8
#define gmodPUNCHANGLE	0xC6

QAngle *GetPlayerPunchAngleGMOD( C_BaseEntity* pEnt )
{
	return ( QAngle* )( ( DWORD )pEnt + gmodPUNCHANGLE );
}