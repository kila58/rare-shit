bool GetHitboxPosition ( int hitbox, Vector& origin, int index, QAngle& angles )
{
	if( hitbox < 0 || hitbox >= 20 )
		return false;
	matrix3x4_t pmatrix[MAXSTUDIOBONES];

	IClientEntity* ClientEntity = m_pClientEntList->GetClientEntity( index );
	if (! ClientEntity )
		return false;
	if ( ClientEntity->IsDormant() )
		return false;
	const model_t* model = ClientEntity->GetModel();
	if(!model)
		return false;
	studiohdr_t *pStudioHdr = m_pModelInfo->GetStudiomodel( model );
	if ( !pStudioHdr )
		return false;
	if(! ClientEntity->SetupBones( pmatrix, 128, BONE_USED_BY_HITBOX, m_pGlobals->curtime ) )
		return false;
	mstudiohitboxset_t *set = pStudioHdr->pHitboxSet( 0 );
	if ( !set )
		return false;
	mstudiobbox_t* pBox = NULL;
	pBox = pStudioHdr->pHitbox( hitbox, NULL );
	Vector min, max;
	MatrixAngles( pmatrix[ pBox->bone ], angles, origin );
	VectorTransform( pBox->bbmin, pmatrix[ pBox->bone ], min );
	VectorTransform( pBox->bbmax, pmatrix[ pBox->bone ], max );
	origin = ( min + max ) * 0.5f;

	return true;
}

		
bool GetHitboxPositionA( int hitbox, Vector& origin, C_BaseEntity* pBaseEntity, QAngle& angles )
{
	return GetHitboxPosition( hitbox, origin, pBaseEntity->index, angles );
}

C_BaseEntity* GetBaseEntity( int Index )
{
	IClientEntity* pEnt = m_pClientEntList->GetClientEntity( Index );
	if(! pEnt || pEnt->IsDormant() )
		return NULL;
			
	return (C_BaseEntity*) pEnt; //pEnt->GetBaseEntity(); will cause perf lossa bit
}

C_BaseEntity* Me ( )
{
	return GetBaseEntity( m_pEngine->GetLocalPlayer() );
}

bool Check( int Index )
{
	C_BaseEntity* pBaseEnt = GetBaseEntity ( Index );
			
	if(!pBaseEnt )
		return false;
	if( pBaseEnt->IsDormant() || !pBaseEnt->IsAlive() )
		return false;

	return ( pBaseEnt->index != m_pEngine->GetLocalPlayer() );
}

float DistanceTo ( C_BaseEntity* pBaseEntity )
{
	if( !pBaseEntity || !Me() )
		return NULL;

	Vector Delta = pBaseEntity->GetAbsOrigin() - Me()->GetAbsOrigin();
	float Distance = FastSqrt( Delta.Length( ) );
	return Distance;
}