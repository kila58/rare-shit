Vector CurrentSpreadVector = Vector(0, 0, 0);
int GetSpreadVector(lua_State* state)
{
	LUA->CheckNumber(1);
	LUA->CheckNumber(2);
	
	int X = LUA->GetNumber(1);
	int Y = LUA->GetNumber(2);

	CurrentSpreadVector = Vector(X, Y, 0);

}

