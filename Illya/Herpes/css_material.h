/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 8
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

std::vector<IMaterial*> m_pWorldTextures;
std::vector<IMaterial*> m_pPlayerTextures;
std::vector<IMaterial*> m_pWeaponTextures;

int inter = 0;
bool inGame = false;
bool hasChanged = false;
bool inWalls = false;

void AddList( char const* pMatName, char const* pTextureGroupName, IMaterial* pTemp )
{
	if( m_pEngine->IsInGame() )
	{
		inGame = true;
	}
	else
	{
		if( inGame )
		{
			m_pWorldTextures.clear();
			m_pWeaponTextures.clear();
			inGame = false;
		}
	
		if(!strcmp(pTextureGroupName, "Lightmaps")||
            !strcmp(pTextureGroupName, "Particle textures")||
            !strcmp(pTextureGroupName, "Decal textures")||       
            !strcmp(pTextureGroupName, "CubeMap textures")||
            !strcmp(pTextureGroupName, "Dynamic Indices")||
            !strcmp(pTextureGroupName, "Dynamic Verts")||
            !strcmp(pTextureGroupName, "World Verts")||
            !strcmp(pTextureGroupName, "Lighting Verts"))
        {
            return;
        }
		else if( strstr( pMatName, "World" ) && !strstr( pMatName, "partical" ) )
		{
			m_pWorldTextures.push_back( pTemp );
		}
		else if( strstr( pMatName, "v_model" ) && !strstr( pMatName, "partical" ) )
		{
			m_pWeaponTextures.push_back( pTemp );
		}
	}
}

void GetAllMaterials()
{
    int size = m_pMaterialSystem->GetNumMaterials();
    int list = m_pMaterialSystem->FirstMaterial();

    while ( ++list != size )
    {
		IMaterial* mat = m_pMaterialSystem->GetMaterial( list );
		AddList(
			mat->GetName(),
			mat->GetTextureGroupName(),
			mat
		);
    }
}

void SetMaterials()
{
	m_pPlayerTextures.clear();

	IMaterial* arctic = m_pMaterialSystem->FindMaterial( "models\\player\\t_arctic\\t_arctic", "Model textures" );
	IMaterial* guerilla = m_pMaterialSystem->FindMaterial( "models\\player\\t_guerilla\\t_guerilla", "Model textures" );
	IMaterial* leet = m_pMaterialSystem->FindMaterial( "models\\player\\t_leet\\t_leet", "Model textures" );
	IMaterial* phoenix = m_pMaterialSystem->FindMaterial( "models\\player\\t_phoenix\\t_phoenix", "Model textures" );
	IMaterial* sas = m_pMaterialSystem->FindMaterial( "models\\player\\ct_sas\\ct_sas", "Model textures" );	
	IMaterial* gsg = m_pMaterialSystem->FindMaterial( "models\\player\\ct_gsg9\\ct_gsg9", "Model textures" );
	IMaterial* gign = m_pMaterialSystem->FindMaterial( "models\\player\\ct_gign\\ct_gign", "Model textures" );
	IMaterial* urban = m_pMaterialSystem->FindMaterial( "models\\player\\ct_urban\\ct_urban", "Model textures" );

	m_pPlayerTextures.push_back( arctic );
	m_pPlayerTextures.push_back( guerilla );
	m_pPlayerTextures.push_back( leet );
	m_pPlayerTextures.push_back( phoenix );
	m_pPlayerTextures.push_back( sas );
	m_pPlayerTextures.push_back( gsg );
	m_pPlayerTextures.push_back( gign );
	m_pPlayerTextures.push_back( urban );

/*	if( cvarXQZ == 1 )
	{
		for( int i = 0; i < (int)m_pPlayerTextures.size(); i++ )
		{
			m_pPlayerTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
			m_pPlayerTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_ZNEARER, true );
			m_pPlayerTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_HALFLAMBERT, true );
			m_pPlayerTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_FLAT, true );
		}
	}
	else
	{
		for( int i = 0; i < (int)m_pPlayerTextures.size(); i++ )
		{
			m_pPlayerTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
			m_pPlayerTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_ZNEARER, false );
			m_pPlayerTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_HALFLAMBERT, false );
			m_pPlayerTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_FLAT, false );
		}
	}*/
}


void RemoveEffects()
{
	SetMaterials();
	GetAllMaterials();

	IMaterial* flashbang = m_pMaterialSystem->FindMaterial( "effects\\flashbang", "ClientEffect textures" );
	IMaterial* flashwhite = m_pMaterialSystem->FindMaterial( "effects\\flashbang_white", "ClientEffect textures" );

	IMaterial *smoke = m_pMaterialSystem->FindMaterial( "particle\\particle_smokegrenade1", NULL );
	IMaterial *fog = m_pMaterialSystem->FindMaterial( "particle\\screenspace_fog", NULL );

	IMaterial* hands = m_pMaterialSystem->FindMaterial( "models\\weapons\\v_models\\hands\\v_hands", "Model textures" );

	/*if( flashbang && flashwhite )
	{
		if( cvarNoFlash == 1 )
		{
			flashbang->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
			flashwhite->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
		}
		else
		{
			flashbang->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
			flashwhite->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
		}
	}

	if( smoke || fog )
	{
		if( cvarNoSmoke == 1 )
		{
			smoke->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
			fog->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
		}
		else
		{
			smoke->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
			fog->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
		}
	}

	if( hands )
	{
		if( cvarNoHands == 1 )
		{
			hands->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
		}
		else
		{
			hands->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
		}
	}

	/*
	if( cvarAsus )
	{
		float level = cvarAsusLevel / 10;
		for( int i = 0; i < (int)m_pWorldTextures.size(); i++ )
		{
			m_pWorldTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_TRANSLUCENT, true );
			m_pWorldTextures[i]->AlphaModulate( level );
		}
	}
	else
	{
		for( int i = 0; i < (int)m_pWorldTextures.size(); i++ )
		{
			m_pWorldTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_TRANSLUCENT, true );
			m_pWorldTextures[i]->AlphaModulate( 1 );
		}
	}

	if( cvarAsusModels )
	{
		float level = cvarAsusLevel / 10;
		for( int i = 0; i < (int)m_pWeaponTextures.size(); i++ )
		{
			m_pWeaponTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_TRANSLUCENT, true );
			m_pWeaponTextures[i]->AlphaModulate( level );
		}
	}
	else
	{
		for( int i = 0; i < (int)m_pWeaponTextures.size(); i++ )
		{
			m_pWeaponTextures[i]->SetMaterialVarFlag( MATERIAL_VAR_TRANSLUCENT, true );
			m_pWeaponTextures[i]->AlphaModulate( 1 );
		}
	}
	*/
}