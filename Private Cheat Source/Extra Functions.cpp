#include "SDK.h"
#include "Player Manager.h"
#include "Extra Functions.h"
#include "Math.h"
#include "CDrawManager.h"
#include "Player ESP.h" // Base Header
#include "Color Manager.h" // gDrawManager
#include "Control Variables.h"


//====================================================
float flGetDistance( Vector vOrigin, Vector vLocalOrigin )
{
	Vector vDelta = vOrigin - vLocalOrigin;

	float m_fDistance = sqrt( vDelta.Length( ) ); // Actually the sqrt in math.h is already inline'd

	if( m_fDistance < 1.0f )
		return 1.0f;

	return m_fDistance;
}
