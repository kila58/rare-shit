typedef void(__stdcall* TD_CreateMove) (int, CUserCmd*);
TD_CreateMove OG_CreateMove;

typedef void(__fastcall* TD_PaintTraverse) (void*, void*, unsigned int, bool, bool);
TD_PaintTraverse OG_PaintTraverse;

typedef void(__fastcall* TD_OverrideView) (void*, void*, CViewSetup*);
TD_OverrideView OG_OverrideView;

QAngle Pos;
QAngle oldPos;
int Target = 0;
bool ShouldRevert = false;
Vector HeadPos;

void __stdcall CreateMove( int InputSampleTime, CUserCmd* UserCmd )
{
	OG_CreateMove( InputSampleTime, UserCmd );


	if (IsAlive((CBaseEntity*)InterfaceManager.ClientEntList->GetClientEntity(InterfaceManager.Engine->GetLocalPlayer()))) // Aria is a nice person!

		for (int i = 0; i < InterfaceManager.ClientEntList->GetHighestEntityIndex(); i++)
		{
			if (i == InterfaceManager.Engine->GetLocalPlayer())
				continue;

			if (!Aimbot.FilterTarget(i))
				continue;

			Target = i;
		}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		if (Aimbot.FilterTarget(Target)) 
		{
			CBaseEntity* Entity = (CBaseEntity*)InterfaceManager.ClientEntList->GetClientEntity(Target);
			Vector HeadPos = GetEyePos(Entity) - GetShootPos(); 
			VectorAngles(HeadPos, Pos);
			Pos = AngleNormalize(Pos);
			UserCmd->viewangles = Pos;
			UserCmd->buttons |= IN_ATTACK; // Attack!
			Aimbot.MovementFix(UserCmd);
		}

	}

}

void __fastcall PaintTraverse( void* _edx, void* _this, unsigned int Panel, bool Repaint, bool AllowForce )
{
	OG_PaintTraverse( _edx, _this, Panel, Repaint, AllowForce );

	
	if( !strcmp(InterfaceManager.Panel->GetClassName(Panel), "OverlayPopupPanel") )
	{
		Visuals.DrawString( 5, 0, 3, Color(0, 0, 255, 255), "FriendlyBot" );

		for( int i = 0; i < InterfaceManager.ClientEntList->GetHighestEntityIndex(); i++ )
		{
			CBaseEntity* Entity = (CBaseEntity*)InterfaceManager.ClientEntList->GetClientEntity( i );	

			if (Entity == NULL)
				continue;

			if (!IsAlive(Entity))
				continue;
			
			player_info_s PlayerInfo;
			if ( InterfaceManager.Engine->GetPlayerInfo( i, &PlayerInfo ) )
			{
				Vector Pos, Pos3D = Vector(0,0,0);
				Pos3D = Entity->GetAbsOrigin();
				if (  WorldToScreen( Pos3D, Pos ) )
				{

					Visuals.DrawStringA( 5, Pos.x, Pos.y, Color(255,255,255,255), "%s", PlayerInfo.name );
				}
			}
		
		}

	}
	
}
 

void __fastcall OverrideView(void* _EDX, void* This, CViewSetup* ViewSetup) 
{
	OG_OverrideView( _EDX, This, ViewSetup);

}

class CHooks
{
public:
	void Initialize();
}; CHooks Hooks;


void CHooks::Initialize()
{

	OG_PaintTraverse = (TD_PaintTraverse)VMTManager.Hook(InterfaceManager.Panel, 41, PaintTraverse);
	OG_CreateMove = (TD_CreateMove)VMTManager.Hook(InterfaceManager.ClientMode, 21, CreateMove);
	OG_OverrideView = (TD_OverrideView)VMTManager.Hook(InterfaceManager.ClientMode, 16, OverrideView);

}