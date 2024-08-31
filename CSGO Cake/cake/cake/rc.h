namespace rc
{
	void manage_rc(usercmd* cmd)
	{
		icliententity* pme = g::ientlist->pget_cliententity(g::ivengine->get_me());
		cmd->vviewangles = cmd->vviewangles - (pme->vget_punch() * 2.0f);
	}
}