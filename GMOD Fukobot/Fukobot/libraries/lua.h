class CLua{
public:
	bool GetLuaState();

	ILuaInterface* ClientLua = NULL;
	lua_State* State = NULL;

	void RunString(const char*);
	void RunFile();
}; CLua Lua;

bool CLua::GetLuaState()
{

	this->ClientLua = NULL;

	this->ClientLua = LuaShared->GetLuaInterface(LUA_CLIENT);
	if (this->ClientLua == NULL) 
		return false;
	
	return true;

}

void CLua::RunString(const char* LuaString)
{
	if (this->GetLuaState())	
	{
		this->ClientLua->RunString("[C]", "", LuaString, true, true);
	}
}