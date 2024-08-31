/*******************************************************
##     ## ######## ########  ########  ########  ######  
##     ## ##       ##     ## ##     ## ##       ##    ## 
##     ## ##       ##     ## ##     ## ##       ##       
######### ######   ########  ########  ######    ######  
##     ## ##       ##   ##   ##        ##             ## 
##     ## ##       ##    ##  ##        ##       ##    ## 
##     ## ######## ##     ## ##        ########  ###### 
********************************************************/

float GetSpreadFactor()
{
	C_BaseEntity* pLocal = GetLocalEntity();

	if( !pLocal )
		return 0.f;

	C_BaseCombatWeapon* pWeapon = GetActiveWeapon( pLocal );

	if( !pWeapon )
		return 0.f;

	int WeaponID = GetWeaponID( pWeapon );
	float flAccuracy = *( float* )( ( DWORD )pWeapon + cssACCURACY );
	bool m_bWeaponBit = *( bool* )( ( DWORD )pWeapon + 0x1768 );
	bool m_bWeaponBitPistol = *( bool* )( ( DWORD )pWeapon + 0x176 );
	int iFlags = GetPlayerFlags( pLocal );
	Vector myVelocity = *( Vector* )( ( DWORD )GetLocalEntity() + cssVELOCITY );

	float flSpreadFactor = 0.f;

	switch( WeaponID )
	{
		default:
		case WEAPON_NULL:
		case WEAPON_KNIFE:
		case WEAPON_FLASHBANG:
		case WEAPON_HE_GRENADE:
		case WEAPON_SMOKE_GRENADE:
		case WEAPON_C4:
			{
				return 0.f;
			}
		case WEAPON_AK47:
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() <= 140 )
						flSpreadFactor = flAccuracy * 0.02749999985098839f;
					else
						flSpreadFactor = flAccuracy * 0.07000000029802322f + 0.03999999910593033f;
				}
				else
					flSpreadFactor = flAccuracy * 0.4000000059604645f + 0.03999999910593033f;

				break;
			}
		case WEAPON_AUG: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() <= 140 )
						flSpreadFactor = flAccuracy * 0.01999999955296516f;
					else
						flSpreadFactor = flAccuracy * 0.07000000029802322f + 0.03500000014901161f;
				}
				else
					flSpreadFactor = flAccuracy * 0.4000000059604645f + 0.03500000014901161f;

				break;
			}
		case WEAPON_AWP: 
			{
				if( !( iFlags & FL_ONGROUND ) )
					flSpreadFactor = 0.8500000238418579f;
				else if( myVelocity.Length2D() > 140 )
					flSpreadFactor = 0.25f;
				else if( myVelocity.Length2D() > 10 )
					flSpreadFactor = 0.1000000014901161f;
				else if( iFlags & FL_DUCKING )
					flSpreadFactor = 0.0f;
				else
					flSpreadFactor = 0.001000000047497451f;

				if( GetFOV( pLocal ) == 90 )
					flSpreadFactor += 0.08f;

				break;
			}
		case WEAPON_DEAGLE:
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() > 5 )
						flSpreadFactor = ( 1 - flAccuracy ) * 0.25f;
					else
					{
						if( iFlags & FL_DUCKING )
							flSpreadFactor = ( 1 - flAccuracy ) * 0.115f;
						else
							flSpreadFactor = ( 1 - flAccuracy ) * 0.13f;
					}
				}
				else
					flSpreadFactor = ( 1 - flAccuracy ) * 1.5f;

				break;
			}
		case WEAPON_ELITES: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() > 5 )
						flSpreadFactor = ( 1 - flAccuracy ) * 0.1749999970197678f;
					else
					{
						if( iFlags & FL_DUCKING )
							flSpreadFactor = ( 1 - flAccuracy ) * 0.07999999821186066f;
						else
							flSpreadFactor = ( 1 - flAccuracy ) * 0.1000000014901161f;
					}
				}
				else
					flSpreadFactor = ( 1 - flAccuracy ) * 1.299999952316284f;

				break;
			}
		case WEAPON_FAMAS:
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() > 140 )
						flSpreadFactor = flAccuracy * 0.07000000029802322f + 0.02999999932944775f;
					else
						flSpreadFactor = flAccuracy * 0.01999999955296516f;
				}
				else 
					flSpreadFactor = flAccuracy * 0.300000011920929f + 0.02999999932944775f;

				break;
			}
		case WEAPON_FIVESEVEN: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() > 5.0f )
						flSpreadFactor = ( 1 - flAccuracy ) * 0.2549999952316284f;
					else
					{
						if( iFlags & FL_DUCKING )
							flSpreadFactor = ( 1 - flAccuracy ) * 0.07500000298023224f;
						else
							flSpreadFactor = ( 1 - flAccuracy ) * 0.1500000059604645f;
					}
				}
				else
					flSpreadFactor = ( 1 - flAccuracy ) * 1.5f;

				break;
			}
		case WEAPON_G3SG1: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() <= 5.0f )
					{
						if( iFlags & FL_DUCKING )
							flSpreadFactor = ( 1 - flAccuracy ) * 0.035f;
						else
							flSpreadFactor = ( 1 - flAccuracy ) * 0.055f;
					}
					else
						flSpreadFactor = 0.1500000059604645f;
				}
				else
					flSpreadFactor = ( 1 - flAccuracy ) * 0.45f;

				break;
			}
		case WEAPON_GALIL: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() <= 140 )
						flSpreadFactor = flAccuracy * 0.03750000149011612f;
					else
						flSpreadFactor = flAccuracy * 0.07000000029802322f + 0.03999999910593033f;
				}
				else
					flSpreadFactor = flAccuracy * 0.300000011920929f + 0.03999999910593033f;

				break;
			}
		case WEAPON_GLOCK18: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() > 5.0f )
						flSpreadFactor = ( 1.0f - flAccuracy ) * 0.1650000065565109f;
					else if( iFlags & FL_DUCKING )
						flSpreadFactor = ( 1.0f - flAccuracy ) * 0.07500000298023224f;
					else
						flSpreadFactor = ( 1.0f - flAccuracy ) * 0.1000000014901161f;
				}
				else
					flSpreadFactor = ( 1.0f - flAccuracy );

				break;
			}
		case WEAPON_M249: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() <= 140 )
						flSpreadFactor = flAccuracy * 0.02999999932944775f;
					else
						flSpreadFactor = flAccuracy * 0.0949999988079071f + 0.04500000178813934f;
				}
				else
					flSpreadFactor = flAccuracy * 0.5f + 0.04500000178813934f;

				break;
			}
		case WEAPON_M4A1:
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() <= 140 )
						flSpreadFactor = flAccuracy * 0.01999999955296516f;
					else
						flSpreadFactor = flAccuracy * 0.07000000029802322f + 0.03500000014901161f;
				}
				else
					flSpreadFactor = flAccuracy * 0.4000000059604645f + 0.03500000014901161f;

				break;
			}
		case WEAPON_MAC10: 
			{
				if( iFlags & FL_ONGROUND )
					flSpreadFactor = flAccuracy * 0.02999999932944775f;
				else
					flSpreadFactor = flAccuracy * 0.375f;

				break;
			}
		case WEAPON_MP5: 
			{
				if( iFlags & FL_ONGROUND )
					flSpreadFactor = flAccuracy * 0.03999999910593033f;
				else
					flSpreadFactor = flAccuracy * 0.2000000029802322f;

				break;
			}
		case WEAPON_P228: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() > 5.0f )
						flSpreadFactor = ( 1 - flAccuracy ) * 0.2549999952316284f;
					else
					{
						if( iFlags & FL_DUCKING )
							flSpreadFactor = ( 1 - flAccuracy ) * 0.07500000298023224f;
						else
							flSpreadFactor = ( 1 - flAccuracy ) * 0.1500000059604645f;
					}
				}
				else
					flSpreadFactor = ( 1 - flAccuracy ) * 1.5f;

				break;
			}
		case WEAPON_P90: 
			{
				if( !( iFlags & FL_ONGROUND ) )
					flSpreadFactor = flAccuracy * 0.3f;
				else if( myVelocity.Length2D() > 170 )
					flSpreadFactor = flAccuracy * 0.115f;
				else
					flSpreadFactor = flAccuracy * 0.045f;

				break;
			}
		case WEAPON_SCOUT: 
			{
				if( !( iFlags & FL_ONGROUND ) )
					flSpreadFactor = 0.2f;
				else if( myVelocity.Length2D() > 170 )
					flSpreadFactor = 0.075f;
				else if( iFlags & FL_DUCKING )
					flSpreadFactor = 0.0;
				else
					flSpreadFactor = 0.007f;

				break;
			}
		case WEAPON_SG550: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() <= 5.0f )
					{
						if( iFlags & FL_DUCKING )
							flSpreadFactor = ( 1 - flAccuracy ) * 0.03999999910593033f;
						else
							flSpreadFactor = ( 1 - flAccuracy ) * 0.05000000074505806f;
					}
					else
						flSpreadFactor = 0.1500000059604645f;
				}
				else
					flSpreadFactor = ( 1 - flAccuracy ) * 0.449999988079071f;

				break;
			}
		case WEAPON_SG552: 
			{
				if( iFlags & FL_ONGROUND )
				{
					if( myVelocity.Length2D() <= 140 )
						flSpreadFactor = flAccuracy * 0.01999999955296516f;
					else
						flSpreadFactor = flAccuracy * 0.07500000298023224f + 0.03500000014901161f;
				}
				else
					flSpreadFactor = flAccuracy * 0.449999988079071f + 0.03500000014901161f;

				break;
			} 
		case WEAPON_TMP: 
			{
				if( !( iFlags & FL_ONGROUND ) )
					flSpreadFactor = flAccuracy * 0.25f;
				else
					flSpreadFactor = flAccuracy * 0.02999999932944775f;

				break;		
			}
		case WEAPON_UMP45: 
			{
				if( iFlags & FL_ONGROUND )
					flSpreadFactor = flAccuracy * 0.03999999910593033f;
				else
					flSpreadFactor = flAccuracy * 0.239999994635582f;

				break;
			}
		case WEAPON_USP45: 
			{
					if( iFlags & FL_ONGROUND )
					{
						if( myVelocity.Length2D() > 5.0f )
							flSpreadFactor = ( 1.0f - flAccuracy ) * 0.2249999940395355f;
						else if( iFlags & FL_DUCKING )
							flSpreadFactor = ( 1.0f - flAccuracy ) * 0.07999999821186066f;
						else
							flSpreadFactor = ( 1.0f - flAccuracy ) * 0.1000000014901161f;
					}
					else
						flSpreadFactor = ( 1.0f - flAccuracy ) * 1.200000047683716f;

				break;
			}
		case WEAPON_M3:
			{
				flSpreadFactor = 0.f;

				break;
			}
		case WEAPON_XM1014:
			{
				flSpreadFactor = 0.f;

				break;	
			}
	}

	return flSpreadFactor;
}

void __AngleVectors( QAngle angles, Vector *f, Vector *r, Vector *u )
{
	float sr, sp, sy, cr, cp, cy;

	SinCos( DEG2RAD( angles.y ), &sy, &cy );
	SinCos( DEG2RAD( angles.x ), &sp, &cp );
	SinCos( DEG2RAD( angles.z ), &sr, &cr );

	if( f ){ f->x = cp * cy; f->y = cp * sy; f->z = -sp; }
	if( r ){
		r->x = ( -1 * sr * sp * cy +- 1 * cr * -sy );
		r->y = ( -1 * sr * sp * sy +- 1 * cr * cy );
		r->z = -1 * sr * cp;
	}
	if( u ){
		u->x = ( cr * sp * cy +- sr * -sy );
		u->y = ( cr * sp * sy +- sr * cy );
		u->z = cr * cp;
	}
}

void __VectorAngles( Vector forward, QAngle & angles )
{
	float tmp, yaw, pitch;

	if( forward.y == 0.f && forward.x == 0.f )
	{
		yaw = 0; pitch = 0;
	}
	else
	{
		yaw = atan2( forward.y, forward.x ) * 180 / M_PI;
		if( yaw < 0 ) yaw += 360;

		tmp = sqrt( forward.x * forward.x + forward.y * forward.y );
		pitch = atan2( forward.z, tmp ) * 180 / M_PI;
	}

	angles.x = pitch;
	angles.y = yaw;
	angles.z = 0;
}

QAngle GetSpreadAngle( UINT random_seed )
{
	random_seed = random_seed & 255;
	random_seed++;

	RandomSeed( random_seed );

	QAngle RandomFloatAngle(
		RandomFloat( -0.5, 0.5 ) + RandomFloat( -0.5, 0.5 ),
		RandomFloat( -0.5, 0.5 ) + RandomFloat( -0.5, 0.5 ),
		0.f
	);

	float flSpread = GetSpreadFactor();

	if( flSpread == 0.f ) 
		return QAngle( 0.f, 0.f, 0.f );

	RandomFloatAngle *= flSpread;

	RandomFloatAngle.z = 0.f;

	return RandomFloatAngle;
}

QAngle CompensateWeaponSpread( QAngle In, UINT random_seed )
{
	QAngle SpreadAngle = GetSpreadAngle( random_seed );

	if( SpreadAngle.x == 0.f && SpreadAngle.y == 0.f )
		return QAngle( 0.f, 0.f, 0.f );

	Vector forward, right, up, dir, view;
	__AngleVectors( In, &forward, &right, &up );

	dir.x = forward.x + SpreadAngle.x * right.x + SpreadAngle.y * up.x;
	dir.y = forward.y + SpreadAngle.x * right.y + SpreadAngle.y * up.y;
	dir.z = forward.z + SpreadAngle.x * right.z + SpreadAngle.y * up.z;

	view = 8192 * dir;

	QAngle dest;
	__VectorAngles( view, dest );
	dest.x *= -1;

	return In - dest;
}

void NoSpread( CUserCmd* cmd )
{
/*	if( cvarNoSpread == 0 )
		return;

	UINT next_random_seed = cmd->random_seed;
	QAngle spreadang = CompensateWeaponSpread( cmd->viewangles, next_random_seed );

	if( spreadang.IsValid() && ( ( spreadang.x == 0.f && spreadang.y == 0.f ) == false ) )
	{
		if( cmd->buttons & IN_ATTACK )
		{
			cmd->viewangles.x += spreadang.x;
			cmd->viewangles.y += spreadang.y;
		}
	}*/
}