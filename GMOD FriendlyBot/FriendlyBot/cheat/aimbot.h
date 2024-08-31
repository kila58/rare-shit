class CAimbot
{
public:
	inline bool FilterTarget(int);
	void FakeAngleFix(CUserCmd*);
	void MovementFix(CUserCmd*);

}; CAimbot Aimbot;

QAngle FakeAngle = QAngle(0, 0, 0);

inline bool CAimbot::FilterTarget(int Index)
{
	CBaseEntity* Entity = (CBaseEntity*)InterfaceManager.ClientEntList->GetClientEntity(Index);

	if (Entity == NULL)
		return false;

	player_info_s PlayerInfo;

	if (!InterfaceManager.Engine->GetPlayerInfo(Index, &PlayerInfo))
		return false;

	if (Entity->IsDormant())
		return false;

	if (!IsAlive(Entity))
		return false;

	if (Entity->GetMoveType() == MOVETYPE_NOCLIP)
		return false;

	if (!IsVisible(Entity))
		return false;

	return true;

}
